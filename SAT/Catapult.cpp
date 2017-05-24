#include "Catapult.h"

Catapult::Catapult(int firePin, int armPin, int ballsPin, int platformPin) {
  fireServoPin = firePin;
  armServoPin = armPin;
  ballsServoPin = ballsPin;
  platformServoPin = platformPin;
  fireServo.attach(3);
  armServo.attach(5);
  ballServo.attach(6);
  platformServo.attach(9);
  
  
}

void Catapult::sweep (Servo servo, int originAngle, int destinationAngle, int speed) {
  int tempPosition = 0;

  if (originAngle >= destinationAngle) {
    for (tempPosition = originAngle; tempPosition >= destinationAngle; tempPosition--) {
      servo.write(tempPosition);
      delay(speed);
    }
  } else {
    for (tempPosition = originAngle; tempPosition <= destinationAngle; tempPosition++) {
      servo.write(tempPosition);
      delay(speed);
    }
  }
}



void Catapult::rest() {
  sweep(fireServo, fireServo.read(), releaseAngle, 15);
  sweep(armServo, armServo.read(), disarmedAngle, 15);
}

void Catapult::prepareToShoot() {
  sweep(fireServo, fireServo.read(), blockingAngle, 15) ;
  sweep(armServo, armServo.read(), armedAngle, 15) ;
}

void Catapult::shoot() {
  sweep(fireServo, fireServo.read(), releaseAngle, 15);
}

void Catapult::openGate() {
  sweep(ballServo, ballServo.read(), feedBalls, 22) ;
}

void Catapult::closeGate() {
  sweep(ballServo, ballServo.read(), stopBalls, 15) ;
}

void Catapult::feedBall() {
  openGate();
  closeGate();
  delay(2000);
}

void Catapult::stepScan(){
  if (currentScanDirection = 1){  
    sweep(platformServo, platformServo.read(),platformServo.read() + scanStep,  15);
  } else {
    sweep(platformServo, platformServo.read(),platformServo.read() - scanStep,  15);
  }
  if (platformServo.read() < startScanAngle ||platformServo.read() > endScanAngle){
    currentScanDirection = currentScanDirection * -1;
  }
}

