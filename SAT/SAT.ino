/////////////////////////////////////////////////////////////////////////////////////////////////////

/*choose either of both options when uploading the code to the respective board
 * There should be no need to use an external pullup resistor since we are only using two arduinos 
 */

#define MASTER
//#define SLAVE
/////////////////////////////////////////////////////////////////////////////////////////////////////


#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Catapult.h"
#include "Sensor.h"
#include "Display.h"

static const uint8_t slaveID = 2;

#ifdef MASTER

  #define firePin 3
  #define armPin 5
  #define ballsPin 6
  #define platformPin 0
  
  Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver();
  Catapult myCatapult(servos, firePin,armPin,ballsPin,platformPin);    
  int currentCommand = 1;
    
#endif

#ifdef SLAVE
  #define detectionDistance 75
  Display myDisplay;  
  Sensor mySensor;

#endif

void setup() {
  
#ifdef MASTER
  //Serial.begin(9600); 
  servos.begin();
  
  servos.setPWMFreq(50);
  
  myCatapult.rest(servos);
  delay(500);
  //myCatapult.feedBall(servos);
  
#endif

#ifdef SLAVE

  Wire.begin(slaveID);
  Serial.begin(9600);  
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestSensorData);

#endif
}

void loop() {

  
/////------------I2C MASTER CODE ----------------//////
  #ifdef MASTER
  Wire.beginTransmission(slaveID);
  int available = Wire.requestFrom(slaveID, (uint8_t)1);
  
  currentCommand = 1;
  Wire.write(currentCommand);
  
  if(available == 1)  
  if(true)
  {
    int receivedValue = Wire.read();   
  Wire.endTransmission();
    if (receivedValue != 1){
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
    if (mySensor.detectTarget(detectionDistance)){
      Wire.write(1);
    } else {
      Wire.write(0);
    }
}

#endif  

