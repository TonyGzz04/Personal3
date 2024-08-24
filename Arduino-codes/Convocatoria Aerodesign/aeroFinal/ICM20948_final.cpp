#include "Arduino.h"
#include "Arduino-ICM20948.h"
#include "ICM20948_final.h"
#include <Wire.h>

ICM20948_final::ICM20948_final(){}

ArduinoICM20948 icm20948;


float run_icm20948_gyro_controller(char var) {
  float x, y, z;
  char sensor_string_buff[128];
  if (icm20948.gyroDataIsReady()){
      icm20948.readGyroData(&x, &y, &z);
      //sprintf(sensor_string_buff, "Gyroscope x, y, z (rad/s): [%f,%f,%f]", x, y, z);
      //Serial.println(x);
      switch (var) {
        case 1: return x; break;
        case 2: return y; break;
        case 3: return z; break;
      }
  }
  return 0;
}


float run_icm20948_accel_controller(char var){
          float x, y, z;
          char sensor_string_buff[128];
          if (icm20948.accelDataIsReady())
          {
              icm20948.readAccelData(&x, &y, &z);
              // sprintf(sensor_string_buff, "Acceleration x, y, z (g): [%f,%f,%f]", x, y, z);
              // Serial.println(sensor_string_buff);
              switch (var) {
                case 1: return x; break;
                case 2: return y; break;
                case 3: return z; break;
              }
          }
          return 0;
}

float run_icm20948_quat9_controller(bool inEuler, char var){
              float quat_w, quat_x, quat_y, quat_z;
              float roll, pitch, yaw;
              char sensor_string_buff[128];
              if (inEuler)
              {
                  if (icm20948.euler9DataIsReady())
                  {
                      icm20948.readEuler9Data(&roll, &pitch, &yaw);
                      // sprintf(sensor_string_buff, "Euler9 roll, pitch, yaw(deg): [%f,%f,%f]", roll, pitch, yaw);
                      // Serial.println(roll);
                      switch (var) {
                        case 1: return roll; break;
                        case 2: return pitch; break;
                        case 3: return yaw; break;
                      }
                  }
              }
              return 0;
              // else
              // {
              //     if (icm20948.quat9DataIsReady())
              //     {
              //         icm20948.readQuat9Data(&quat_w, &quat_x, &quat_y, &quat_z);
              //         // sprintf(sensor_string_buff, "Quat9 w, x, y, z (deg): [%f,%f,%f,%f]", quat_w, quat_x, quat_y, quat_z);
              //         // Serial.println(sensor_string_buff);
              //     }
              // }
              
}








void ICM20948_final::inite(){ 
  Wire.begin();
  Wire.setClock(400000);
  Serial.println("Starting ICM");

      ArduinoICM20948 icm20948;
      ArduinoICM20948Settings icmSettings =
      {
        .i2c_speed = 400000,                // i2c clock speed
        .is_SPI = false,                    // Enable SPI, if disable use i2c
        .cs_pin = 10,                       // SPI chip select pin
        .spi_speed = 7000000,               // SPI clock speed in Hz, max speed is 7MHz
        .mode = 1,                          // 0 = low power mode, 1 = high performance mode
        .enable_gyroscope = true,           // Enables gyroscope output
        .enable_accelerometer = true,       // Enables accelerometer output
        .enable_magnetometer = true,        // Enables magnetometer output // Enables quaternion output
        .enable_gravity = true,             // Enables gravity vector output
        .enable_linearAcceleration = true,  // Enables linear acceleration output
        .enable_quaternion6 = true,         // Enables quaternion 6DOF output
        .enable_quaternion9 = true,         // Enables quaternion 9DOF output
        .enable_har = true,                 // Enables activity recognition
        .enable_steps = true,               // Enables step counter
        .gyroscope_frequency = 7,           // Max frequency = 225, min frequency = 1
        .accelerometer_frequency = 1,       // Max frequency = 225, min frequency = 1
        .magnetometer_frequency = 1,        // Max frequency = 70, min frequency = 1 
        .gravity_frequency = 1,             // Max frequency = 225, min frequency = 1
        .linearAcceleration_frequency = 1,  // Max frequency = 225, min frequency = 1
        .quaternion6_frequency = 50,        // Max frequency = 225, min frequency = 50
        .quaternion9_frequency = 50,        // Max frequency = 225, min frequency = 50
        .har_frequency = 50,                // Max frequency = 225, min frequency = 50
        .steps_frequency = 50               // Max frequency = 225, min frequency = 50
        
      };

      const uint8_t number_i2c_addr = 2;
      uint8_t poss_addresses[2] = {0X69, 0X68};
      uint8_t ICM_address;
      bool ICM_found = false;


  delay(10);
  
  uint8_t error;
            for(uint8_t add_int = 0; add_int < number_i2c_addr; add_int++ ){
                Serial.print("Scanning 0x%02X for slave...");
                Serial.println(poss_addresses[add_int]);
                Wire.beginTransmission(poss_addresses[add_int]);
                error = Wire.endTransmission();
                if (error == 0){
                    Serial.println("found.");
                    if(poss_addresses[add_int] == 0x69 || poss_addresses[add_int] == 0x68){
                        Serial.println("\t- address is ICM.");
                        ICM_address = poss_addresses[add_int];
                        ICM_found = true;
                    }
                }
            }

  if (ICM_found)
  {
      icm20948.init(icmSettings);
  }
}

