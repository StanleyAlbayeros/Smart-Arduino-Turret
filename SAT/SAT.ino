/////////////////////////////////////////////////////////////////////////////////////////////////////

/*choose either of both options when uploading the code to the respective board
 * There should be no need to use an external pullup resistor since we are only using two arduinos 
 */

#define slaveID 2

#define MASTER
//#define SLAVE
/////////////////////////////////////////////////////////////////////////////////////////////////////


#include <Servo.h>
#include <Wire.h>
#include "Catapult.h"
#include "Sensor.h"
#include "Display.h"



#ifdef MASTER
  #define firePin 3
  #define armPin 5
  #define ballsPin 6
  #define platformPin 9
#endif


#ifdef MASTER
  Catapult myCatapult(firePin,armPin,ballsPin,platformPin);    
  int currentCommand = 1;
  
#endif

#ifdef SLAVE
  Display myDisplay;  
  Sensor mySensor;
#endif

void setup() {
  
#ifdef MASTER
  Wire.begin();

  
  
  myCatapult.rest();
  myCatapult.closeGate();
  myCatapult.openGate();
  delay(500);
  
  //myCatapult.prepareToShoot();
  //myCatapult.shoot();
  //myCatapult.rest();

  
#endif

#ifdef SLAVE

  Wire.begin(slaveID);
  Serial.begin(9600);  
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestSensorData);
  


#endif

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

  
/////------------I2C MASTER CODE ----------------//////
  #ifdef MASTER
  
  Wire.beginTransmission(slaveID);
  int available = Wire.requestFrom(slaveID, (uint8_t)1);
  
  currentCommand = 1;
  Wire.write(currentCommand);
  
  if(available == 1)
  {
    int receivedValue = Wire.read();   
  Wire.endTransmission();
    if (receivedValue != 1){
      //scanning
    } else {
      //target found!
      currentCommand = 2;
  Wire.beginTransmission(slaveID);
      Wire.write(currentCommand);
  Wire.endTransmission();
       myCatapult.feedBall(); 
      // fire the ball
      myCatapult.prepareToShoot() ;  
      delay(2000);
      currentCommand = 4;
      
  Wire.beginTransmission(slaveID);
      Wire.write(currentCommand);
      myCatapult.shoot(); 
      myCatapult.rest(); 

      
    }
  }  
      delay(250);
      Wire.endTransmission();
/*
  Wire.beginTransmission(slaveID);
  currentCommand = 2;
  Wire.write(currentCommand);
  Wire.endTransmission();
  delay(4000);
*/

  //while no target
  //scan for targets
  //send slave display::scanning command
  //endwhile

  //target found
  //send slave display::targetaqcuired command
  //sleep
  //prepare to shoot
  //send slave display::preparing command
  
  //sleep
  //send slave display::shooting command
  //shoot


  
  #endif
  
/////------------I2C SLAVE CODE ----------------//////
  #ifdef SLAVE
    delay(100);

  #endif  
}


#ifdef SLAVE
int byteIndex = 1;

// SLAVE receive event
void receiveEvent(int howMany) {
  int x = Wire.read();    // receive byte as an integer

  switch (x){
    case 1: myDisplay.scanning();
    break;
    case 2: myDisplay.detected();
    break;
    case 3: myDisplay.preparing();
    break;
    case 4: myDisplay.shooting();
    break;
  }
}

//SLAVE request event

void requestSensorData(){
    if (mySensor.detectTarget(100)){
      Wire.write(1);
    } else {
      Wire.write(0);
    }
}

#endif  
