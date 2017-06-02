#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Sensor.h"
#include "Display.h"

static const uint8_t slaveID = 2;

  #define detectionDistance 75
  Display myDisplay;  
  Sensor mySensor;

void setup() {
  
  Wire.begin(slaveID);
  Serial.begin(9600);  
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestSensorData);
}

void loop() {
  delay(100);
}

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


