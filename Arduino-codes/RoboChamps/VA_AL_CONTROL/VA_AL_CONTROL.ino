#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001","00002"};


int mensaje;
int transmission;
int x=0;
int valor;
int valorP;
const int SG=29;
const int Sshooter=28;
int stateSG=0;
int stateSshooter=0;


void setup() {

  pinMode(SG,INPUT_PULLUP);
  pinMode(Sshooter,INPUT_PULLUP);
  
  Serial.begin(9600);
radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  int number=random(0,10);

  radio.write(&number,sizeof(number));
  Serial.println("Ya1");
  delay(5);
  radio.startListening();
  delay(10);

while (!(radio.available())){
  radio.stopListening();
  delay(5);
  radio.write(&number,sizeof(number));
  Serial.println("Ya1");
  radio.startListening();
  delay(5);
  }
  if (radio.available()){
    radio.read(&transmission,sizeof(transmission));

    if (transmission==number){
       radio.stopListening();
       delay(5);
       mensaje=12;
       radio.write(&mensaje,sizeof(mensaje));
       Serial.println("connected");
    }
    
  }

}

void loop() {
  valor=analogRead(A0);
  valorP=map(valor,0,1023,0,20);
  radio.write(&valorP,sizeof(valorP));
  Serial.println(valorP);


stateSG=digitalRead(SG);
if (stateSG==LOW){
  mensaje=2222;
  radio.write(&mensaje,sizeof(mensaje));
}

stateSshooter=digitalRead(SS);
if (stateSshooter==LOW){
  mensaje=3333;
  radio.write(&mensaje,sizeof(mensaje));
}

}
