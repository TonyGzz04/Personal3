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

  Serial.begin(115200);
  delay(100);
  Serial.print("Listo");

  for (short i=0; i<500; i++){
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,2,true);
    AcX = Wire.read()<<8|Wire.read();
    ax=float(AcX)/16384*9.81;
    suma=suma+ax;
    Serial.println(suma,4);
  }
  promedio=suma/500.0;
  
  Serial.print("Promedio: ");
  Serial.println(promedio,4);

for (short i=0; i<2000; i++){
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,2,true);
    previousTime=millis();
    AcX = Wire.read()<<8|Wire.read();
    
    ax=float(AcX)/16384*9.81-promedio;
    elapsedTime=millis()-previousTime;
    sumaD=sumaD+ax*elapsedTime*elapsedTime/2;
    Serial.println(sumaD,4);
  }

  promedioD=sumaD/2000.0;
  Serial.print("PromedioD: ");
  Serial.println(promedioD,4);
  delay(2000);
  
}

void loop()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  //Wire.write(0x43);
  Wire.endTransmission(false);
  //Wire.requestFrom(MPU_addr,22,true);
  
  Wire.requestFrom(MPU_addr,14,true);
  
  previousTime = millis();
  AcX = Wire.read()<<8|Wire.read();    
  AcY = Wire.read()<<8|Wire.read();
  AcZ = Wire.read()<<8|Wire.read();
  Tmp = Wire.read()<<8|Wire.read();
  GyX = Wire.read()<<8|Wire.read();
  GyY = Wire.read()<<8|Wire.read();
  GyZ = Wire.read()<<8|Wire.read();

  gx=float(GyX);
  Serial.println(gx,1);

  


 }
