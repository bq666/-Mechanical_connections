/* This example shows how to use the AMIS-30543 stepper motor
driver with the AccelStepper library.

You will need to install the AccelStepper library for this
example to work.  Documentation and installation instructions for
the AccelStepper library are available here:

    http://www.airspayce.com/mikem/arduino/AccelStepper/

Before using this example, be sure to change the
setCurrentMilliamps line to have an appropriate current limit for
your system.  Also, see this library's documentation for
information about how to connect the driver:

    http://pololu.github.io/amis-30543-arduino/
*/

#include <SPI.h>
#include <AMIS30543.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

const uint8_t amisDirPinW = 2;
const uint8_t amisStepPinW = 3;
const uint8_t amisSlaveSelectW = 4;


const uint8_t amisDirPinS = 10;
const uint8_t amisStepPinS = 9;
const uint8_t amisSlaveSelectS = 5;


const uint8_t outDirPin = 7;
const uint8_t outStepPin = 8;

AMIS30543 stepperW;
AMIS30543 stepperS;

AccelStepper inStepper(AccelStepper::DRIVER, amisStepPinW, amisDirPinW);
AccelStepper midStepper(AccelStepper::DRIVER, amisStepPinS, amisDirPinS);
AccelStepper outStepper(AccelStepper::DRIVER, outStepPin, outDirPin);

MultiStepper steppers;


void setup()
{
  SPI.begin();
  stepperW.init(amisSlaveSelectW);
  stepperS.init(amisSlaveSelectS);
  delay(1);

  stepperW.resetSettings();
  stepperW.setCurrentMilliamps(1900);
  stepperW.setStepMode(32);
  stepperW.enableDriver();

  stepperS.resetSettings();
  stepperS.setCurrentMilliamps(2000);
  stepperS.setStepMode(64);
  stepperS.enableDriver();
  
  
  inStepper.setMaxSpeed(4000.0);
  inStepper.setAcceleration(1.0);

  midStepper.setMaxSpeed(4000.0);
  midStepper.setAcceleration(1);

  outStepper.setMaxSpeed(4000.0);
  outStepper.setAcceleration(1.0);

  steppers.addStepper(inStepper);
  steppers.addStepper(midStepper);
  steppers.addStepper(outStepper);
  
  Serial.begin(9600);
  
  
}


  int L1 = 100;
  int L2 = 150;
//  float L3 = 50; 

//  int x = 0;
//  int y = 0;

  int x2 = 0; //215;
  int y2 = 0;
  
  float Q1 = 0;
  float Q2 = 0;



  

