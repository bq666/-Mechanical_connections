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
  

  #define l1 100;
  #define l2 100;
  #define l3 50; 

  
  
}

void loop()
{
  long positions[3];
  positions[0] = 0;
  positions[1] = 0;
  positions[2] = 0;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
  
//  accelStepper.runToNewPosition(0);
//  midStepper.runToNewPosition(0);
//  outStepper.runToNewPosition(0);  
  
  delay(500);

  positions[0] = 12800 / 4;
  positions[1] = 25600 / 4;
//  positions[2] = 6400 / 2;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
  
//  accelStepper.runToNewPosition(2000);
//  midStepper.runToNewPosition(1000);
//  outStepper.runToNewPosition(1000);
  
  delay(500);
//    
  positions[0] = -12800 / 4;
  positions[1] = -25600 / 4;
//  positions[2] = -6400 / 2;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
  
//  accelStepper.runToNewPosition(2000);
//  midStepper.runToNewPosition(1000);
//  outStepper.runToNewPosition(1000);
  
  delay(500);
}
