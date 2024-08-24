// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// RF24 radio(7, 8); // CE, CSN

// const int addresses[][6] = {"00001", "00002"};
// int info;

// void setup() {
//   Serial.begin(9600);
//   Serial.println(0);
//   radio.openWritingPipe(addresses[0]);
//   Serial.println(0);
//   radio.openReadingPipe(1,addresses[1]);
//   radio.setPALevel(RF24_PA_MIN);
//   radio.startListening();
  

// }

// void loop() {
//   if (radio.available()){
//     Serial.println(1);
//     radio.read(&info,sizeof(info));
//     Serial.println(info);
//   }
//   //else {Serial.println(0);}

// }


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    int text=0;
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
  else {Serial.println(10);}
}
