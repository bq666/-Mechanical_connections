#include "Wire.h"
#include "MPU6050.h"
MPU6050 accelgyro;
int16_t axi, ayi, azi;  // define accel as ax,ay,az
int16_t gxi, gyi, gzi;  // define gyro as gx,gy,gz
long faxi;

// #include "SampleFilter.h"
#include "SampleFilter.h"
SampleFilter FiltrX;
SampleFilter FiltrY;


long calibX = 0;





void setup() { // <----------------------------------------------------------      SETUP
  Wire.begin();      // join I2C bus
  Serial.begin(9600);    //  initialize serial communication
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  SampleFilter_init(&FiltrX);
  SampleFilter_init(&FiltrY);

  for (int i = 1; i <= 100; i++) { // <--- kalibracja
    accelgyro.getMotion6(&axi, &ayi, &azi, &gxi, &gyi, &gzi);  // read measurements from device
    calibX += axi;
//        Serial.print(axi);
//        Serial.print(' ');
//        Serial.println(calibX);
  }
  calibX /= 100;
//    Serial.println(calibX);
}

float Vxp = 0;
float Vxk = 0;
float dVx = 0;
float dSx = 0;
float Sxk = 0;
//long ax = 0;

//long Vyp = 0;
//long Vyk = 0;
//long dVy = 0;
//long Sy = 0;

long ts = 0;
float tstop = 0;




int move_xy_ar[] = {0, 0, 0, 0};
int border = 5;
int i = 0;


void loop() { // <----------------------------------------------------------      LOOP
  ts = micros();
  accel_xy();
//  Serial.println(move_xy_ar[0]);

  if (abs(move_xy_ar[0]) > border) {
    move_xy();
    i = 1;
    Serial.println(move_xy_ar[2]);
  } else if ((abs(move_xy_ar[0]) < border) && (i > 0) && (i <= 10)){
    move_xy();
    Serial.println(move_xy_ar[2]);
    i++;
//    Serial.println(i);
  }
//  Serial.println(i);
  if (i >= 10 ){
    i = 0; 
//    Serial.println(i);
    Vxp = 0;
    Vxk = 0;
    dVx = 0;
    dSx = 0;
    Sxk = 0;
  }
//  Serial.println(Sxk);

  tstop = micros() - ts; 
}




void accel_xy(){
  accelgyro.getMotion6(&axi, &ayi, &azi, &gxi, &gyi, &gzi);  // read measurements from device
  axi -= int(calibX);
  SampleFilter_put(&FiltrX, axi);
  faxi = SampleFilter_get(&FiltrX);
//    Serial.print(faxi);
//    Serial.print(' ');
  faxi = (faxi * 981) / 17850;
//    Serial.print(faxi);
//    Serial.println(' ');
  move_xy_ar[0] = int(faxi);
}

void move_xy(){
  tstop = tstop / 1000000;
  //  Serial.print(tstop, 3);
  //  Serial.print(' ');
  dVx = faxi * tstop; //float(ax) * t;
  Vxk = dVx + Vxp;
  Vxp = Vxk;
  dSx = ((Vxp * tstop) + (faxi * pow(tstop, 2)) / 2);
  Sxk += dSx;  
  move_xy_ar[2] = int(Sxk * 10);
}




