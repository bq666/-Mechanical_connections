/*
 # Product: 6 DOF Sensor-MPU6050 
 # SKU    : SEN0142 
 # Description:     
 # To read  accel/gyro data from 6 DOF Sensor 
*/
#include "Wire.h"                 
//#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;  
int16_t axi, ayi, azi;  // define accel as ax,ay,az
int16_t gxi, gyi, gzi;  // define gyro as gx,gy,gz


#include <SampleFilter.h>
SampleFilter FiltrX;
SampleFilter FiltrY;








void setup() { // <----------------------------------------------------------      SETUP
  Wire.begin();      // join I2C bus   
  Serial.begin(9600);    //  initialize serial communication
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();  

  // verify connection
//  Serial.println("Testing device connections...");
//  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  // Init Filter
  SampleFilter_init(&FiltrX);
  SampleFilter_init(&FiltrY);
  
  


  
}








#define moveSteps 220
#define moveStart 1400
#define calibX -750


int dataX [moveSteps];
//int dataXout [220];
int dataY [moveSteps];
//int dataYout [220];


float t = 0.424;


long Vxp = 0;
long Vxk = 0;
long dVx = 0;
long dSx = 0;
long Sxk = 0;
long ax = 0;

long Vyp = 0;
long Vyk = 0;
long dVy = 0;
long Sy = 0;


long ts = 0;
long tstop = 0;



void loop() { // <----------------------------------------------------------      LOOP
//  ts = micros();
  accelgyro.getMotion6(&axi, &ayi, &azi, &gxi, &gyi, &gzi);  // read measurements from device
//  tstop = micros() - ts;
//  Serial.print(tstop);
//  Serial.print(" ");
  
//    Serial.print(axi);
//    Serial.print(" ");
//    Serial.print(ayi);
//    Serial.print(" ");
//    Serial.print(azi);
//    Serial.println(" ");
    
  dataX[0] = axi;// + calibX;
  dataY[0] = ayi + 600;

//  Serial.print(dataX[0]);
//  Serial.print(" "); 
//  Serial.print(dataY[0]);
//  Serial.println(" ");  


  if((abs(dataX[0]) > moveStart)){// || (abs(dataY[0]) > moveStart)){
//    ts = micros();
    for(int i = 0; i < moveSteps; i++){
      accelgyro.getMotion6(&axi, &ayi, &azi, &gxi, &gyi, &gzi);  // read measurements from device
      dataX[i] = axi;// + calibX;
      dataY[i] = ayi + 1400;
    }
//    tstop = micros() - ts;
//    Serial.print(tstop);
//    Serial.print(" ");
    for(int i = 0; i < moveSteps; i++){
      SampleFilter_put(&FiltrX, dataX[i]);
      dataX[i] = SampleFilter_get(&FiltrX);
      SampleFilter_put(&FiltrY, dataY[i]);
      dataY[i] = SampleFilter_get(&FiltrY);
    }

//    for(int i = 0; i < moveSteps; i++){
//      Serial.print(dataX[i]);
//      Serial.print(" "); 
//      Serial.print(dataY[i]);
//      Serial.println(" ");      
//    }
//    for(int i = 0; i < moveSteps; i++){
//      dataX[i] = 0;
//      dataY[i] = 0;
//    }

    for(int i = 0; i < moveSteps; i++){
      ax = (long(dataX[i]) * 9806) / 16500;      
      dVx = float(ax) * t;
      Vxk = dVx + Vxp; 
//      Vxp = Vxk;
      dSx = ((float(Vxp) * t) * (ax * pow(t, 2)) / 2);
      Sxk += dSx;
//      Vxk = dVx + Vxp;
      Vxp = Vxk;
      Serial.print(dataX[i]);
      Serial.print(" "); 
      Serial.print(ax);
      Serial.print(" "); 
      Serial.print(dVx);
      Serial.print(" ");
      Serial.print(Vxk);
//      Serial.print(" ");
//      Serial.print(Sxk);
      Serial.println(" ");
    }
    dSx = 0;
    Sxk = 0; 
    Vxk = 0;
    Vxp = 0;
//    Serial.println(ax);


  }    
  
//  tstop = micros() - ts;
//  Serial.print(tstop);  
//  Serial.print(" ");  


  
  
//  SampleFilter_put(&Filtr, 100);
//  a = SampleFilter_get(&Filtr);
//  Serial.println(a);
  
//  for(int i = 0; i <= 99; i++){
////    SampleFilter_put(&Filtr, dataXin[i]);
//    dataXout[i] = 0; //SampleFilter_get(&Filtr);
//  }
//
//  for(int i = 0; i <= 99; i++){
//    Serial.print(dataXin[i]);
//    Serial.print(" "); 
//    Serial.println(dataXout[i]);
//  }


  
}













  
  
//  ax = (ax * 10) / 17500;
//  ay = (ay * 10) / 17500;
//  
//  Vkx = Vpx + ax * pow(t, 2);
//  Sx = Vpx * t + (ax / 2) * pow( t, 2); 
//  Vpx = Vkx;
//  
//  Vky = Vpy + ay * pow(t, 2);
//  Sy = Vpy * t + (ay / 2) * pow( t, 2); 
//  Vpy = Vky;
  
  
  
  
  
  
  // display tab-separated accel/gyro x/y/z values
//  Serial.print("a/g:\t");
  

//  Serial.print(gx); 
//  Serial.print("\t");
//  Serial.print(gy); 
//  Serial.print("\t");
//  Serial.print(gz);

//
//  Serial.print(ax); 
//  Serial.print("\t");
//  Serial.print(ay); 
//  Serial.print("\t");
//  Serial.print(az); 

//  Serial.print(Vpx);
//  Serial.print("\t");
//  Serial.print(Vkx);
//  Serial.print("\t");
//  Serial.print(Sx);
//  Serial.print("\t");
//  Serial.print(Sy);

  
//  Serial.print(t);
//  Serial.print("\t");
//  Serial.print(sx);

  
//  Serial.println("\t");


//  t = micros() - ts;
 





//void SampleFilter_init(SampleFilter* f) {
//  int i;
//  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i)
//    f->history[i] = 0;
//  f->last_index = 0;
//}
//
//void SampleFilter_put(SampleFilter* f, int input) {
//  f->history[f->last_index++] = input;
//  if(f->last_index == SAMPLEFILTER_TAP_NUM)
//    f->last_index = 0;
//}
//
//int SampleFilter_get(SampleFilter* f) {
//  long long acc = 0;
//  int index = f->last_index, i;
//  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
//    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
//    acc += (long long)f->history[index] * filter_taps[i];
//  };
//  return acc >> 16;
//}







