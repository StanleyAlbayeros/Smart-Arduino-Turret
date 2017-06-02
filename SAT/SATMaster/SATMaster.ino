#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Catapult.h"

static const uint8_t slaveID = 2;
#define firePin 3
#define armPin 5
#define ballsPin 6
#define platformPin 0

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver();
Catapult myCatapult(servos, firePin, armPin, ballsPin, platformPin);
int currentCommand = 1;

void setup() {

  servos.begin();
  servos.setPWMFreq(50);
  myCatapult.rest(servos);
  delay(500);

}

void loop() {

  Wire.beginTransmission(slaveID);
  int available = Wire.requestFrom(slaveID, (uint8_t)1);
  currentCommand = 1;
  Wire.write(currentCommand);

  if (available == 1)
    if (true)
    {
      int receivedValue = Wire.read();
      Wire.endTransmission();
      if (receivedValue != 1) {
        //scanning
        myCatapult.stepScan(servos);
      } else {
        //target found!
        currentCommand = 2;
        Wire.beginTransmission(slaveID);
        Wire.write(currentCommand);
        delay(500);
        Wire.endTransmission();
        myCatapult.feedBall(servos);
        myCatapult.prepareToShoot(servos) ;
        delay(2000);
        currentCommand = 4;

        Wire.beginTransmission(slaveID);
        Wire.write(currentCommand);
        delay(500);
        myCatapult.shoot(servos);
        myCatapult.rest(servos);
      }
    }
  delay(100);
  Wire.endTransmission();
}
