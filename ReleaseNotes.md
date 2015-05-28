# omicron v2.0 (**current developer version**) #
**Initial Revision**: 183
## Summary ##
## Major Changes ##
**Added the**Sound API**, can be used to interface to a Supercollider sound server using the OpenSoundControl protocol.** Added the **Asset Cache manager**: the cache manager can synchronize application assets across different machines. The cache manager is used by the sound system to send sound files to the sound server machine, but can be used independently from the sound API.
**Old porthole code removed** Streamlined Event structure, removed a few unused event types.
**Removed `Color` class (moved to omegalib)**


---

# omicron v1.2 (**current developer version**) #
**Initial Revision**: 36
**Branch-out**: 182
## Summary ##
omicron 1.2 is the version used in the first installation of the CAVE2 system. It's main changes over 1.1 are **improved stability**, a better input server, support
for an **osc-based sound server** and various **gamepad and wand** support improvements
## Change Log ##
NEW: added support for multiple instances of same service
FIX: Disabling legacy client data transmission (causes all data to jitter).
NEW: Handling of worldToLocal calculations for sound server. NEW: Additional functions for handling camera position and user head-tracked position separately.
FIX: OInputServer handling of Omicron and Legacy clients simultaneously.
CHANGE: tinystr in omega::xml namespace
CHANGE: tinyxml put in omega::xml namespace to avoid conflicts in omegalib when using the SAIL library
NEW: COnfig::readVector4f
FIX: getSound(String). CHANGE: Removed 'not fully implemented' messages from some functions.
CHANGE: Sound buffer IDs 0-9 are now considered reserved by the sound server. New sounds start with ID 10.
FIX: SoundInstance::setMix() now works as intended. FIX: Updated soundtest for recent SoundEnvironment changes.
CHANGE: Sound cleanup and listenerPosition functions moved to SoundEnvironment NEW: SoundEnvironment now sends cleanup buffer/instance node commands to SuperCollider. Added functions for specifying sound size.
FIX: loadSoundFromFile using assetDirectory CHANGE: Default volume is now 0.5
NEW: playStereo() added to Sound class. NEW: Set assetDirectory path for SoundEnvironment class. FIX: Default mix, reverb for sounds set to 0.
FIX: PQService was using screen size and offset incorrectly when generating touch positions
FIX: sound stuff
CHANGE: Sound classes derive from ReferenceType, char**converted to string, plus a few minor improvements.
OpenNI: Added support to track only the closest user to a point.
FIX: Omicron-OmegaLib build on Windows and Linux. NEW: Default sound parameters and setters.
NEW: Math::quaternionToEuler
CHANGE: SoundInstances have additional width, reverb, and mix parameters.
UPDATE: Omicron examples for Processing 2.0b3.
FIX: Second touch key (control) updated for Processing 2.0b3.
FIX: Linux build.
CHANGE: OmegaLib compatibility
FIX: VRPNDevice now looks for Wand events in addition to Controller events. (Fixes CalVR controller button input).
FIX: some inlines removed (caused link errors in win32 release mode)
FIX: oinputserver->OmicronAPI(Processing/Java) legacy dgram parsing fixed. NEW: Java OmicronTester for testing Processing library directly in Eclipse.
NEW:Event::isButtonUp
FIX: linux build
NEW: TcpClientConnection
CHANGE: OmicronAPI - added additional comments for Processing alpha differences.
CHANGE: ologdisable now does not disable sending og to custom listeners
CHANGE: OptiTrackService disabled by default (to compile on express-edition visual studio IDEs)
CHANGE: Event::isKeuDOwn/Up now takes int instead of char
NEW: Kinect two-handed rotation gesture (yaw and roll).
CHANGE: removed deprecated Event::setPosition(int component)
FIX: MSKinectService - multiple Kinect connect/disconnect. Single Kinect skeleton tracking. FIX: VRPNDevice checks for controller type.
CHANGE: revised ArgumentHelper behavior on parsing errors
NEW: MSKinectService - Partial support for multiple Kinects. Single Kinect skeleton tracking only. NEW: MSKinectService - Default or seated tracking modes. CHANGE: Omicron skeleton enumerations are now part of Event class and are shared bet...
NEW: HttpRequest (WIP)
NEW: HttpRequest (WIP)
CHANGE: VRPNDevice Navigator controller matches mouse configuration (left/right/mouse click -> Cross/Circle/Analog Button2). Analog stick now functions like a mouse wheel would.
CHANGE: Errors in ArgumentHelper parsing don't close the application anymore
CHANGE: Config is now a ReferenceType
FIX: leaks in tcp server
NEW: MSKinectService implemented. Currently connects to a single Kinect and extracts joint data (no event generation yet).
FIX: refcount
FIX: Cleanup of oinputserver messages.
CHANGE: improved refcount support
CHANGE: minor changes to StringUtils
CHANGE: few PS3 Move button mappings
NEW: log disabling support
FIX: Various fixes for CAVE2
NEW: Event::parseButton
FIX: OmicronAPI Event types are no longer using an enum due to differences in Java enums verses C++.
FIX: Replaced omegaLib references with omicron. FIX: Using 'omicron\_legacy\_data\_on' handshake. FIX: Processing examples are now read-only. NEW: Processing Kinect example (alpha). CHANGE: OmicronAPI now uses enumerations for ServiceType - be...
FIX: Controllers can now be added after initialization. CHANGE: DirectXInputService handles disconnects/reconnects better. FIX: Changed PS3 button mappings to match DS3\_TOOL 0.7.1001 default mapping. NEW: MSKinectService for Kinect for Wind...
FIX: linux build
FIX: removed inlines
CHANGE: oinputserver cleanup
UPDATE: oinputserver and soundserver Linux support CHANGE: oinputserver and connectorClient handshake changed to 'omicron\_data\_on' to distinguish new and legacy data formats. CHANGE: legacy oinputserver and legacy NetService handshake now '...
CHANGE: StringUtils methods return Vector**

