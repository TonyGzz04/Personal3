#ifndef ICM20948_final_h
  #define ICM20948_final_h
  #pragma once
  #include "Arduino.h"
  #include "Arduino-ICM20948.h"
  #include <Wire.h>


  class ICM20948_final {

    private:

    public:

      ArduinoICM20948 icm20948;

      ICM20948_final();
      
      float gx();
      float gy();
      float gz();

      float ax();
      float ay();
      float az();

      float roll();
      float pitch();
      float yaw();

      void inite();

    /*
      float run_icm20948_gyro_controller(char var);
      float run_icm20948_accel_controller(char var);
      float run_icm20948_quat9_controller(bool inEuler, char var);
      void i2c_scan();
      */

  };





#endif