float ICM20948_final::gx(){ 
  icm20948.task();
  float x, y, z;
  char sensor_string_buff[128];
  if (icm20948.gyroDataIsReady()){
      icm20948.readGyroData(&x, &y, &z);
      //sprintf(sensor_string_buff, "Gyroscope x, y, z (rad/s): [%f,%f,%f]", x, y, z);
      //Serial.println(x);
       return x;
      }
    return 0;
  } 
float ICM20948_final::gy(){ 
  icm20948.task();
  float x, y, z;
  char sensor_string_buff[128];
  if (icm20948.gyroDataIsReady()){
      icm20948.readGyroData(&x, &y, &z);
      //sprintf(sensor_string_buff, "Gyroscope x, y, z (rad/s): [%f,%f,%f]", x, y, z);
      //Serial.println(x);
       return y;
      }
    return 0;
 }
float ICM20948_final::gz(){ 
  icm20948.task();
  float x, y, z;
  char sensor_string_buff[128];
  if (icm20948.gyroDataIsReady()){
      icm20948.readGyroData(&x, &y, &z);
      //sprintf(sensor_string_buff, "Gyroscope x, y, z (rad/s): [%f,%f,%f]", x, y, z);
      //Serial.println(x);
       return z;
      }
    return 0;
 }

float ICM20948_final::ax(){ 
  icm20948.task();
  float x, y, z;
          char sensor_string_buff[128];
          if (icm20948.accelDataIsReady())
          {
              icm20948.readAccelData(&x, &y, &z);
              // sprintf(sensor_string_buff, "Acceleration x, y, z (g): [%f,%f,%f]", x, y, z);
              // Serial.println(sensor_string_buff);
            return x;
          }
          return 0;
 }
float ICM20948_final::ay(){ 
  icm20948.task();
  float x, y, z;
          char sensor_string_buff[128];
          if (icm20948.accelDataIsReady())
          {
              icm20948.readAccelData(&x, &y, &z);
              // sprintf(sensor_string_buff, "Acceleration x, y, z (g): [%f,%f,%f]", x, y, z);
              // Serial.println(sensor_string_buff);
            return y;
          }
          return 0;
 }
float ICM20948_final::az(){ 
  icm20948.task();
  float x, y, z;
          char sensor_string_buff[128];
          if (icm20948.accelDataIsReady())
          {
              icm20948.readAccelData(&x, &y, &z);
              // sprintf(sensor_string_buff, "Acceleration x, y, z (g): [%f,%f,%f]", x, y, z);
              // Serial.println(sensor_string_buff);
            return z;
          }
          return 0;
 }

float ICM20948_final::roll(){ 
  icm20948.task();
  float roll, pitch, yaw;
  char sensor_string_buff[128];
  if (icm20948.euler9DataIsReady())
      {
      icm20948.readEuler9Data(&roll, &pitch, &yaw);
      // sprintf(sensor_string_buff, "Euler9 roll, pitch, yaw(deg): [%f,%f,%f]", roll, pitch, yaw);
      // Serial.println(roll);
      return roll;
  }
  return 0;
}
float ICM20948_final::pitch(){ 
  icm20948.task();
  float roll, pitch, yaw;
  char sensor_string_buff[128];
  if (icm20948.euler9DataIsReady())
      {
      icm20948.readEuler9Data(&roll, &pitch, &yaw);
      // sprintf(sensor_string_buff, "Euler9 roll, pitch, yaw(deg): [%f,%f,%f]", roll, pitch, yaw);
      // Serial.println(roll);
      return pitch;
  }
  return 0;
 }
float ICM20948_final::yaw(){ 
  float roll, pitch, yaw;
  char sensor_string_buff[128];
  if (icm20948.euler9DataIsReady())
      {
      icm20948.readEuler9Data(&roll, &pitch, &yaw);
      // sprintf(sensor_string_buff, "Euler9 roll, pitch, yaw(deg): [%f,%f,%f]", roll, pitch, yaw);
      // Serial.println(roll);
      return yaw;
  }
  return 0;
 }