void loop(){
  long positions[3];
  positions[2] = 0; 
  

  x2 = 230;
  y2 = 60;
  Q2 = (acos(float((pow(x2, 2) + pow(y2, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2))))*(180/PI);
  Q1 = (atan(float(y2)/float(x2))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
  positions[0] = (long(Q1) * 12800) / 360; //12800 / 2;
  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
  PrintParm(positions);
  delay(100);
  
  x2 = 230;
  y2 = 90;
  Q2 = (acos(float((pow(x2, 2) + pow(y2, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2))))*(180/PI);
  Q1 = (atan(float(y2)/float(x2))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
  positions[0] = (long(Q1) * 12800) / 360; //12800 / 2;
  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
  PrintParm(positions);
  delay(100);

  x2 = 80;
  y2 = 90;
  Q2 = (acos(float((pow(x2, 2) + pow(y2, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2))))*(180/PI);
  Q1 = (atan(float(y2)/float(x2))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
  positions[0] = (long(Q1) * 12800) / 360; //12800 / 2;
  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
  PrintParm(positions);
  delay(100);

  x2 = 80;
  y2 = 60;
  Q2 = (acos(float((pow(x2, 2) + pow(y2, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2))))*(180/PI);
  Q1 = (atan(float(y2)/float(x2))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
  positions[0] = (long(Q1) * 12800) / 360; //12800 / 2;
  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
  PrintParm(positions);
  delay(100);

  Serial.println("----------------------------");
//  x2 = 230;
//  y2 = 60;
//  Q2 = (acos(float((pow(x2, 2) + pow(y2, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2))))*(180/PI);
//  Q1 = (atan(float(y2)/float(x2))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
//  positions[0] = (long(Q1) * 12800) / 360; //12800 / 2;
//  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
//  steppers.moveTo(positions);
//  steppers.runSpeedToPosition();
//  delay(1000);
  
  
//  Q2 = (acos(float((pow(x2, 2) + pow(y2, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2))))*(180/PI);
//  Q1 = (atan(float(y2)/float(x2))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
//
//  
//  long positions[3];
//  positions[0] = 0;
//  positions[1] = 0;
//  x2 = 230;
//  y2 = 90;
//  Q2 = (acos(float((pow(x2, 2) + pow(y2, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2))))*(180/PI);
//  Q1 = (atan(float(y2)/float(x2))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
//  positions[0] = (long(Q1) * 12800) / 360; //12800 / 2;
//  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
//  steppers.moveTo(positions);
//  steppers.runSpeedToPosition();
//  delay(1000);
//  steppers.moveTo(positions);
//  steppers.runSpeedToPosition();
//
//  delay(1000); 
//
//  positions[0] = (long(Q1) * 12800) / 360; //12800 / 2;
//  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
//  steppers.moveTo(positions);
//  steppers.runSpeedToPosition();
//  delay(1000); 
//
//
//
//  x2 = 230;
//  y2 = 90;
//  Q2 = (acos(float((pow(x2, 2) + pow(y2, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2))))*(180/PI);
//  Q1 = (atan(float(y2)/float(x2))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
//  positions[0] = (long(Q1) * 12800) / 360; //12800 / 2;
//  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
//  steppers.moveTo(positions);
//  steppers.runSpeedToPosition();
//  delay(1000); 

  
  

//  Serial.print(q);
//  Serial.print(' '); 
//  Serial.print(xp);
//  Serial.print(' '); 
//  Serial.print(yp);
//  Serial.print(' '); 
//  Serial.print(d);
//  Serial.print(" -------- "); 

//  Serial.print(Q1);
//  Serial.print(' '); 
//  Serial.print(Q2);
//  Serial.print(' '); 
////  Serial.print(Q3);
////  Serial.print(' ');
//  Serial.print(positions[0]);
//  Serial.print(' '); 
//  Serial.print(positions[1]);
////  Serial.print(' '); 
////  Serial.print(positions[2]);
//  Serial.println("---------------");

//  Serial.println(x2);
//--------------------------------------
//  long positions[3];
//  positions[0] = 0;
//  positions[1] = 0;
//  positions[2] = 0;
//  steppers.moveTo(positions);
//  steppers.runSpeedToPosition();
//  
////  accelStepper.runToNewPosition(0);
////  midStepper.runToNewPosition(0);
////  outStepper.runToNewPosition(0);  
//  
//  delay(500);
//
//  positions[0] = 12800 / 2;
//  positions[1] = 25600 / 2;
//  positions[2] = 6400 / 2;
//  steppers.moveTo(positions);
//  steppers.runSpeedToPosition();
//  
////  accelStepper.runToNewPosition(2000);
////  midStepper.runToNewPosition(1000);
////  outStepper.runToNewPosition(1000);
//  
//  delay(500);
}

void PrintParm(long arrPositions[]){
  Serial.print(Q1);
  Serial.print(' '); 
  Serial.print(Q2);
  Serial.print(' '); 
//  Serial.print(Q3);
//  Serial.print(' ');
  Serial.print(arrPositions[0]);
  Serial.print(' '); 
  Serial.print(arrPositions[1]);
//  Serial.print(' '); 
//  Serial.print(positions[2]);
  Serial.println("---------------");

}


