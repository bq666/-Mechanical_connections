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


  float L1 = 100;
  float L2 = 100;
  float L3 = 50; 

  int x = 0;
  int y = 0;

  int x2 = 200;
  int y2 = 130;
  
  float q = 0;

  int Q1 = 0;
  int Q2 = 0;
  int Q3 = 0;

  float yp = 0;
  float xp = 0;
  float d = 0;
  

void loop()
{
  q = 90 - atan2(y2, x2) * (180/PI);
  
  xp = x2 - (L3 * cos(q * (PI/180)));
  yp = y2 - (L3 * sin(q * (PI/180)));


  d = atan2((-yp/(sqrt(pow(xp, 2) + pow(yp, 2)))),(-xp/(sqrt(pow(xp, 2) + pow(yp, 2)))));

  Q1 = d + acos((-(pow(xp, 2) + pow(yp, 2) + pow(L1, 2) - pow(L2, 2)))/(2 * L1 * sqrt(pow(xp, 2) + pow(yp, 2))));

  Q2 = atan2((yp - L1 * sin(Q1)) / L2, (xp - L1 * cos(Q1)) / L2) - Q1;

  Q3 = q - (Q1 - Q2); 

  long positions[3];
  positions[0] = 0;
  positions[1] = 0;
  positions[2] = 0;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();

  delay(1000); 

  positions[0] = (long(Q3) * 12800) / 360; //12800 / 2;
  positions[1] = (long(Q2) * 25600) / 360; //25600 / 2;
  positions[2] = (long(Q1) * 6400) / 360; //6400 / 2;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();

  delay(1000); 
  

  Serial.print(q);
  Serial.print(' '); 
  Serial.print(xp);
  Serial.print(' '); 
  Serial.print(yp);
  Serial.print(' '); 
  Serial.print(d);
  Serial.print(" -------- "); 
  Serial.print(Q1);
  Serial.print(' '); 
  Serial.print(Q2);
  Serial.print(' '); 
  Serial.print(Q3);
  Serial.print(' ');
  Serial.print(positions[0]);
  Serial.print(' '); 
  Serial.print(positions[1]);
  Serial.print(' '); 
  Serial.print(positions[2]);
  Serial.println("---------------");

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
