#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN

const byte addresses[][6] = {"00001", "00002"};

int mensaje;
int transmission;
int x=0;
int Vx=0;
int Vy=0;
int jUno=1111;
int jDos=2222;


void setup() {

  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  

  byte number=random(0,10);

  radio.write(&number,sizeof(number));
  delay(5);
  radio.startListening();
  delay(10);

  if (radio.available()){
    radio.read(&transmission,sizeof(transmission));

    if (transmission==number){
       radio.stopListening();
       delay(5);
       mensaje=12;
       radio.write(&mensaje,sizeof(mensaje));
       
       Serial.print(transmission);
       Serial.print(" número= ");
       Serial.println(number);
       Serial.println(" Conectado ");
    }
    
  }

  
}

void loop() {

radio.write(&jUno,sizeof(jUno));
delay(7);
Vx=analogRead(A1);
radio.write(&Vx,sizeof(Vx));
delay(5);

radio.write(&jDos,sizeof(jDos));
delay(7);
Vy=analogRead(A0);
radio.write(&Vy,sizeof(Vy));
delay(5);
}
