#include <MPU9250.h>
#include "Wire.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;

float temperature, pressure, altitude;

#include "SD.h"
char filename[] = "LOGGER00.TXT";
const int chipSelect = 10;
// the logging file
File logfile;

void setup() {
// serial to display data
Serial.begin(115200);
while(!Serial) {}

// start communication with IMU
Serial.println("IMU");
status = IMU.begin();
if (status < 0) {
Serial.println("IMU initialization unsuccessful");
Serial.println("Check IMU wiring or try cycling power");
Serial.print("Status: ");
Serial.println(status);

}
Serial.println("BMP");

Serial.println("Initializing SD card...");
pinMode(10, OUTPUT);

// see if the card is present and can be initialized:
if (!SD.begin(chipSelect)) {
Serial.println("Card failed, or not present");
// don't do anything more:
return;
}
Serial.println("card initialized.");

// create a new file

for (uint8_t i = 0; i < 100; i++) {
filename[6] = i/10 + '0';
filename[7] = i%10 + '0';
if (! SD.exists(filename)) {
logfile = SD.open(filename, FILE_WRITE);
break; // leave the loop!
}
}

if (! logfile) {
Serial.println("couldnt create file");
}

Serial.println("Logging to: ");
Serial.println(filename);

logfile.close();

logline("Accel X, Accel Y, Accel Z, Gyro X, Gyro Y, Gyro Z, Temp (Celsius), Pressure (hPa), Altitude (m)");
}

void loop() {

{
// read the sensor
IMU.readSensor();
// display the data

String s = "";
s += String(millis());
s += ", ";
s += String(IMU.getAccelX_mss());
s += ", ";
s += String(IMU.getAccelY_mss());
s += ", ";
s += String(IMU.getAccelZ_mss());
s += ", ";
s += String(IMU.getGyroX_rads() * 57.2957795);
s += ", ";
s += String(IMU.getGyroY_rads() * 57.2957795);
s += ", ";
s += String(IMU.getGyroZ_rads() * 57.2957795);
s += ", ";
s += String(temperature); 
s += ", ";
s += String(pressure);
s += ", ";
s += String(altitude); 
logline(s);
}

}

void logline(String s) {
Serial.println(s);
logfile = SD.open(filename, FILE_WRITE);
logfile.println(s);
logfile.close();
}
