# Smart Arduino Turret

The scope of this project is to take [instructables user avi_o's simple arduino robot catapult](https://www.instructables.com/id/Arduino-Robot-Catapult/) and put some brains in it so it can do it's own thing.
***
I'll be using an ultrasonic sensor, a display and two arduino boards to achieve this. Did I say two arduino boards? Yes, two! I'll be implementing I2C communication between two boards that will be in charge of controlling the whole robot. The I2C master board will take control of the ultrasound sensor and the display, and will relay orders to the slave to shoot targets detected by the sensor. 