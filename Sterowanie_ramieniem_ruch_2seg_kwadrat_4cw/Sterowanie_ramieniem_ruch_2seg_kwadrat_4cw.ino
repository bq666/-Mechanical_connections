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

AMIS30543 stepperW;
AMIS30543 stepperS;

AccelStepper StepperW(AccelStepper::DRIVER, amisStepPinW, amisDirPinW);
AccelStepper StepperS(AccelStepper::DRIVER, amisStepPinS, amisDirPinS);

MultiStepper steppers;
//------------------------------------------

#include "Wire.h"   
#include "MPU6050.h"

MPU6050 accelgyro;  
int16_t ax, ay, az;  // define accel as ax,ay,az
int16_t gx, gy, gz;  // define gyro as gx,gy,gz
//------------------------------------------



  #define res 1000
  
  long L1 = res;
  long L2 = res;
 
  float Q1 = 0;
  float Q2 = 0;

  int SetSpeed = 0; // im większa liczba tym wolniej 
  
//  int a = 1000;

//  int xs = 800;
//  int ys = 800;
//  int xi = 0;
//  int yi = 0;
  int r = 300;
  int n = 100;
//  int i = 0;


//-------------------------------------
long t = 1;


long Vpx = 0;
long Vkx = 0;
long dVx = 0;
long Sx = 0;

long Vpy = 0;
long Vky = 0;
long dVy = 0;
long Sy = 0;
//--------------------------------------

  
void setup()
{
  SPI.begin();
  Wire.begin();      // join I2C bus   

  stepperW.init(amisSlaveSelectW);
  stepperS.init(amisSlaveSelectS);
  delay(5);

  stepperW.resetSettings();
  stepperW.setCurrentMilliamps(2300);
  stepperW.setStepMode(32);
  stepperW.enableDriver();

  stepperS.resetSettings();
  stepperS.setCurrentMilliamps(1900);
  stepperS.setStepMode(64);
  stepperS.enableDriver();
    
  StepperW.setMaxSpeed(2000.0);
  StepperW.setAcceleration(1.0);

  StepperS.setMaxSpeed(2000.0);
  StepperS.setAcceleration(1);

  steppers.addStepper(StepperW);
  steppers.addStepper(StepperS);

  pinMode(7, OUTPUT);
  Serial.begin(9600);  
}

void loop(){  
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);  // read measurements from device
//  Serial.print(ax);
  ax = (ax * 10) / 17500;
  ay = (ay * 10) / 17500;
  
  Vkx = Vpx + ax * pow(t, 2);
  Sx = Sx + (Vpx * t + (ax / 2) * pow(t, 2));
  Vpx = Vkx;
  
  Vky = Vpy + ay * pow(t, 2);
  Sy = Sy + (Vpy * t + (ay / 2) * pow(t, 2)); 
  Vpy = Vky;

  if(Sx == 0){Sx = 1;}
  if(Sy == 0){Sy = 1;}
  
  Serial.print("\t");
  Serial.print(Vkx);
  Serial.print("\t");
  Serial.print(Vky);

  
//  MoveArm(Sx, Sy, SetSpeed);




//  MoveArm(2000, 0, SetSpeed); 

//  MoveArm(0, 0, SetSpeed);

  
//  for(int y = 0; y <= 500; y++){
//    MoveArm(1000, y, SetSpeed);
//  }
////  Serial.println("xxxxxxxxxxxxxxxxxxxxx"); 
//  for(int x = 1000; x >= -1000; x--){
//    MoveArm(x, 500, SetSpeed);
//  }
////  Serial.println("xxxxxxxxxxxxxxxxxxxxx"); 
//  for(int y = 500; y >= 0; y--){
//    MoveArm(-1000, y, SetSpeed);
//  }
////  Serial.println("xxxxxxxxxxxxxxxxxxxxx"); 
//  for(int x = -1000; x <= 1000; x++){
//    MoveArm(x, 0, SetSpeed);
//  }

//  for(int i = 0; i <= n; i++){
//    digitalWrite(7, HIGH);
//    xi = xs + (r * cos((2*PI*i) / n));
//    yi = ys + (r * sin((2*PI*i) / n));
//    digitalWrite(7, LOW);
//    MoveArm(xi, yi, SetSpeed);
//  }

//  Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); 
  Serial.println("\t");
}



void MoveArm(int x, int y, int SetSpeed){
  static long positions[2];
  if((x >= 0) && (y >= 0)){
    Q2 = ComputQ2(x, y, L1, L2);
    Q1 = ComputQ1(x, y, L1, L2, Q2);
  }
  if(((x < 0) && (y >= 0)) || ((x < 0) && (y < 0))){
    Q2 = ComputQ2(x, y, L1, L2);
    Q1 = 180 + ComputQ1(x, y, L1, L2, Q2);
  }  
   if((x >= 0) && (y < 0)){
    Q2 = ComputQ2(x, y, L1, L2);
    Q1 = 360 + ComputQ1(x, y, L1, L2, Q2);
  }  
  positions[0] = (Q1 * 12800) / 360; //12800 / 2;
  positions[1] = (Q2 * 25600) / 360; //25600 / 2;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();
//  PrintParm(positions, x, y);
  delay(SetSpeed);
}

float ComputQ2 (int x, int y, long L1, long L2){
  return (acos(float((pow(x, 2) + pow(y, 2) - pow(L1, 2) - pow(L2, 2))/(2 * L1 * L2)))*(180/PI));
}

float ComputQ1 (int x, int y, long L1, long L2, float Q2){
  return (atan(float(y)/float(x))*(180/PI)) - atan(float((L2 * sin(Q2*(PI/180)))/(L1 + (L2 * cos(Q2*(PI/180))))))*(180/PI);
}

void PrintParm(long arrPositions[], int x, int y){
  Serial.print(x);
  Serial.print(' '); 
  Serial.print(y);
  Serial.print(' ');
  Serial.print(Q1);
  Serial.print(' '); 
  Serial.print(Q2);
  Serial.print(' '); 
//  Serial.print(Q3);
//  Serial.print(' ');
  Serial.print(arrPositions[0]);
  Serial.print(' '); 
  Serial.print(arrPositions[1]);
  Serial.print(' '); 
//  Serial.print(positions[2]);
  Serial.println("---------------");

}


