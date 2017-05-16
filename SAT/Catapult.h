#ifndef Catapult_h
#define Catapult_h

#include "Arduino.h"
#include <Servo.h>

class Catapult {

  public: 

    Catapult(int firePin, int armPin, int ballsPin, int platformPin);
    void Catapult::sweep (Servo servo, int originAngle, int destinationAngle, int speed);
    void Catapult::rest();
    void Catapult::prepareToShoot();
    void Catapult::shoot();
    void Catapult::openGate();
    void Catapult::closeGate();
    void Catapult::feedBall();
    

  private:
    int fireServoPin;
    int armServoPin;
    int ballsServoPin;
    int platformServoPin;
    Servo platformServo;
    Servo ballServo;
    Servo fireServo;
    Servo armServo;
    const int releaseAngle  = 100;
    const int blockingAngle = 20;  
    const int armedAngle    = 50;
    const int disarmedAngle = 140;   
    const int feedBalls     = 155;
    const int stopBalls     = 175;
};

#endif
