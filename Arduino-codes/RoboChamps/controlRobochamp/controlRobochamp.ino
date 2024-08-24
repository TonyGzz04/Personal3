/*
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

int transmission=0;
  int randomNumber=4;

RF24 radio(9,8);

const byte addresses[][6] = {"00001","00002"};



void setup() {

  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);


}

void loop() {
  radio.stopListening();
  radio.write(&randomNumber,sizeof(randomNumber));
  delay(50);
}

*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int number=123;

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;

void setup() {
  pinMode(12, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  
 radio.write(&number,sizeof(number));
 delay(5);
 
}