&lt;String&gt;


CHANGE: cleaned up math library
NEW: Dictionary::exists
CHANGE: more debug messages
NEW: GestureService UPDATE: Mocap Gestures: Right hand (left/right/up/down) swipe and click.
CHANGE: OSCTest app renamed to soundtest NEW: Added listener position to SoundManager NEW: VRPNDevice for streaming data out in VRPN format. NEW: oinputserver sends out first controller as VRPN data (CalVR PSNavigator prototype - remove aft...
FIX: LegacyNetService handshake corrected. Updated to new omega\_legacy handshake. serverPort renamed to msgPort to reduce confusion. UPDATE: LegacyNetService mocap datagram updated with userID field for Kinect.
CHANGE: non-templated omicronConnectorClient
CHANGE: non-templated omicronConnectorClient
CHANGE: non-templated omicronConnectorClient
CHANGE: comments
NEW: Sound volume control and playing multiple sounds.
NEW: ReferenceType object count
CHANGE: Eigen vectorization disabled by default (does not play along well with boost::python wrappers)
REMOVED: old file (TabletService.h)
NEW: Color supports RGB and RGBA strings
NEW: Start/stop OSC sound server, loadBuffer, play sound, stop sound. NEW: Processing mouse events now sent through OmicronAPI event system.
NEW: SoundManager, SoundEnvironment, Sound classes. CHANGE: SoundManager replaces OSCService for OSC messaging. CHANGE: PS3 controller (Sixaxis and Navigator) support added to DirectXInputService.
FIX: Re-exported jar for Java 1.6. FIX: Re-ordered constructor to fix occasional null pointer on OmicronAPI. FIX: Cleaned up examples. CHANGE: Examples moved to library examples (examples are now listed in the Processing examples menu). NEW...
NEW: Processing fullscreen example for Cyber-Commons wall (No input server) - OmicronSDK still handles screen scaling and fullscreen fix.
CHANGE: Legacy oinputserver now accepts a handshake of 'omega\_legacy\_data\_on' for clients that request a specific datagram format (OmegaLegacy, TouchAPI, etc.). NEW: OmicronAPI library for Java with Processing touch example and Javadocs.
CHANGE, BREAKING: Added Timer class to substitute the old StopWatch. Timer provides high resolution timings.
FIX: Error in color parser NEW: ologaddnewline function
FIX: misc fixes to Tcp support
CHANGE: TcpServer now derives from Service
CHANGE; Better omicron connector client example (Thanks to Luc Renambot)
CHANGE: Event and EventData refacoring to make omicronConnectorClient easier to use.
[New](New.md) OSCClient for CAVE2 audio testing. [New](New.md) ServiceType: Audio [Changed](Changed.md) OSCService handles AudioEvent->OSCMessage conversion and communication to audio server. OSCClient generates AudioEvents and inserts them into event list. [Changed](Changed.md) ...
FIX: TouchIDs are handled by TouchGestureManager if enabled. Otherwise PQService handles it like before. NEW: TouchGroups partially implemented. NEW: TouchGestureManager can be enabled/disabled from PQService configuration file.
FIX: Error correction accounts for missing touch down events. Still a problem with missing up events in SAGE. NEW: Migrating more of the gesture prototype into TouchGestureManager.
NEW: TouchGestureManager handles dropped touch up events. NEW: SAGEInputServer sends multi-user single-click and drags.
NEW: DirectXInputService button Up / Down events
NEW: DirectXInputService Xbox360 gamepad button mappings.
NEW: revised DirectXInputService (WIP)
NEW: Color supports string parsing with color names or hexadecimal values
NEW quaternion conversion to yaw pitch roll
NEW: OSCService connects to OSC server and can create OSC messages. NEW: TouchGestureManager added. CHANGE: PQLabs gestures are now completely disabled (most were broken anyway). FIX: Cleaned up warnings in DirectXService and PQService.
NEW: Setting constructor now public
NEW: support for absolute paths in FilesystemDataSource
NEW: Event::isButtonDown
NEW: Service type Wand and related changes.
NEW: Wiimote event source now customizable.
FIX: Event button3 code
FIX: ServiceManager event queue bug
FIX: Event ExtraData read incorrectly over network connection
NEW: Wiimote pointer emulation
FIX: NetService was not receiving Event flags.
UPDATE: vrpn.lib to release version. NEW: sageinputserver for streaming touch data to SAGE. Eventually can replace SAGE\_Touch app as well as a testbed for new touch gesture library.
NEW: SagePointerService now can force source id to all generated pointer events.
FIX: SagePointer used int instead of float for normalized positions
CHANGE: NetService now overwrites remote event service ids with its own.
NEW: Sage & WandService
FIX: update timer for WandService
FIX: missing extra data valid mask transmission in input server
FIX: oinputserver port is now configurable
NEW: wiimote & wand services (WIP)


---

# omicron v1.1 #
**Initial Revision**: 16
**Branch-out Revision**: 35
## Summary ##
> This is the first version to be released as a binary package too (windows only for now).
> The most important changes from 1.0 are the following:
    * omicron now supports a new binary event streaming protocol. The protocol is supported by `oinputserver` and `NetService` by default. The old string-based protocol is still available through `LegacyNetService` and `legacy-oinputserver`
    * we added **omicronConnector**. omicronConnector is a header-only library that allows C++ applications to easily connect to input server instances and receive events over a TCP/UDP connection.
    * a few utility methods have been added to the Config and ArgumentHelper APIs.
    * The implementation of reference counting and smart pointer support has been completed. This also allowed fixing a few memory leaks in the library.
## Change Log ##
  * NEW: Reference counting support
  * CHANGE: ArgumentHelper
  * CHANGE: ServiceManager event methods now public
  * NEW: Config::getVector2iValue
  * NEW vector3to2
  * NEW: Unity integration and demo
  * NEW: Config::getVector2fValue
  * NEW: Thread class, fixed setting custom output build directories
  * NEW: omicronConnectorClient
  * NEW: fixing netservice, new binary event protocol
## Bugfixes ##
  * FIX: linux NetService
  * FIX: Tcp connection polling
  * FIX: const correctness fixes
  * FIX: LegacyNetService was not registered
  * FIX: various memory leaks