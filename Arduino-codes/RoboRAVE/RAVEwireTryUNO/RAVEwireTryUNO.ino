#include "Wire.h"

int x = 100;
int angulo = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(9);
  Wire.onRequest(request);
  

}

void loop() {

 String c = "";
 Serial.print(12);
 while (!(Serial.read() > 0)){}
 if (Serial.available() > 0){
   c = Serial.readStringUntil("\n");
   c.trim();
   angulo = c.toInt();
 }
}


void request() {
  Wire.write(angulo);
}
