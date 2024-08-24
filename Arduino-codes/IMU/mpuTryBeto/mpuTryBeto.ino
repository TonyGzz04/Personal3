#include<Wire.h>
#include <LiquidCrystal_I2C.h>  //se incluye la librería para la LCD

LiquidCrystal_I2C lcd(0x27,16,2);     //se declara la memoria que usará la LCD y su tamaño

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int j=1;

float elapsedTime, currentTime, previousTime;
unsigned long tiempo = 0;

int anguloX = 0;

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.begin(9600);
  Serial.print("Hi");
  delay(100);

  Wire.beginTransmission(0x27);
  lcd.init();
  lcd.backlight();
  
  lcd.print("Calibrando...");   //mensaje en la LCD
  Wire.endTransmission(true);
}

void loop()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  
  Wire.requestFrom(MPU_addr,14,true);
  
  AcX = Wire.read()<<8|Wire.read();    
  AcY = Wire.read()<<8|Wire.read();
  AcZ = Wire.read()<<8|Wire.read();
  Tmp = Wire.read()<<8|Wire.read();
  GyX = Wire.read()<<8|Wire.read();
  GyY = Wire.read()<<8|Wire.read();
  GyZ = Wire.read()<<8|Wire.read();

  GyX = GyX / 131.0;
  
  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime)/1000;

  anguloX = anguloX + GyX * 0.01;
  Serial.println(AcZ);

  // Wire.endTransmission(true);

  // Wire.beginTransmission(0x27);
  // lcd.init();
  // lcd.backlight();
  
  // for (int i=0; i<10; i=i+j){
  //   // Serial.println(i);
  //   lcd.print(i);   //mensaje en la LCD
  // }
  
  // Wire.endTransmission(true);
  // j++; 
  
 }