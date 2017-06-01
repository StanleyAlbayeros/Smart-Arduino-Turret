#include "Catapult.h"

Catapult::Catapult(Adafruit_PWMServoDriver &servoDriver, int firePin, int armPin, int ballsPin, int platformPin) {
  fireServoID = firePin;
  armServoID = armPin;
  ballServoID = ballsPin;
  platformServoID = platformPin;
  /*
    fireServo.attach(3);
    armServo.attach(5);
    ballServo.attach(6);
    platformServo.attach(9);
  */
}

void Catapult::sweep (Adafruit_PWMServoDriver &servoDriver,int servoID, int originPulse, int destinationPulse, int speed) {
  int tempPulse = 0;
  
     //servoDriver.setPWM(servoID, 0, destinationPulse);
  if (originPulse >= destinationPulse) {
    for (tempPulse = originPulse; tempPulse >= destinationPulse; tempPulse--) {
      servoDriver.setPWM(servoID, 0, tempPulse);
      //servo.write(tempPosition);
      delay(speed);
    }
  } else {
    for (tempPulse = originPulse; tempPulse <= destinationPulse; tempPulse++) {
      servoDriver.setPWM(servoID, 0, tempPulse);
      //servo.write(tempPosition);
      delay(speed);
    }
  }
}



void Catapult::rest(Adafruit_PWMServoDriver &servoDriver) {
  sweep(servoDriver, fireServoID, currentFireServoPulse, releasePulse, 5);
  currentFireServoPulse = releasePulse;
  sweep(servoDriver, armServoID, currentArmServoPulse, disarmedPulse, 5);
  currentArmServoPulse = disarmedPulse;
}

void Catapult::prepareToShoot(Adafruit_PWMServoDriver &servoDriver) {
  sweep(servoDriver, fireServoID, currentFireServoPulse, blockingPulse, 5) ;
  currentFireServoPulse = blockingPulse;
  sweep(servoDriver, armServoID, currentArmServoPulse, armedPulse, 5) ;
  currentArmServoPulse = armedPulse;
}

void Catapult::shoot(Adafruit_PWMServoDriver &servoDriver) {
  sweep(servoDriver, fireServoID, currentFireServoPulse, releasePulse, 5);
  currentFireServoPulse = releasePulse;
}

void Catapult::openGate(Adafruit_PWMServoDriver &servoDriver) {
  sweep(servoDriver, ballServoID, currentBallServoPulse, feedBalls, 0) ;
  currentBallServoPulse = feedBalls;
}

void Catapult::closeGate(Adafruit_PWMServoDriver &servoDriver) {
  sweep(servoDriver, ballServoID, currentBallServoPulse, stopBalls, 0) ;
  currentBallServoPulse = stopBalls;
}

void Catapult::feedBall(Adafruit_PWMServoDriver &servoDriver) {
  openGate(servoDriver);
  delay(0);
  closeGate(servoDriver);
}

void Catapult::stepScan(Adafruit_PWMServoDriver &servoDriver) {
  /*
    Serial.print("Current dir: "); 
    Serial.print(currentScanDirection);
    */
  if (currentScanDirection == 1) {
    /*
    Serial.print("  dir 1 - current: ");
    Serial.print(currentPlatformServoPulse);
    Serial.print(" to: ");
    Serial.print(currentPlatformServoPulse + scanStep);
    */
    sweep(servoDriver, platformServoID, currentPlatformServoPulse, currentPlatformServoPulse + scanStep,  15);
    currentPlatformServoPulse = currentPlatformServoPulse + scanStep;
  } else if (currentScanDirection == -1) {
    /*
    Serial.print(" dir -1 - current: ");
    Serial.print(currentPlatformServoPulse);
    Serial.print(" to: ");
    Serial.print(currentPlatformServoPulse - scanStep);
    */
    sweep(servoDriver, platformServoID, currentPlatformServoPulse, currentPlatformServoPulse - scanStep,  15);
    currentPlatformServoPulse = currentPlatformServoPulse - scanStep;
  }
  
  if (currentPlatformServoPulse <= startScanPulse){
    /*
    Serial.print(" change  dir to 1 ");
    */
    currentScanDirection = 1;
    //sweep(servoDriver, platformServoID, currentPlatformServoPulse, startScanPulse + scanStep,  15);
    //currentPlatformServoPulse = startScanPulse + scanStep;
  } else if (currentPlatformServoPulse >= endScanPulse) {
    /*
    Serial.print(" change  dir to -1 ");
    */
    currentScanDirection = -1;
    //sweep(servoDriver, platformServoID, currentPlatformServoPulse, endScanPulse - scanStep,  15);
    //currentPlatformServoPulse = endScanPulse - scanStep;
  }

  //Serial.println(currentPlatformServoPulse);
  return currentPlatformServoPulse;
}


