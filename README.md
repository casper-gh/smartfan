
#Extremely Simple ESP6288 SmartThings Blinds

This is my attempt to control window blinds in SmartThings with a NodeMCU ESP8266 chip, and a servo. And while I know there is more elaborate solutions and implementations with SmartThings-MQTT Bridges and such, I was trying to keep this as simplistic, cheap, and zero-maintenance as possible.

While I am using the NodeMCU board, this <i>should</i> work on just about any ESP8266 based board...

Image Gallery: http://imgur.com/a/WZmPM

Servo Shaft Couplers (the easiest way to connect your servo in-place of the blinds tilt gearbox and thus hide the servo, board, and cords in the blinds upper housing) can be found here: https://www.servocity.com/html/servo_to_shaft_couplers.html

This is a fork of user casper-gh's smartfan code that can be found here: https://github.com/casper-gh/smartfan

Pieces of the Arduino sketch were cherry-picked from: 
* http://randomnerdtutorials.com/esp8266-remote-controlled-sockets/
* http://www.bruhautomation.com/p/cheapest-wifi-automated-blinds.html
* https://www.arduino.cc/en/Tutorial/Sweep
