#include <Servo.h>

Servo platformServo;
Servo ballServo;
Servo fireServo;
Servo armServo;

#define releaseAngle  100
#define blockingAngle 20

#define armedAngle    50
#define disarmedAngle 140

#define feedBalls     155
#define stopBalls     175

void setup() {

  //attach the servos to their pins
  fireServo.attach(3); 
  armServo.attach(5); 
  ballServo.attach(6);
  platformServo.attach(9);

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

}

void loop() {

}

void sweep (Servo servo, int originAngle, int destinationAngle, int speed){
  int tempPosition = 0;

   if (originAngle >= destinationAngle){
    for (tempPosition = originAngle; tempPosition >= destinationAngle; tempPosition--){
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



void rest(){
  sweep(fireServo, fireServo.read(), releaseAngle,15);
  sweep(armServo, armServo.read(), disarmedAngle, 15);
}

void prepareToShoot(){  
  sweep(fireServo,fireServo.read(),blockingAngle,15) ; 
  sweep(armServo,armServo.read(),armedAngle,15) ; 
}

void shoot(){
  sweep(fireServo, fireServo.read(), releaseAngle, 15);
}

void openGate(){
  sweep(ballServo,ballServo.read(),feedBalls,22) ; 
}

void closeGate(){
  sweep(ballServo,ballServo.read(),stopBalls,15) ; 
}

void feedBall(){
  openGate();
  closeGate();
  delay(2000);  
}

