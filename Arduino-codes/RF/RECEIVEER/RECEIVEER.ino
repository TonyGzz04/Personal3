#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte addresses[][6] = {"00001","00002"};

int mensaje;
int transmission;
int a;
int b;
int c;
int d;
int x;
int Vx;
int Vy;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();
  Serial.println(radio.isChipConnected());

  while (!(radio.available())){int x=0;}
  
  if (radio.available()){
    radio.read(&transmission,sizeof(transmission));
    delay(5);
    Serial.println(transmission);
    radio.stopListening();
    mensaje=transmission;
    radio.write(&mensaje,sizeof(mensaje));
    delay(5); 
    radio.startListening();
  }

  while (!(radio.available())){int x=0; Serial.println("esperando");}

  if (radio.available()){
    radio.read(&transmission,sizeof(transmission));
    if (transmission==12){
      Serial.println(transmission);
      Serial.println("¡Conectado!");
      delay(500);
    }
  }


  
}

void loop() {

while (!(radio.available())) {x=0;}
if (radio.available()){
  radio.read(&transmission,sizeof(transmission));
  if (transmission==1111){
    while (!(radio.available())) {x=0;}
    radio.read(&Vx,sizeof(Vx));
    Serial.print("Vx = ");
    Serial.println(Vx);
  }
  else if (transmission==2222){
    while (!(radio.available())) {x=0;}
    radio.read(&Vy,sizeof(Vy));
    Serial.print("Vy = ");
    Serial.println(Vy);
  }
}



/*

while (!(radio.available())){x=0;}
if (radio.available()){
  radio.read(&a,sizeof(a));
  Serial.print("a=");
  Serial.println(a);
  radio.stopListening();
  delay(1);
  radio.write(&a,sizeof(a));
  radio.startListening();
  delay(5);
}

while (!(radio.available())){x=0;}
if (radio.available()){
  radio.read(&a,sizeof(a));
  Serial.print("b=");
  Serial.println(a);
  radio.stopListening();
  delay(1);
  radio.write(&a,sizeof(a));
  radio.startListening();
  delay(5);
}

while (!(radio.available())){x=0;}
if (radio.available()){
  radio.read(&a,sizeof(a));
  Serial.print("c=");
  Serial.println(a);
  radio.stopListening();
  delay(1);
  radio.write(&a,sizeof(a));
  radio.startListening();
  delay(5);
}

while (!(radio.available())){x=0;}
if (radio.available()){
  radio.read(&d,sizeof(d));
  Serial.print("d=");
  Serial.println(d);
  radio.stopListening();
  delay(1);
  radio.write(&d,sizeof(d));
  radio.startListening();
  delay(5);
}
*/



}
