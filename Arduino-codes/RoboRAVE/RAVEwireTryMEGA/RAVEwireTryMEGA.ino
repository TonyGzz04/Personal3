#include <Wire.h>

int x = 0;
int xInt = 98;
int angulo = 1;
byte byteCount = 1;

void setup() {
  Serial.begin(9600);
  // Wire.begin(9);
  //  Wire.onReceive(receiveEvent);

}

void loop() {
  // String c = "";
  // Wire.requestFrom(9, 1);
  // if (Wire.available()){
  //   x = Wire.read(); // Read the bytes and reconstruct the integer
    //Serial.println(xInt);
  // }
  // delay(100);

  // if (byteCount >= 1) {
  //   byte bytes[1];
  //   int value;

//   if (Wire.available()){
//     for (int i = 0; i < 1; i++) {
//       bytes[i] = Wire.read();
//     }
//   }

//     value = (int)(bytes[0]) | ((int)(bytes[1]) << 8);
//     Serial.print("Received value: ");
//     Serial.println(value);
// }

  if (true){  
    Wire.begin(9);
    delay(10);
    Wire.onReceive(receiveEvent);
    delay(10);
    Serial.println(x*4);
    Wire.end();
  }
  delay(10);

}

void receiveEvent(int mensaje){
  if (Wire.available() > 0){
    x = Wire.read();
  }
  
  // xInt = x.toInt();
}