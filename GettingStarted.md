<p><b>Last revision:</b> ver. 2.0 - 13 May 2013</p>

# Getting started with omicron #
This page offers basic information on how to build omicron, and how to start creating applications that use the omicron toolkit.

omicron is distributed as a source-only project. Users are responsible for creating binaries for their operating system and architecture. The build process is kept as simple as possible and should require very little configuration effort by the user.

## Building omicron ##

### Operating system support ###
This is the current supported status of omicron:
  * **Windows XP/Vista/7:** VS2010 32bit builds and is regularly tested. VS2008 32bit deprecated and may not work. 64bit builds not tested regularly.
  * **Linux:** 64bit builds and is regularly tested (SUSE). 32bit should build but is tested less often (Ubuntu).
  * **OSX, Intel:** 64bit currently not supported (builds but fails to link), 32bit not supported

### Building on Windows ###
This section explains how to build omicron on Windows. The basic procedure and requirements are similar for all supported operating systems, so you can use this as a general guideline.
#### Requirements ####
  * An SVN client [TortoiseSVN recommended](http://tortoisesvn.net/)
  * Visual Studio 2010 (Visual C++ 2010 Express edition works too, [Download it here](http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express))
  * CMake [Download it here](http://www.cmake.org/cmake/resources/software.html)
  * **if you use the Express Edition of Visual C++** and want to enable Optitrack camera support you will have to download the [Windows SDK](http://www.microsoft.com/en-us/download/details.aspx?id=3138) as well

#### Step 1: download the code ####
  * Follow the instruction of your svn client of choice and checkout:
    * https://omicron-sdk.googlecode.com/svn/trunk/ if you are a **registered committer** for the project.
    * http://omicron-sdk.googlecode.com/svn/trunk/ if you are an anonymous user.

#### Step 2: running CMake ####
  * Run cmake-gui.
  * In the **where is the source code** field, specify the directory where you checked out the source code.
  * In the **where to build the binaries** field, specify a directory you will want your project files and binaries to be generated.
  * Hit **Configure**: The option table will look simlar to the following figure:
<p align='middle'><img src='http://omicron-sdk.googlecode.com/svn/wiki/Building/cmake.png' width='500' /></p><p align='middle'>
<i><sup>The Windows CMake GUI. Versions on other operating systems have a similar layout.</sup></i>
</p>
  * Enable and disable desired options. For a guide on options go to the bottom of this page. **Note:** omicron should build just fine if you leave everything to their default values.
  * If you changed any options, hit **configure** again. You may have to repeat this proces multiple times if new options appear.
  * Once you are done configuring all build options, hit **Generate**. If the process ends without errors, you will have Visual Studio solution files under your build directory.

**SUGGESTION:** Keep both directories under a single 'root' folder. For example you can have something like this
  * `omicron`: your root folder
    * `source`: the source code directory, checked out from http://omicron-sdk.googlecode.com/svn/trunk/
    * `build`: the build and binaries directory

You should now be able to open the generated Visual Studio solution and build everything.

### Building on Linux ###
The basic instructions are the same as for the Windows guide. Under linux, you will use make as your build system. To summarize, the process will be:
  * Download the code
  * create a build directory
  * get in the build directory and run `cmake -i <path-to-source-dir>` or run `ccmake` or `cmake-gui`. The commands will respectively run an interactive shell version of cmake, a curses based version, and a gui version similar to the windows one.
  * Follow the same steps as the one in windows to generate a makefile
  * run `make`
  * if the build succeeds, get in the `bin` directory and you should find your libraries and compiled demo applications.



---

## Adding omicron to your application: omicronConnector ##
if you want to use omicron-supported input devices in the easiest way possible, the following is the best solution:
  * You run the omicron input server executable (`oinputserver`) locally or on the machine where the input devices are phisically attached
  * you add the `omicronConnector` header file to your c++ application
...and that's pretty much it. You won't need to add any dependencies to your original project, other than one single header file. This is by far the easiest solution, altough it requires you to run the input server as a separate application you connect to.

The following is an example of code using omicronConnector:
```
	class ConnectorListener: public IOmicronConnectorClientListener
	{
	public:
		virtual void onEvent(const EventData& e)
		{ printf("event received\n"); }
	};

	int main(int argc, char** argv)
	{
		ConnectorListener listener;
		OmicronConnectorClient client(&listener);
		client.connect("127.0.0.1", 27000);
		while(true)
		{
			client.poll(); 
		}
	}
```
All you need to do is instantiate a copy of the `OmicronConnectorClient` template, passing it a class with an `onEvent` method as a template argument. After connecting and running a polling loop, the `onEvent` method will be called for each event received from the input server.

## Adding omicron to your application: direct integration ##
In this scenario, you want to integrate omicron directly inside your application, without running an external input server. This is a slightly more complex but supported alternative to using omicronConnector. We assome you use CMake to manager your application build. In the explanation, we assume **omicronSource** is the root directory of your omicron source installation.

### Step 1: Create the directory structure ###
  * Create a new directory (say, `myapp-source`).
  * copy omicronSource/FindOmicron.cmake to myapp-source

### Step 2: Create the source and cmake file ###
In a new directory, create a source file (say, `myapp.cpp`). Also create a `CMakeLists.txt` file in the same directory, with the following content:
```
	cmake_minimum_required(VERSION 2.8.1) 
	project(myapp)

	include(${CMAKE_SOURCE_DIR}/FindOmicron.cmake)

	include_directories(${OMICRON_INCLUDE_DIRS})
	add_executable(myapp myapp.cpp)
	target_link_libraries(myapp ${OMICRON_LIB})
```
You should now be able to run cmake to configure and generate build files for your platform.

The contents of your source file could be something like this:
```
	#include <omicron.h>

	using namespace omicron;

	void onEvent(const Event& e)
	{
		// DO stuff with the event.
	}

	int main(int argc, char** argv)
	{
		// Add a default filesystem data sources (used to retrieve configuration files and other resources)
		DataManager* dm = DataManager::getInstance();
		dm->addSource(new FilesystemDataSource("./"));

		// Load a configuration file for this application and setup the system manager.
		// Read config file name from command line or use default one.
		const char* cfgName = "eventlogger.cfg";
		if(argc == 2) cfgName = argv[1];
		Config* cfg = new Config(cfgName);

		// Start running services and listening to events.
		ServiceManager* sm = new ServiceManager();
		sm->setupAndStart(cfg);

		omsg("eventlogger start logging events...");
		while(true)
		{
			// Poll services for new events.
			sm->poll(); 

			// Get available events
			Event evts[OMICRON_MAX_EVENTS];
			int av;
			if(0 != (av = sm->getEvents(evts, ServiceManager::MaxEvents)))
			{
				for( int evtNum = 0; evtNum< av; evtNum++)
				{
					onEvent(evts[evtNum]);
				}
			}
		}
		delete cfg;
	}
```

The code is slightly more complex than the omicronConnector example, but not that much. The main difference would be the need to add the input service libraries inside your application binary folder. Also, some input services only run on windows: check the [input service reference page](ServiceReference.md) for more information.
