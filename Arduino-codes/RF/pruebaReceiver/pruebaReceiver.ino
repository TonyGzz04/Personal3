#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address1[6] = "00001";
const byte address2[6] = "00002";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address1);
  radio.openReadingPipe(1,address2);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  radio.startListening();
  delay(5);
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
  radio.stopListening();
  delay(5);
  int transmission=2020;
  radio.write(&transmission,sizeof(transmission));
}
