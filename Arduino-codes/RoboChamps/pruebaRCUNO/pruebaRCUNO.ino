#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001","00002"};


int mensaje;
int transmission;

void setup() {
   Serial.begin(9600);
radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.println("Listo");
}

void loop() {
mensaje=122;
radio.write(&mensaje,sizeof(mensaje));
delay(5);

}
