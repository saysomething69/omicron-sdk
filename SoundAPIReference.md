<p><b>Last revision:</b> ver. 1.2 - 4 April 2013</p>



# SoundAPI reference #
The Omicron Sound API allows CAVE2 developers a simple way to trigger, place, and update sounds in virtual space. The API sends simple Open Sound Control (OSC) messages to a Supercollider server developed by JD Pirtle.

The coordinate system used by the sound api is the same as the tracker: origin on the floor at the center of CAVE2, Y-up. Positions are stored as vector3 floats in meters. Orientations in quaternions.

<p align='middle'><img src='http://omicron-sdk.googlecode.com/svn/wiki/Sound/CAVE2CoordinateSystem.png' width='500' /></p><p align='middle'>
<i><sup>The CAVE2 Tracking/Speaker Coordinate System.</sup></i>
</p>


---

## `class SoundManager` ##
Provides basic management of the sound server and sound objects. Uses the Ultra minimalistic OSC library (http://gruntthepeon.free.fr/oscpkt/).

### Methods ###
| Method(s) | Description | Associated OSC Messages |
|:----------|:------------|:------------------------|
| `connectToServer(IP, port)` | Connects to a sound server at the specified IP address and port. |                         |
| `startSoundServer()` | Starts the sound server and loads the default synthdefs. | /startServer /loadSynth /loadStereoSynth |
| `stopSoundServer()` | Shuts down the sound server. | /killServer             |
| `getEnvironment()`, `setEnvironment(SoundEnvironment)` | Gets and sets the current sound environment. |                         |
| `sendOSCMessage(Message)` | Sends an OSC message to the server. |                         |
| `showDebugInfo(bool)` | Toggles console display of all debugging messages. |                         |
| `isDebugEnabled()` | Returns whether displaying debugging information to the console has been enabled. |                         |

---

## `class SoundEnvironment` ##

The sound environment class provides a set of default sound parameters used for all sound objects it creates.

### Methods ###
| Method(s) | Description | Associated OSC Messages |
|:----------|:------------|:------------------------|
| **Environment Management** |             |                         |
| `stopAllSounds()` | Stops any currently playing sounds in the current sound environment | /freeNode (nodeID)      |
| `cleanupAllSounds()` | Unloads all sounds in the current sound environment. | /freeBuf (bufferID)     |
| `getSoundManager()` |             |                         |
| `getAssetDirectory()`, `setAssetDirectory(path)` | Gets and sets the default directory path for all created sounds. |                         |
| `getRoomSize()`, `setRoomSize(value)` | Gets and sets the default reverb room size for all created sounds as a normalized float (0.0-1.0) | /setReverb (nodeID, wetness, roomSize) |
| `getWetness()`, `setWetness(value)` | Gets and sets the default reverb wetness/dryness for all created sounds as a normalized float (0.0-1.0) | /setReverb (nodeID, wetness, roomSize) |
| **Sound Management** |             |                         |
| `loadSoundFromFile(name, fileName)` | Creates an new sound object with the given name and path to the sound file. | /loadBuffer (See Sound::loadFromFile) |
| `createInstance(sound)` | Creates an new sound instance from the given sound object. |                         |
| `getListenerPosition()`, `setListenerPosition(pos)` | Gets and sets the listener position. This corresponds to CAVE2's navigated position in the virtual space (meters, Y up). |                         |
| `getListenerOrientation()`, `setListenerOrientation(orientation)` | Gets and sets the listener orientation. This corresponds to CAVE2's navigated position in the virtual space (Quaternion). |                         |
| `getUserPosition()`, `setUserPosition(pos)` | Gets and sets the user position. This corresponds to tracked user's head position in tracker space (meters, Y up). **Not fully supported yet - will assume user is at origin** |                         |
| `getUserOrientation()`, `setUserOrientation(orientation)` | Gets and sets the user orientation. This corresponds to tracked user's head orientation in tracker space (Quaternion). |                         |
| `worldToLocalPosition(position)` | Convert a position from virtual space to local tracker/speaker space based on the listener's current orientation and position. **SoundInstance uses this automatically unless setLocalPosition() is used instead of setPosition()**|                         |
| `localtoWorldPosition(position)` | Convert a position from local tracker/speaker to virtual space space based on the listener's current orientation and position. |                         |


---

## `class Sound` ##
A sound object storing the bufferID, filepath to the sound, and the default sound properties. These correspond to Supercollider buffers. Sound objects will use the same room size and wetness values as the current environment by default. If these parameters are manually changed (i.e. setRoomSize() is used) the sound will use those values instead until resetToEnvironmentParameters() is called.

### Methods ###
| Method(s) | Description | Associated OSC Messages |
|:----------|:------------|:------------------------|
| `loadFromFile(path)` | Loads a sound file withe the given path. | /loadBuffer (bufferID,path) |
| `getRoomSize()`, `setRoomSize(value)` | Gets and sets the default reverb room size for this sound as a normalized float (0.0-1.0) |                         |
| `getWetness()`, `setWetness(value)` | Gets and sets the default reverb wetness/dryness for this sound as a normalized float (0.0-1.0) |                         |
| `resetToEnvironmentParameters()` | Resets this sound objects environment parameters (room size and reverb) to the environment settings |                         |
| `isUsingEnvironmentParameters()` | Returns false if the environment paremeters for this sound was manually changed using setRoomSize() or setWetness() |                         |

The following is a snippet of the soundtest.cpp application which is included within Omicron.
In you use the Omicron SoundAPI in conjunction with OmegaLib's rendering framework, you only need to get the sound environment and load sounds from it. All SoundManager initializations and setting the listener and user positions it provided by the OmegaLib engine class. For using the Omicron SoundAPI functions using Omegalib's python interface, see [OmegaPythonReference](http://code.google.com/p/omegalib/wiki/OmegaPythonReference#Sound_Management).

Sound setup outside of Omegalib:
```
	SoundManager* soundManager;
	SoundEnvironment* env;
	Sound* sound;
	Sound* music;
	
	SoundTest()
	{
		soundManager = new SoundManager("supercolliderIP",57120);
		soundManager->startSoundServer();
		env = soundManager->getSoundEnvironment();
		
		// If this is not set, you will have to set an absolute path below
		env->setAssetDirectory("/Users/demo/sounds/");
		
		// This effectivly looks for '/Users/demo/sounds/menu_select.wav'
		sound = env->loadSoundFromFile("beep", "menu_select.wav");
		
		// This effectivly looks for '/Users/demo/sounds/music/filmic.wav'
		music = env->loadSoundFromFile("music", "/music/filmic.wav");
	}
	
	~SoundTest()
	{
		// Call the SoundManager destructor, cleans up all sounds
		soundManager->~SoundManager();
	}
	
	virtual bool handleEvent(const Event& evt)
	{
		switch(evt.getServiceType())
		{
			case Service::Mocap:
				// Here we assume the mocap ID of the head tracked user is 0.
				if( evt.getSourceId() == 0 )
				{
					// evt.getPosition() returns a Vector3f
					soundManager->setListenerPosition( evt.getPosition() );
					
					// evt.getOrientation() returns a Quaternion
					soundManager->setListenerOrientation( evt.getOrientation() );
				}
		}
	}
	
```

Sound setup using Omegalib in C++:
```
	SoundEnvironment* env;
	Sound* sound;
	Sound* music;
	
	virtual void initialize()
	{
		// SoundManager initializations, listener position, and cleanup handled by engine.
		// Sound server IP and ports set by OmegaLib configuration file.
		
		env = getEngine()->getSoundEnvironment();
		env->setAssetDirectory("/Users/demo/sounds/");
		
		// All sound files should be in .wav format
		// For positional sounds, file should be mono.
		// Rest of important sound code is in handleEvent()
		sound = env->loadSoundFromFile("beep", "/menu_sounds/menu_select.wav");
		music = env->loadSoundFromFile("music", "/music/filmic.wav");
	}
```

Sound setup using Omegalib in Python:
```
	env = getSoundEnvironment()

	env.setAssetDirectory("/Users/demo/sounds/");

	# Just using s_ to denote a sound object verses a sound instance (si_)
	s_sound = env.loadSoundFromFile("beep", "/menu_sounds/menu_select.wav");
	s_music = env.loadSoundFromFile("music", "/music/filmic.wav");
```


---

## `class SoundInstance` ##
A sound instance object storing the associated sound object, instanceID, and sound parameters (volume, mix, reverb, etc.). These correspond to Supercollider nodes.

### Methods ###
| Method(s) | Description | Associated OSC Messages |
|:----------|:------------|:------------------------|
| **Playback** |             |                         |
| `play()`  | Plays a sound with the default sound parameters. | /play (instanceID, bufferID, volume, xPos, yPos, zPos, listenerX, listenerY, listenerZ, width, mix, reverb, loop) |
| `playStereo()` | Plays a stereo sound with the default sound parameters. | /playStereo (instanceID, bufferID, volume, loop) |
| `play(pos,volume,width,wetness,roomSize,loop)` | Plays a sound with the specified sound parameters. Position is in navigated/world space (meters, Y up). | /play (instanceID, bufferID, volume, xPos, yPos, zPos, listenerX, listenerY, listenerZ, width, mix, reverb, loop) |
| `playStereo(volume,loop)` | Plays a stereo sound with the specified sound parameters. | /play (instanceID, bufferID, volume, loop) |
| `stop()`  | Stops the sound from playing. | /freeNode (instanceID)  |
| `fade(targetVolume, duration)` | Fades the sound instance from it's current volume to the target volume over the specified duration in seconds | /setVolEnv (instanceID, targetVolume, envelopeDuration) |
| **Parameters** |             |                         |
| `getLoop()` `setLoop(loop)` | Gets and sets the looping flag. |
| `getPosition()`, `setPosition(pos)` | Gets and sets the position of the sound in navigated/world space (meters, Y up). This function will convert world position to local tracker/speaker position based on the SoundEnvironment's listenerPosition. | /setObjectLoc (instanceID, xPos, yPos, zPos) |
| `getLocalPosition()`, `setLocalPosition(pos)` | Gets and sets the position of the sound in local tracker/speaker space (meters, Y up). | /setObjectLoc (instanceID, xPos, yPos, zPos) |
| `getVolume()`, `setVolume(volume)` | Gets and sets the normalized (0.0-1.0) sound instance volume. | /setVol (instanceID, volume) |
| `getWidth()`, `setWidth(width)` | Gets and sets the number of speakers (1-20) to pan the sound. |                         |
| `isEnvironmentSound()`, `setEnvironmentSound(bool)` | Gets and sets the environment flag (play on all 20 speakers) of the sound. |                         |
| `getWetness()`, `setWetness(wetness)` | Gets and sets the wetness/dryness (0.0-1.0) of the sound instance. | /setReverb (nodeID, wetness, roomSize) |
| `getRoomSize()`, `setRoomSize(roomSize)` | Gets and sets the reverb/room size (0.0-1.0) of the sound instance. | /setReverb (nodeID, wetness, roomSize) |

C++ Example:
```
	virtual void initialize()
	{
		// Previous SoundManager/SoundEnvironment/Sound setup
		// ....
		
		// Play some background music at startup
		// playStereo() is for ambient music and plays in a fixed left/right channel configuration
		SoundInstance* musicInst = new SoundInstance(music);
		musicInst->setVolume(0.2);
		musicInst->setLoop(true);
		musicInst->playStereo();
	}
	
	virtual bool handleEvent(const Event& evt)
	{
		if( evt.getFlags() == Event::ButtonLeft )
		{
			SoundInstance* soundInst = new SoundInstance(sound);
			
			// Place the sound at the wand position
			soundInst->setPosition( evt.getPosition() );
			
			// We could also set other sound parameters before playing
			soundInst->setVolume(0.7);
			soundInst->setRoomSize(0.5);
			
			soundInst->play();
		}
	}
```

Python Example:
```
	# Previous SoundEnvironment/Sound setup
	# ....
	
	# Play some background music at startup
	# playStereo() is for ambient music and plays in a fixed left/right channel configuration
	si_music = SoundInstance(s_music)
	
	si_music.setVolume(2.0)
	si_music.setLoop(True)
	si_music.playStereo()
	
	def onEvent():
		global playStopLight
		global moveVector
		
		e = getEvent()
		if(e.getServiceType() == ServiceType.Wand):
			
			if(e.isButtonDown( EventFlags.ButtonLeft )):
				si_sound = SoundInstance(s_sound)
				
				# Place the sound at the wand position
				si_sound.setPosition( e.getPosition() )
				
				# We could also set other sound parameters before playing
				si_sound.setVolume(0.7)
				si_sound.setRoomSize(0.5)
				
				si_sound.play()
				
	# Register our evern function with Omegalib
	setEventFunction(onEvent)
```