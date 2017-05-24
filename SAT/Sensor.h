#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include <Ultrasonic.h>

#define DEFAULT_TRIGGER_PIN 3
#define DEFAULT_ECHO_PIN 2

    
class Sensor {

  public:
    Sensor();
    Sensor(Ultrasonic mySensor);
    Sensor(int triggerPin, int echoPin);
    bool Sensor::detectTarget(int range);
    uint8_t getDistanceMap();

  private:
    Ultrasonic mySensor;
};

#endif
