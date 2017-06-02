#include "Sensor.h"

/* Using cpp's initialization lists, we can have a private object from
   the ultrasonic class, which doesn't have a default constructor, and
   initialize it properly in an initialization list
*/

//Initializes a sensor object with default pins trigger:3 and echo:2
Sensor::Sensor(): mySensor(DEFAULT_TRIGGER_PIN, DEFAULT_ECHO_PIN) {

}

//Initializes a sensor object with an available ultrasonic object
Sensor::Sensor(Ultrasonic mySensor): mySensor(mySensor) {
}

//Initializes a sensor object with the specified trigger and echo pins
Sensor::Sensor(int triggerPin, int echoPin): mySensor(triggerPin, echoPin) {
}

bool Sensor::detectTarget(int range) {
  int avgCount = 5;
  int tempDistance = 0;
  //reads distance in centimeters
  for (uint8_t i = 0; i < avgCount; i++) {
    tempDistance += mySensor.distanceRead(CM);
  }
  int distance = floor (tempDistance / avgCount);
  //maps the distance and desired range to a shorter of numbers
  uint8_t distanceMap = map(distance, 0, 250, 0, 100);
  uint8_t rangeMap = map(range, 0, 250, 0, 100);

  //returns true if the sensor detects an object within the set range
  if (distanceMap <= rangeMap) {
    return true;
  }
  return false;
}

uint8_t Sensor::getDistanceMap() {
  return map(mySensor.distanceRead(CM), 0, 250, 0, 100);
}


