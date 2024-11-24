# Arduino USB DInput Gamepad Controller for Xbox Adaptive Controller

This has only been tested on a Arduino Leonardo board. But it should work
Arduino Pro Micro and Arduino Micro because they all have the same
microcontroller.

The gamepad has the following controls.

|Control |Description
|--------|---------------
|X       |8 bits, 0..255, left stick
|Y       |8 bits, 0..255, left stick
|Z       |8 bits, 0..255, right stick
|RZ      |8 bits, 0..255, right stick
|Hat     |8 way hat switch/direction pad
|Buttons |12 buttons

The HID report has been carefully chosen so it works with the Xbox Adaptive
Controller (XAC). The X,Y axes map to the XAC left joystick. The Z,RZ
axes map to the XAC right joystick. The hat switch maps to the XAC dpad.
The buttons map to XAC buttons.

The XAC firmware must be updated to the June 2024 version or newer for all
features to work. Use the Xbox Accessory app to update the firmware. The app
runs on Xbox console and Windows.

Install this library by downloading a zip file from this repo. Use the IDE
"Add .ZIP library" option.

## Button Mapping

The XAC default button mapping for external USB joystick buttons is unexpected.
See this video on how map buttons so they are useful.

https://www.youtube.com/watch?list=PLGr-X28QXcrsVR17qugfIKH1C1aAaD5yM&v=gm4w4qXaDm8
