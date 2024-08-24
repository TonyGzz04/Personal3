#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

const byte verde=7;
const byte boton1=5;
const byte boton2=6;
const byte sw=53;
const int Jx1=A0;
const int Jy1=A1;
const int Jx2=A2;
const int Jy2=A3;
int transmission=0;
int Vx1=0;
int Vy1=0;
int Vx2=0;
int Vy2=0;

RF24 radio(9,8);

const byte addresses[][6] = {"00001","00002"};


void setup() {

  pinMode(verde,OUTPUT);
  
  pinMode(boton1,INPUT_PULLUP);
  pinMode(boton2,INPUT_PULLUP);
  pinMode(sw,INPUT_PULLUP);

  radio.begin();
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
    radio.setPALevel(RF24_PA_MIN);
    
    radio.startListening();

    if (radio.available()){
        radio.read(&transmission,sizeof(transmission));
        delay(5);
        radio.stopListening();
        delay(50);
        radio.write(&transmission,sizeof(transmission));
        delay(50);
        radio.startListening();
    }

    if (radio.available()){
        radio.read(&transmission,sizeof(transmission));
        delay(5);
        radio.stopListening();
        delay(50);
        
       if (transmission==1){
        digitalWrite(verde,HIGH);
        delay(200);
        digitalWrite(verde,LOW);
       }
    }
}




void loop() {

  Vx1=analogRead(Jx1);
  radio.write(&Vx1,sizeof(Vx1));
  delay(10);

  Vy1=analogRead(Jy1);
  radio.write(&Vx1,sizeof(Vx1));
  delay(10);

  Vx2=analogRead(Jx2);
  radio.write(&Vx2,sizeof(Vx2));
  delay(10);

  Vx2=analogRead(Jy2);
  radio.write(&Vy2,sizeof(Vy2));
  delay(10);

  
  radio.startListening();
  radio.read(&transmission,sizeof(transmission));
  if (transmission==101){
    digitalWrite(verde,HIGH);
  }
  else {digitalWrite(verde,LOW);}
  radio.stopListening();
  delay(5);

  radio.write(&Vx2,sizeof(Vx2));
  

}
