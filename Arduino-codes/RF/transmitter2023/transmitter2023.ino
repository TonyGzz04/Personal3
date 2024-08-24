


// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// RF24 radio(5, 6); // CE, CSN

// const byte addresses[][6] = {"00001", "00002"};
// int mensaje = 1007;

// void setup() {
//   Serial.begin(9600);
//   radio.openWritingPipe(addresses[1]);
//   radio.openReadingPipe(1,addresses[0]);
//   radio.setPALevel(RF24_PA_MIN);
//   radio.stopListening();

// }

// void loop() {
//   radio.write(&mensaje,sizeof(mensaje));
//   delay(100);

// }


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const int text = 997;
  radio.write(&text, sizeof(text));
  delay(1000);
}