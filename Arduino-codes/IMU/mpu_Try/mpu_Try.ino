#include <Wire.h>

const int MPU_addr=0x68;
#define PWR_MGMT_1_AD 0x6B


int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int iniciador = 1;

float elapsedTime=0; 
float currentTime, previousTime;
unsigned long tiempo = 0;

float anguloX = 0;
float distancia = 0;
float suma = 0.0;
float promedio = 0.0;
float sumaD = 0.0;
float promedioD = 0.0;
float gx = 0;
float ax = 0;
float distance=0.0;


void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);

  //Wire.write(0x6B);
  //Wire.write(0x00);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_addr);
  Wire.write(PWR_MGMT_1_AD);
  Wire.write(0x01);
  Wire.write(1);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);
  Wire.write(0x04);
  Wire.write(2);
  Wire.endTransmission(true);

  Serial.begin(250000);
  delay(100);
  Serial.print("Listo");

  for (short i=0; i<500; i++){
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,2,true);
    GyX = Wire.read()<<8|Wire.read();
    gx=float(GyX)/131;
    suma=suma+gx;
    Serial.println(suma,4);
  }
  promedio=suma/500.0;
  
  Serial.print("Promedio: ");
  Serial.println(promedio,4);
  
}

void loop()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);
  //Wire.write(0x43);
  Wire.endTransmission(false);
  //Wire.requestFrom(MPU_addr,22,true);
  
  Wire.requestFrom(MPU_addr,14,true);
  
  previousTime = millis();
  GyX = Wire.read()<<8|Wire.read();

  gx=float(GyX)/131-promedio;
  //Serial.println(gx);

  
  elapsedTime=millis()-previousTime;
  anguloX=anguloX+gx*elapsedTime;
  Serial.println(anguloX,4);


 }
