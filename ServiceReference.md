<p><b>Last revision:</b> ver. 1.3 - 13 March 2013</p>

# omicron Event Services reference #
This place lists all the event services shipped with omicron, together with their supported configuration options.


---

## BasicPortholeService ##
**main class:** [omicron::BasicPortholeService](http://omegalib.googlecode.com/svn/refdocs/trunk/html/classomicron_1_1_basic_porthole_service.html)
Interfaces omicron with tablets running the Porthole application. Porthole is a prototype application for controlling VR application through tablet devices. This service is reimplemented in omegalib to offer advanced functionalities like picture streaming and dynamic gui generation.

### Generated events ###
  * **Service type:** Tablet, Ui
  * **Event types:** Move, Up, Down, Zoom, Rotate
  * **Event data fields:** position, extra data (int array), flags
The service returns pointer events like a mouse (with flags for left/right click). The position is in normalized coordinates (0.0 to 1.0). The service also returns Ui type events when the user interacts with gui elements in the porthole application. The extra data int array contains the id of the ui control at index 0.

### Configuration parameters ###
  * `port (integer)`: the listening port for the service (default: 3490)


---

## DirectInputService ##
  * **Deprecated**
This has been replaced by XInputService.
Uses the Microsoft DirectInput component of the DirectX API to access game controllers. Supports Xbox 360 controllers using the USB Xbox360 Wireless Receiver for Windows and PlayStation 3 Sixaxis, Move, and Navigation Controllers via bluetooth and MotioninJoy.

### Generated events ###
  * **Service type:** Controller
  * **Event types:** `Update`, `Down`, `Up`
  * **Event data fields:** flags for digital buttons and extra data (float array) for analog inputs

#### Common Analog Fields ####
These fields are the same for Xbox 360 and PS3 controllers. These floats are normalized (0.0 to 1.0) or (-1.0 to 0.0) depending which axis the data corresponds to.
The PS3 Navigation controller uses the left analog stick and left analog trigger.

  * ExtraDataFloat 0: Left Analog Stick (-left, +right)
  * ExtraDataFloat 1: Left Analog Stick (-up, +down)
  * ExtraDataFloat 2: Right Analog Stick (-left, +right)
  * ExtraDataFloat 3: Right Analog Stick (-up, +down)
  * ExtraDataFloat 4: Analog Trigger (+left, -right)

#### PS3 Controller Specific Fields ####
The following button flags correspond to PS3 controller buttons. Some controllers such as the Move or Navigation may not have all buttons available.
  * Button 1: Triangle
  * Button 2: Circle
  * Button 3: Cross
  * Button 4: Square
  * Button 5: Left Shoulder Button (L1)
  * Button 6: Left Analog Stick Button (L3)
  * Special Button 1: Select
  * Special Button 2: Start
  * Special Button 3: PS Button

  * ExtraDataFloat 4: Analog Trigger (L2) (+left, -right)

#### Xbox360 Controller Specific Fields ####
The following button flags correspond to Xbox360 controller buttons.
  * Button 1: A
  * Button 2: B
  * Button 3: X
  * Button 4: Y
  * Button 5: Left Shoulder Button (LB)
  * Button 6: Right Shoulder Button (RB)
  * Special Button 1: Back
  * Special Button 2: Start
  * Special Button 3: Not Currently Assigned

  * ExtraDataFloat 4: Analog Trigger (LT) (0.0 to 1.0)
  * ExtraDataFloat 4: Analog Trigger (RT) (-1.0 to 0.0)

### Configuration parameters ###
  * `updateInterval (float)`: the delay time in seconds between polling for new data (default: 0.01)
  * `checkControllerInterval (float)`: the delay time in seconds between checking for new controllers (default: 2.0)


---

## HeartbeatService ##
A simple service that generates periodic events. Used to test connections and as a skeleton for implementation of new event services.

### Generated events ###
  * **Service type:** Generic
  * **Event types:** `Update`
  * **Event data fields:** position, orientation.

Position and orientation contain an increasing event sequence number pls a floating point offset. This is used to test the correctness of event streaming modules like oinputserver and omicronConnector. The structure of the data is as follows:
  * position[0](0.md) = sequence number
  * position[0](0.md) = sequence number + 0.1
  * position[0](0.md) = sequence number + 0.2
  * orientation[0](0.md) = sequence number + 0.3
  * orientation[0](0.md) = sequence number + 0.4
  * orientation[0](0.md) = sequence number + 0.5
  * orientation[0](0.md) = sequence number + 0.6

### Configuration parameters ###
  * `rate (float)`: the number of events per seconds that the service will generate


---

## LegacyDirectInputService ##
  * **Deprecated**
This is the old implementation of a controller service supporting XBox and wiimote
controllers. It is kept for compatiility reasons. Use `DIrectXInputService` or `WiimoteService` if you need X360 gamepad or wiimote support.


---

## LegacyNetService ##
  * **Deprecated**
Connects to an legacy omicron input server instance to receive remote events.

This service uses a text-based protocol to stream event data. It supports a limited range of input services. It is kept for compatibility reasons but it should not be used in new applications.


---

## NaturalPointService ##
### Generated events ###
#### Description ####
### Configuration parameters ###


---

## NetService ##
Connects to an omicron input server instance to receive remote events.
### Generated events ###
The events depend on the remote services active on the input server. The only change is the
**service id** of th event, which is substituted with the local `NetService` service id.
This is done because in the local context, remote service ids have no meaning, so all events are marked as being originated from `NetService`.

### Configuration parameters ###
  * `serverIP (string)`: the name or ip address of the input server (default: localhost)
  * `msgPort (int)`: the tcp port to use for the initial handshake and reliable message passing (default: 27000)
  * `dataPort (int)`: the udp port to use for general event passing (default: 7000)


---

## OpenNIService ##
### Generated events ###
#### Description ####
### Configuration parameters ###


---

## OptiTrackService ##
### Generated events ###
#### Description ####
### Configuration parameters ###


---

## PQService ##
Uses the PQLabs API to connect and receive touch data from a PQLabs server (MultiTouchPlatform). Can be combined with the GestureManager to generate more accurate touch point events as well as basic multi-touch gestures like pan and zoom.

### Generated events ###
  * **Service type:** Pointer
  * **Event types:** `Down`, `Move`, `Up`
  * **Event data fields:** position, extra data (float array) for touch width and height.

### Configuration parameters ###
  * `serverIP (string)`: the name or ip address of the PQLabs server (default: localhost)
  * `maxBlobSize (int)`: the largest pixel diameter of touches to be reported (default: 1000)
  * `screenX (int)`: the x resolution to expand normalized touch data. If 0, the resolution of the PQLabs server will be used. If 1, the data will be normalized (0.0 to 1.0). (default: 0)
  * `screenY (int)`: the y resolution to expand normalized touch data. If 0, the resolution of the PQLabs server will be used. If 1, the data will be normalized (0.0 to 1.0). (default: 0)
  * `screenOffsetX (int)`: the offset in pixels in the x direction. (default: 0)
  * `screenOffsetY (int)`: the offset in pixels in the y direction. (default: 0)
  * `useGestureManager (bool)`: toggle the Gesture Manager. (default: false)


---

## SagePointerService ##
### Generated events ###
#### Description ####
### Configuration parameters ###


---

## TcpServer ##
Implements a tcp server that listens for incoming tcp connections. This is just a base class for other services that need to use tcp. `TcpServer` generates no events and has no configuration parameters.


---

## ThinkGearService ##
Uses the ThinkGear NeuroSky API to access MindWave EEG data.

### Generated events ###
  * **Service type:** Brain
  * **Event types:** `Update`
  * **Event data fields:** extra data (float array) for EEG values described below.

#### Extra Data Fields ####
Signal strength ranges from 0-200 while attention/meditation from 0-100. All other values can vary from 0 to over 100,000,000 depending on the wave.
Signal strength of 200 typically means the headset is not current worn, values 50-25 indicates one of the contacts (forehead or ear) is not properly set.

  * ExtraDataFloat 0: Signal strength (200 - no signal, 50-25 - parital signal, 0 - full signal)
  * ExtraDataFloat 1: Attention (0-20 'strongly lowered', 20-40 'reduced', 40-60 'neutral', 60-80 'slightly elevated', 80 - 100 'elevated')
  * ExtraDataFloat 2: Meditation (0-20 'strongly lowered', 20-40 'reduced', 40-60 'neutral', 60-80 'slightly elevated', 80 - 100 'elevated')
  * ExtraDataFloat 3: Delta waves (Deep, dreamless sleep, non-REM sleep, unconscious)
  * ExtraDataFloat 4: Theta waves (Intuitive, creative, recall, fantasy, imaginary, dream)
  * ExtraDataFloat 5: Low alpha waves (Relaxed, but not drowsy, tranquil, conscious)
  * ExtraDataFloat 6: High alpha waves (Relaxed, but not drowsy, tranquil, conscious)
  * ExtraDataFloat 7: Low beta waves (Formerly SMR, relaxed yet focused, integrated)
  * ExtraDataFloat 8: High beta waves (Thinking, aware of self & surroundings, Alertness, agitation)
  * ExtraDataFloat 9: Low gamma waves
  * ExtraDataFloat 10: High gamma waves
  * ExtraDataFloat 11: Blink strength (Blinks typically register around values of 100 or greater)

### Configuration parameters ###
  * `comPortName (string)`: com port the MindWave Wireless USB Adapter is connected to (default: "\\\\.\\COM10")
  * `enableStreamLog (bool)`: enable stream logging to streamLog.txt (default: false)
  * `enableDataLog (bool)`: enable data logging to dataLog.txt (default: false)
  * `baudRate (int)`: sets the connection baud rate (1200, 2400, 4800, 9600, 57600, or 115200) (default: 4800)


---

## VRPNDevice ##
This creates a VRPN server to stream controller events as a VRPN Input Gamepad. This is currently part of the oinputserver application and not yet an independent service.
This is exclusively used to send controller/wand events to CalVR.

### VRPN Gamepad Mapping from Omicron Controller/Wand Event ###
The following Omicron controller/wand event mapping to VRPN Gamepad was designed to easily convert from CalVR's gyromouse button mapping to using the PlayStation Navigation controller's buttons.
Having Omicron Button 6 and 7 mapped to Button 2 allows for the analog button to emulate the middle mouse button and allow analog trigger L2 to function for CalVR navigation.

  * Channel 0: Omicron ExtraDataFloat 0: Left Analog Stick (-left, +right)
  * Channel 1: Omicron ExtraDataFloat 1: Left Analog Stick (-up, +down)
  * Button 0: Omicron Button 3 (PS Navigation Cross button emulating 'left mouse button')
  * Button 1: Omicron Button 2 (PS Navigation Circle button emulating 'right mouse button')
  * Button 2: Omicron Button 6 and Omicron Button 7 (PS Navigation Analog button and L2 trigger emulating 'middle mouse button')
  * Button 3: Omicron Button Up
  * Button 4: Omicron Button Down
  * Button 5: Omicron Button Left
  * Button 6: Omicron Button Right

### Configuration parameters ###
  * `serverPort (int)`: Port number VRPN clients will connect to
  * `vrpnTrackerName (string)`: Device name client will use to get the device data
  * `vrpnTrackerPort (int)`: Port client will use to get the device data


---

## VRPNService ##
This service connects to a VRPN server and generates mocap events.

### Generated events ###
  * **Service type:** Mocap
  * **Event types:** `Update`
  * **Event data fields:** position and orientation

### Configuration parameters ###
  * `updateInterval (float)`: the delay time in seconds between polling for new data (default: 0.01)
  * `serverIP (string)`: IP address of the VRPN server
  * `trackedObjects`: A list of VRPN objects to get data from:
  * Example
```
VRPNService:
{
	serverIP = "localhost"; // This is the IP of all trackable objects below, unless marked otherwise
	trackedObjects:
	{
		Head_Tracker: // Unique name for this list
		{
			name = "Head_Tracker"; // The VRPN name of the object
			trackableID = 0; // The ID this object will be associated with
			
			// Optional: The IP address of the VRPN server for this object if different from above
			serverIP = "localhost"; 
		};
	};
};
```


---

## WandService ##
This service takes data coming from a Mocap and a Controller service and merges it into a single Wand type event.

In a VR system, we may want to use a controller (like a wiimote or PS3 move) as a wand device for pointing and selection. To do this, set of markers is usually attached to the device to perform 3d tracking. This means we have two separate input systems used to implement a wand (the gamepad and the 3d tracker). `WandService` joins these two systems into a logical wand, with its own stream of input events. This way, applications don't have to keep track of two separate streams of events to implement wand logic.

### Generated events ###
  * **Service type:** Wand
  * **Event types:** Same as source controller events (Usually `Up`, `Down`, `Update`)
  * **Event data fields:** position, orientation, plus anything coming from controller source ( usually flags for digital buttons and extra data (float array) for analog inputs)

#### Description ####
The event is the same as what is generated by the controller source (check the guide for the controller service you are using), plus position and orientation data coming from the mocap service.

### Configuration parameters ###
  * `debug (bool)`: enables debug mode
  * `raySourceId (int)`: the source id for mocap events to use as the wand device
  * `controllerService (string)`: the name of the service generating the controller events
  * `controllerSourceId (int)`: the source id of the controller to use as the wand device


---

## WiimoteService ##
### Generated events ###
#### Description ####
### Configuration parameters ###


---

## XInputService ##
Uses the Microsoft XInput API to access game controllers. Supports Xbox 360 controllers using the USB Xbox360 Wireless Receiver for Windows and PlayStation 3 Sixaxis, Move, and Navigation Controllers via bluetooth and MotioninJoy (Using the Xbox 360 emulator).

### Generated events ###
  * **Service type:** Controller
  * **Event types:** `Update`, `Down`, `Up`
  * **Event data fields:** flags for digital buttons and extra data (float array) for analog inputs

#### Common Analog Fields ####
These fields are the same for Xbox 360 and PS3 controllers. These floats are normalized (0.0 to 1.0) or (-1.0 to 0.0) depending which axis the data corresponds to.
The PS3 Navigation controller uses the left analog stick and left analog trigger.

  * ExtraDataFloat 0: Left Analog Stick (-left, +right)
  * ExtraDataFloat 1: Left Analog Stick (-up, +down)
  * ExtraDataFloat 2: Right Analog Stick (-left, +right)
  * ExtraDataFloat 3: Right Analog Stick (-up, +down)
  * ExtraDataFloat 4: Analog Trigger (+left, -right)

#### PS3 Controller Specific Fields ####
The following button flags correspond to PS3 controller buttons. Some controllers such as the Move or Navigation may not have all buttons available.
  * Button 1: Triangle
  * Button 2: Circle
  * Button 3: Cross
  * Button 4: Square
  * Button 5: Left Shoulder Button (L1)
  * Button 6: Left Analog Stick Button (L3)
  * Button 7: Left Analog Trigger ( Value > 0.5 ) (L2)
  * Special Button 1: Not Currently Assigned
  * Special Button 2: Not Currently Assigned
  * Special Button 3: Not Currently Assigned

  * ExtraDataFloat 4: Left Analog Trigger (L2) (+left, -right)

#### Xbox360 Controller Specific Fields ####
The following button flags correspond to Xbox360 controller buttons.
  * Button 1: Y
  * Button 2: B
  * Button 3: A
  * Button 4: X
  * Button 5: Left Shoulder Button (LB)
  * Button 6: Left Thumb Button
  * Button 7: Left Analog Trigger ( Value > 0.5 ) (L2)
  * Special Button 1: Not Currently Assigned
  * Special Button 2: Not Currently Assigned
  * Special Button 3: Not Currently Assigned

  * ExtraDataFloat 4: Left Analog Trigger (LT) (0.0 to 1.0)
  * ExtraDataFloat 4: Right Analog Trigger (RT) (-1.0 to 0.0)

### Configuration parameters ###
  * `updateInterval (float)`: the delay time in seconds between polling for new data (default: 0.01)
  * `checkControllerInterval (float)`: the delay time in seconds between checking for new controllers (default: 2.0)


---
