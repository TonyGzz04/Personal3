#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx  = Adafruit_MLX90614();

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001","00002"};

Servo motor;
Servo servoG;
Servo servoS;

int mensaje;
int transmission;
byte x=0;
int SG=0;
const byte ledT = 2;
const byte led2 = 3;
double temp;
int valor;


void setup() {

  pinMode(led2,OUTPUT);
  pinMode(ledT,OUTPUT);

Serial.begin(9600);

motor.attach(11,1000,2000);
  servoG.attach(5);
  servoS.attach(4);
  
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
    radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  

  while (!(radio.available())){x=0; Serial.print("intentando");}
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
  while (!(radio.available())){x=0;}
  if (radio.available()){
    radio.read(&transmission,sizeof(transmission));
    if (transmission==12){
      Serial.println(transmission);
      Serial.println("¡Conectado!");
      digitalWrite(led2,HIGH);
      delay(500);
      
    }
  }

}






void loop() {

  /*

  temp = mlx.readObjectTempC();
  if(mlx.readObjectTempC() >= 40)
    {
      digitalWrite(ledT, HIGH);
    }
  else
  {
    digitalWrite(ledT, LOW);
  }
  */

    

  
if (radio.available()){
  radio.read(&transmission,sizeof(transmission));

  if (transmission==2222){
    if (SG=0){
    servoG.write(90);
    SG=1;
    }
    else if (SG=1){
      servoG.write(0);
       SG=0;
    }
  }

  else if (transmission==3333){
    servoS.write(90);
    delay(300);
    servoS.write(0);
  }

 else {
      motor.write(transmission);
      Serial.println(transmission);
  }

  
  }
  
}
