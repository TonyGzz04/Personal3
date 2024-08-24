#include "Wire.h"


const int MPU_ADDR = 0x68; // 0x say that we are working with hex numbers and 68 is the acc & gyro sensor adress in hex (from data sheet)
const int MAG_ADDR = 0x0C; // 0x say that we are working with hex numbers and 0C is the magnetometer sensor adress in hex (from data sheet)

int8_t Device_ID;
int16_t mag_xL, mag_xH, mag_yL, mag_yH, mag_zL, mag_zH;

int16_t mag_x, mag_y, mag_z;
int16_t acc_x, acc_y, acc_z;
int16_t gyr_x, gyr_y, gyr_z;
int16_t temp;

int16_t Msens_x,Msens_y, Msens_z;

int8_t control_1;
int8_t status_1;
int8_t status_2;
float Yaw;
float asax, asay, asaz;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Acc & Gyro Registers********************************************
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6A);   // USER CONTROL  
  Wire.write(0x00);   // 0x00 is reset value
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_ADDR);   
  Wire.write(0x37);   //  IMU INT PIN CONFIG    
  Wire.write(0x02);   //  0x02 activate bypass in order to communicate with magnetometer
  Wire.endTransmission(true);
  delay(200);

  // Magnetometer Registers*****************************************
  Wire.beginTransmission(MAG_ADDR); 
  Wire.write(0x0B);   //  CONTROL 2
  Wire.write(0b01);   //  0 NORMAL OR 1 RESET
  Wire.endTransmission(true);
  delay(200);

  Wire.beginTransmission(MAG_ADDR);   //SLEEP MODE
  Wire.write(0x0A);   //  CONTROL 1
  Wire.write(0b00010000);   // 1 for 16 bit or 0 for 14 bit output, 0000 SLEEP MODE
  Wire.endTransmission(true);
  delay(200);

  
  Wire.beginTransmission(MAG_ADDR);   //ROM WRITE MODE
  Wire.write(0x0A);   //  CONTROL 1
  Wire.write(0b00011111); // 1 for 16 bit or 0 for 14 bit output, 1111 FUSE ROM ACCESS MODE
  Wire.endTransmission(true);
  delay(200);

  Wire.beginTransmission(MAG_ADDR);   //GET MAGNETIC SENSITIVITY DATA FOR CONVERTING RAW DATA
  Wire.write(0x10);     //  ASAX  
  Wire.endTransmission(false);
  Wire.requestFrom(MAG_ADDR, 3 , true);  //GET SENSITIVITY ADJUSMENT VALUES STARTS AT ASAX
  Msens_x = Wire.read();    //GET X SENSITIVITY ADJUSMENT VALUE
  Msens_y = Wire.read();    //GET Y SENSITIVITY ADJUSMENT VALUE
  Msens_z = Wire.read();    //GET Z SENSITIVITY ADJUSMENT VALUE
  Serial.println(Msens_x);
  Serial.println(Msens_y);
  Serial.println(Msens_z);
  Wire.endTransmission(true);
  asax = (((Msens_x-128))/256.0f)+1.0f;
  asay = (((Msens_y-128))/256.0f)+1.0f;
  asaz = (((Msens_z-128))/256.0f)+1.0f;
  Serial.print("Mx Sensitivity: ");  Serial.println(asax);
  Serial.print("My Sensitivity: ");  Serial.println(asay);
  Serial.print("Mz Sensitivity: ");  Serial.println(asaz); 
  delay(200);
  
  Wire.beginTransmission(MAG_ADDR);   //SLEEP MODE
  Wire.write(0x0A);   //  CONTROL 1
  Wire.write(0b00010000);  // 1 for 16 bit or 0 for 14 bit output, 0000 SLEEP MODE
  Wire.endTransmission(true);
  delay(200);
    
  Wire.beginTransmission(MAG_ADDR);   //CONT MODE 2
  Wire.write(0x0A);
  Wire.write(0b00010110); // 1 for 16 bit or 0 for 14 bit output, 0110 FOR CONT MODE 2 (X Hz?) 
  Wire.endTransmission(true);
  delay(200);
}

void loop() {
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x00);
  Wire.endTransmission(false);
  Wire.requestFrom(MAG_ADDR, 1 , true);   
  Device_ID = Wire.read();
  Serial.print("Device_ID: "); Serial.println(Device_ID,DEC);  
  Wire.endTransmission(true);
 

  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x0A);
  Wire.endTransmission(false);
  Wire.requestFrom(MAG_ADDR, 1 , true);  
  control_1 = Wire.read();  // check DRDY bit if ready to read
  Serial.print("control_1: "); Serial.println(control_1,BIN);  
  Wire.endTransmission(true);

  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x02);
  Wire.endTransmission(false);
  Wire.requestFrom(MAG_ADDR, 1 , true);   
  status_1 = Wire.read();
  Serial.print("Status 1: "); Serial.println(status_1,BIN);  
  Wire.endTransmission(true);

  if(status_1 == 0b11) {
    Wire.beginTransmission(MAG_ADDR);
    Wire.write(0x03);
    Wire.endTransmission(false);
    Wire.requestFrom(MAG_ADDR, 7 , true);
   
    mag_xL = Wire.read();
    mag_xH = Wire.read();
    mag_x = (mag_xH << 8) | mag_xL;

    Serial.print("Available bytes left after reading mag x values: "); Serial.println(Wire.available(),DEC);    
    
    mag_yL = Wire.read();
    mag_yH = Wire.read();
    mag_y = (mag_yH << 8) | mag_yL;    
    
    Serial.print("LOW BITS Mag_Y: "); Serial.println(mag_yL,BIN);  
    Serial.print("HIGH BITS Mag_Y: "); Serial.println(mag_yH,BIN);
    Serial.print("FULL BITS Mag_Y: "); Serial.println(mag_y,BIN);    
    
    mag_zL = Wire.read();
    mag_zH = Wire.read();
    mag_z = (mag_zH << 8) | mag_zL;

    
    status_2 = Wire.read();   // check if there is a magnetic overflow 
    Serial.print("Status 2: "); Serial.println(status_2,BIN);  
    
  //if(status_2 != 0x08)
    
    
    
    Wire.endTransmission(true);

    Serial.print("  | mX = "); Serial.print(mag_x*asax*0.15); Serial.print(" [uT]");
    Serial.print("  | mY = "); Serial.print(mag_y*asay*0.15); Serial.print(" [uT]");
    Serial.print("  | mZ = "); Serial.print(mag_z*asaz*0.15); Serial.println(" [uT]");
  }
   
  
  //  Yaw = (atan2(mag_y,mag_x)*(180/3.141));
  //Serial.println(Yaw);  
  

  Serial.println("-------------------------------END OF THE LOOP ---------------------------");
  delay(500);

}
