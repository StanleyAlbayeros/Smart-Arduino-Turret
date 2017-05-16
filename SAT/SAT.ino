#include <Servo.h>
#include "Catapult.h"

#define firePin 3
#define armPin 5
#define ballsPin 6
#define platformPin 9

Catapult myCatapult(firePin,armPin,ballsPin,platformPin);

void setup() {


  myCatapult.rest();
  myCatapult.closeGate();
  myCatapult.openGate();
  delay(2500);
  myCatapult.prepareToShoot();
  myCatapult.shoot();
  myCatapult.rest();
  
/*

  // take the firing arm to it's resting position
  rest();
  
  //load a ball into the catapult
  closeGate();   
  delay(2500);
  feedBall(); 
  // fire the ball
  prepareToShoot() ;  
  shoot(); 
  rest(); 
*/
}

void loop() {

}


