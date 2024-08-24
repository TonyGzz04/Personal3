#include "ICM20948_final.h"
#include <SoftwareSerial.h>

ICM20948_final icm;

// SoftwareSerial gps(4, 3);  // checar si son válidos para ESP8266

char buffer[100];


void setup() {
  Serial.begin(115200);
  icm.inite();
  // gps.begin(115200);
}

void loop() {
  float gx = icm.gx();
  float gy = icm.gy();
   float gz = icm.gz();
  float wTot = sqrt(gx*gx+gy*gy+gz*gz);
  // float aTot = sqrt(icm.ax()*icm.ax()+icm.ay()*icm.ay()+icm.az()*icm.az());
  float* loc[] = {readGPS()}; // AGREGAR VELOCIDAD LINEAL

  Serial.print(millis()); Serial.print(",");
  Serial.print(wTot); Serial.print(",");
  Serial.print(0); Serial.print(",");
  Serial.print(0); Serial.print(",");
  Serial.print(0); Serial.print(",");
  Serial.print(icm.roll()); Serial.print(","); delay(10);
  Serial.print(icm.pitch()); Serial.print(","); delay(10);
  Serial.print(icm.yaw()); Serial.print(",");delay(10);
  Serial.print(icm.gx()); Serial.print(",");delay(10);
  Serial.print(icm.gy()); Serial.print(",");delay(10);
  Serial.print(icm.gz()); Serial.print(",");delay(10);
  Serial.print(icm.ax()); Serial.print(",");delay(10);
  Serial.print(icm.ay()); Serial.print(",");delay(10);
  Serial.print(icm.az()); Serial.print(",");delay(10);
  Serial.print(icm.gx()); Serial.print(",");delay(10);
  Serial.print(icm.gy()); Serial.print(",");delay(10);
  Serial.println(0);
  


  // Imprimir valores
  // sprintf(buffer,"%d,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", millis(), wTot, loc[1], loc[2], loc[3], icm.roll(), icm.pitch(), 
          // cm.yaw(), icm.gx(), icm.gy(), icm.gz(), icm.ax(), icm.ay(), icm.az(), aTot);

  delay(10);


}




float* readGPS(){
  // while (gps.available() > 0){
  //     // get the byte data from the GPS
  //     byte gpsData = gps.read();
  //     // Serial.write(gpsData);
  // }
  float lon = 0;
  float lat = 0;
  float vel = 0;
  float loc[3] = {lon,lat,vel};
  return loc;
}
