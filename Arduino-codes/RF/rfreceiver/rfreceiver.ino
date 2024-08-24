#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Servo.h>
#include <IRremote.h>

//create an RF24 object
RF24 radio(7,8);

//address through which two modules communicate.
const byte address1[6] = "00001";
const byte address2[6] = "00002";

int transmission;
int mensaje;
byte x=0;
int a=0;

/*
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
*/

void setup() {

  Serial.begin(9600);
  
  /*
    motor1.attach(8);
    motor2.attach(9);
    motor3.attach(10);
    motor4.attach(11);
    */

    Wire.begin();

   // ir.enableIRIn();
    //ir.blink13(true);

    radio.begin();
    radio.openWritingPipe(address1);
  radio.openReadingPipe(1,address2);
    radio.setPALevel(RF24_PA_MIN);
    
    radio.startListening();

    boolean xx=0;
    while (xx==0){
      if (radio.available()){
        radio.read(&transmission,sizeof(transmission));
        Serial.println(transmission);
        radio.stopListening();
        delay(500);
        radio.write(&transmission,sizeof(transmission));
        radio.startListening();
        delay(5);

        boolean yy=0;
        while (yy==0){
          if (radio.available()){
            radio.read(&transmission,sizeof(transmission));
            Serial.println(transmission);
            radio.stopListening();
            delay(5);

            if (transmission==5){
              delay(400);
              yy=1;
              xx=1;
              Serial.println("Conectado");
              radio.stopListening();
              delay(5);
              mensaje=3;
              radio.write(&mensaje,sizeof(mensaje));
              radio.startListening();
              delay(5);
            }
            
          } //cierra if transmisión conexión 2
        } //cierra while transmisión conexión 2
      } //cierra if transmisión conexión 1

      else{
        Serial.println("Nada 1");
      }
      
    } //cierra while transmisión conexión 1

    boolean zz=0;
    while (zz==0){ //while drone or plane
        if (radio.available()){
          int flyState;
          radio.read(&flyState,sizeof(flyState));
          if (flyState==0){
            Serial.println("FlyState checked");
            radio.stopListening();
            delay(5);
            mensaje=3;
            radio.write(&mensaje,sizeof(mensaje));
            radio.startListening();
            delay(5);
            delay(100);
            zz=1;
          }
          else { Serial.println("FlyState NOT checked"); while(1){}}
        }
    } //cierra while drone or plane

    boolean aa=0;
    while (aa == 0){
      if (radio.available()){
        int droneState;
        radio.read(&droneState,sizeof(droneState));
        if (droneState==0){
          Serial.println("DroneState checked");
          radio.stopListening();
          delay(5);
          mensaje=3;
          radio.write(&mensaje,sizeof(mensaje));
          radio.startListening();
          aa=1;
        }
        else { Serial.println("DroneState NOT checked"); while(1){}}
      }
    } //cierra while estado del vuelo


    /*
    aa=0;
    while (aa == 0){
      if (radio.available()){
        int droneState=0;
        radio.read(&droneState,sizeof(droneState));
        delay(100);
        aa=1;
      }
    } //cierra while estado del dron
    */

    
    radio.stopListening();
    delay(5);
    mensaje=10;
    radio.write(&mensaje,sizeof(mensaje));

    //CALIBRACIÓN

    Serial.println("Calibrando");
    delay(1000);
    /*
    motor1.write(180);
    motor2.write(180);
    motor3.write(180);
    motor4.write(180);
    delay(2000);
    for (int i=150; i>-1; i=i-1){
    motor1.write(i);
    motor2.write(i);
    motor3.write(i);
    motor4.write(i);
    delay(8);
    Serial.println(i);
  }
    motor1.write(0);
    motor2.write(0);
    motor3.write(0);
    motor4.write(0);
    */
    delay(2000);
    mensaje=120;
    radio.stopListening();
    delay(5);
    radio.write(&mensaje,sizeof(mensaje));

   
    
    
} //cierra void setup


void loop()
{

    radio.startListening();
    delay(5);
  
  if (radio.available())
  {
      radio.read(&transmission,sizeof(transmission));
      if (transmission == 2000){ Serial.println("BOTÓN!");}
      else{
      Serial.print("VX: ");
      Serial.println(transmission);
      }
      radio.read(&transmission,sizeof(transmission));
      if (transmission == 2000){ Serial.println("BOTÓN!");}
      else{
      Serial.print("VY: ");
      Serial.println(transmission);
      }
  }

}

 
