#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

int Vx1=0;
int Vy1=0;
int Vx2=0;
int Vy2=0;
int stateBoton1=0;
int stateBoton2=0;
const byte azul=10;
const byte rojo=3;
const byte amarillo=5;
const byte verde=6;
const byte buzzer=2;
const byte boton1=7;
const byte boton2=4;
int transmission=0;
int mensaje=0;

RF24 radio(9,8);

const byte addresses[][6] = {"00001","00002"};

void setup() {

  pinMode(rojo,OUTPUT);
  pinMode(verde,OUTPUT);
  pinMode(amarillo,OUTPUT);
  pinMode(azul,OUTPUT);
  
  pinMode(buzzer,OUTPUT);

  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);

  int randomNumber=random(0,10);

  radio.stopListening();
  radio.write(&randomNumber,sizeof(randomNumber));
  delay(50);

  radio.stopListening();
  radio.read(&transmission,sizeof(transmission));
  delay(5);
  radio.stopListening();

  if (randomNumber==transmission){
    delay(50);
    mensaje=1;
    radio.write(&mensaje,sizeof(mensaje));
    delay(5);
    digitalWrite(verde,HIGH);
    tone(buzzer,400,100);
    delay(200);
    digitalWrite(verde,LOW);
    delay(500);
  }


}

void loop() {

  radio.startListening();
  radio.read(&Vx1,sizeof(Vx1));
  delay(5);
  radio.stopListening();
  analogWrite(azul,Vx1);

  radio.startListening();
  radio.read(&Vy1,sizeof(Vy1));
  delay(5);
  radio.stopListening();
  analogWrite(rojo,Vy1);
 
  radio.startListening();
  radio.read(&Vx2,sizeof(Vx2));
  delay(5);
  radio.stopListening();
  analogWrite(amarillo,Vx2);

  radio.startListening();
  radio.read(&Vy2,sizeof(Vy2));
  delay(5);
  radio.stopListening();
  analogWrite(verde,Vy2);

  if (stateBoton1==LOW){
  mensaje=101;
  radio.write(&mensaje,sizeof(mensaje));
  delay(5);
  }

 /* if (stateBoton2==LOW){
  mensaje=202;
  radio.write(&mensaje,sizeof(mensaje));
  delay(5);
  }
  */

}
