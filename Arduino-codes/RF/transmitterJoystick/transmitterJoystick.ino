#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);

const byte addresses[][6] = {"00001","00002"};
const int greenLEDpin=7;
const int blueLEDpin=2;
const int VRx=A0;
const int VRy=A1;
long startNumber=0;
long transmission=0;



void setup(){
  pinMode(blueLEDpin,OUTPUT);
  pinMode(greenLEDpin,OUTPUT);
  
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.setPALevel(RF24_PA_MIN);

  startNumber=1;
 

  
}

void loop(){
   radio.write(&startNumber, sizeof(startNumber));

  delay(5);

  radio.startListening();
  
  if (radio.available()){
    while (radio.available()){
    radio.read(&transmission, sizeof(transmission));
    
    if (startNumber==transmission){
      digitalWrite(greenLEDpin,HIGH);
    }
    }
     radio.stopListening();
  }

}
