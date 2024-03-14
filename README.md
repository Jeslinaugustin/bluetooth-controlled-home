# bluetooth-controlled-home
A Simple Bluetooth controlled home using arduino

This project is intended to show, how Bluetooth module can be connected to arduino and it can communicate with other devices.

Here, three different LEDs (indicates bulb, heater and ac) are connected to the arduino, which is controlled by a Android application installed in user’s device. The communication between the two devices is established by using Bluetooth.

A membrane keypad is connected to arduino indicating door lock. The system, allows the user to set the password using the mobile application.

To run this code, the libraries for keypad and servo motor needs to be installed first.

The mobile application used here is a custom application developed by using MIT App inventor. 

Procedure:
Install the libraries and load the code to the arduino.
Install the application to the android device using the apk file provided 
Pair the HC-06 module with the android device
To use the application, first connect it with the HC-06 module using the conncet button in the app. 
