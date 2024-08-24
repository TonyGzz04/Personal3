#include <Wire.h>


const int mpu = 0x68;

float roll, pitch, yaw;
float rollRate, pitchRate, yawRate;
float angRoll, angPitch, angYaw;

float ax, ay, az;

float kAngRoll = 0, kUncAngRoll = 2*2;
float kAngPitch = 0, kUncAngPitch = 2*2;

float k1Dout[] = {0,0};

long loopTimer = 0;
bool listo = false;


void setup(){

  Serial.begin(57600);

  Wire.setClock(400000);
  Wire.begin();
  delay(250);

  Wire.beginTransmission(mpu);  // start and continue in power mode
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  for (int cal = 0; cal < 2000; cal++){
    gyro();
    rollRate += roll;
    pitchRate += pitch;
    yawRate += yaw;
    delay(1);
  }

  listo = true;
  rollRate /= 2000;
  pitchRate /= 2000;
  yawRate /= 2000;

  loopTimer = micros();

}  




void loop(){

  // gyro();
  // Serial.print("Roll: "); Serial.print(roll-rollRate); Serial.print("\t");
  // Serial.print("Pitch: "); Serial.print(pitch-pitchRate); Serial.print("\t");
  // Serial.print("Yaw: "); Serial.println(yaw-yawRate);

  // acc();
  // Serial.print("AX: "); Serial.print(ax); Serial.print("\t");
  // Serial.print("AY: "); Serial.print(ay); Serial.print("\t");
  // Serial.print("AZ: "); Serial.println(az);

  // gyro();
  // Serial.print("Roll: "); 
  // Serial.print(angRoll); 
  // Serial.print("\t");
  // Serial.print("Pitch: "); 
  // Serial.println(angPitch);
  
  gyro();
  kalman1D(kAngRoll,kUncAngRoll,roll,angRoll);
  kAngRoll = k1Dout[0];
  kUncAngRoll = k1Dout[1];
  kalman1D(kAngPitch,kUncAngPitch,pitch,angPitch);
  kAngPitch = k1Dout[0];
  kUncAngPitch = k1Dout[1];

  Serial.print("Roll: "); 
  Serial.print(kAngRoll); 
  Serial.print("\t");
  Serial.print("Pitch: "); 
  Serial.println(kAngPitch);  

  delay(50);

  while (micros()-loopTimer < 4000);
  loopTimer = micros();

}










// FUNCIONES

void gyro(){
  Wire.beginTransmission(mpu);

  Wire.write(0x1A);   // filtro pasa bajos
  Wire.write(0x05);
  Wire.endTransmission();

  Wire.beginTransmission(mpu);    // sensitividad del giroscopio
  Wire.write(0x1B);
  Wire.write(0x8);
  Wire.endTransmission();

  if (listo == false){
    Wire.beginTransmission(mpu);
    Wire.write(0x43);
    Wire.endTransmission(false);

    Wire.requestFrom(mpu,6,true);

    float gx = Wire.read() << 8 | Wire.read();
    float gy = Wire.read() << 8 | Wire.read();
    float gz = Wire.read() << 8 | Wire.read();

    float fsb = 131;

    roll = (float)gx/fsb;
    pitch = (float)gy/fsb;
    yaw = (float)gz/fsb;
  }

  if (listo == true){
    Wire.beginTransmission(mpu);
    Wire.write(0x43);
    Wire.endTransmission(false);

    Wire.requestFrom(mpu,6,true);

    float gx = Wire.read() << 8 | Wire.read();
    float gy = Wire.read() << 8 | Wire.read();
    float gz = Wire.read() << 8 | Wire.read();

    float fsb = 131;

    roll = (float)gx/fsb-rollRate;
    pitch = (float)gy/fsb-pitchRate;
    yaw = (float)gz/fsb-yawRate;
  }

  Wire.beginTransmission(mpu);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(mpu,6,true);

  float accx = Wire.read() << 8 | Wire.read();
  float accy = Wire.read() << 8 | Wire.read();
  float accz = Wire.read() << 8 | Wire.read();

  float fsb = 4096;

  ax = (float)accx/fsb-0.06;
  ay = (float)accy/fsb+0.01;
  az = (float)accz/fsb+0.08;

  angRoll = atan(ay/sqrt(ax*ax+az*az))*1/(3.1415/180);
  angPitch = atan(-1*ax/sqrt(ay*ay+az*az))*1/(3.1415/180);



}


void acc(){

  Wire.write(0x1A);   // filtro pasa bajos
  Wire.write(0x05);
  Wire.endTransmission();

  Wire.beginTransmission(mpu);    // sensitividad del giroscopio
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  Wire.beginTransmission(mpu);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(mpu,6,true);

  float accx = Wire.read() << 8 | Wire.read();
  float accy = Wire.read() << 8 | Wire.read();
  float accz = Wire.read() << 8 | Wire.read();

  float fsb = 4096;

  ax = (float)accx/fsb-0.06;
  ay = (float)accy/fsb+0.01;
  az = (float)accz/fsb+0.08;

}


void kalman1D(float kState, float kUnc, float kIn, float kMeas){
  kState = kState + 0.004*kIn;
  kUnc = kUnc + 0.004*0.004*4*4;
  float kGain = kUnc*1/(1*kUnc+3*3);
  kState = kState + kGain*(kMeas-kState);
  kUnc = (1-kGain) * kUnc;

  k1Dout[0] = kState;
  k1Dout[1] = kUnc;
}