/*

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

int transmission=0;

RF24 radio(9,8);

const byte addresses[][6] = {"00001","00002"};


void setup() {

  Serial.begin(9600);
  
 radio.begin();
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
    radio.setPALevel(RF24_PA_MIN);
    
    radio.startListening();


    
}

void loop() {
  
    if (radio.available()){
        radio.read(&transmission,sizeof(transmission));
        delay(5);
        Serial.println(transmission);
    }
}

*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int number;

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

void setup() {

  Serial.begin(9600);
 
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  radio.startListening();
  if (radio.available()) {
    radio.read(&number,sizeof(number));
    delay(5);
    Serial.println(number);
  }
}
