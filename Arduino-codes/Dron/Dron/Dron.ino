#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Servo.h>
#include <IRremote.h>

const byte rojoRGB1=2;
const byte verdeRGB1=3;
const byte azulRGB1=4;
const byte rojoRGB2=5;
const byte verdeRGB2=6;
const byte azulRGB2=7;
const short trigPin=0;
const short echoPin=0;
const short distanciaPiso=0;
const short irPin=0;
short alturaP1;
short alturaP2;
short velocidad;
short distanciaP1;
short distanciaP2;
byte buzzer=12;
int transmission=0;
int VxD=0;
int VyD=0;
int VxI=0;
int VyI=0;
int vVxD;
int vVyD;
int vVxI;
int vVyI;
int motor1vel=0;
int motor2vel=0;
int motor3vel=0;
int motor4vel=0;
int arrVarInt[]={velocidad,alturaP1,alturaP2,distanciaP1,distanciaP2}; 
int16_t altura=0;
int16_t tiempo=0;
int16_t tiempoInicial=0;
int16_t VzInicial=0;
int16_t VzFinal=0;
boolean x;
boolean y;
boolean z;
boolean a;
boolean estado;
boolean droneState;
String mensaje;
String transmissionR;
String SVxD;
String SVyD;
String SVxI;
String SVyI;
String colorFrente="";
String colorAtras="";

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

IRrecv ir(irPin);
decode_results results;

RF24 radio(7,8);

const short addresses[][19] = {"Redsupergiantstar1","Redsupergiantstar2"};








void setup() {

    pinMode(buzzer,OUTPUT);
    pinMode(rojoRGB1,OUTPUT);
    pinMode(rojoRGB2,OUTPUT);
    pinMode(verdeRGB1,OUTPUT);
    pinMode(verdeRGB2,OUTPUT);
    pinMode(azulRGB1,OUTPUT);
    pinMode(azulRGB2,OUTPUT);

    motor1.attach(8);
    motor2.attach(9);
    motor3.attach(10);
    motor4.attach(11);

    Wire.begin();

    ir.enableIRIn();
    ir.blink13(true);

    radio.begin();
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
    radio.setPALevel(RF24_PA_MIN);
    
    radio.startListening();

    boolean xx=0;
    while (xx==0){
      if (radio.available()){
        radio.read(&transmission,sizeof(transmission));
        radio.stopListening();
        delay(15);
        radio.write(&transmission,sizeof(transmission));
        radio.startListening();

        boolean yy=0;
        while (yy==0){
          if (radio.available()){
            radio.read(&transmission,sizeof(transmission));
            delay(5);
            radio.stopListening();

            if (transmission==5){
              tone(buzzer,400,100);
              rgb1('v'); rgb2('v');
              delay(100);
              rgb1('-'); rgb2('-');
              delay(100);
              tone(buzzer,400,100);
              rgb1('v'); rgb2('v');
              delay(100);
              rgb1('-'); rgb2('-');
              delay(400);
              yy=1;
            }
            
          } //cierra if transmisión conexión 2
        } //cierra while transmisión conexión 2
      } //cierra if transmisión conexión 1
      xx=1;
    } //cierra while transmisión conexión 1

        radio.startListening();

    boolean zz=0;
    while (zz==0){ //while drone or plane
        if (radio.available()){
          radio.read(&estado,sizeof(estado));
          delay(5);
          tone(buzzer,900,100);
          delay(100);
          zz=1;
        }
    } //cierra while drone or plane

    boolean aa=0;
    while (aa == 0){
      if (radio.available()){
        radio.read(&flyState,sizeof(flyState));
        tone(buzzer,900,100);
        delay(150); 
        tone(buzzer,900,100);
        delay(100);
        aa=1;
      }
    } //cierra while estado del vuelo

    if (flyState == 0){ 
      for (byte i=0; i<2; i++){
        tone(buzzer,400,500+i*1000);
        rgb1('v');
        rgb2('v');
        delay(500+i*1000);
        rgb1('-');
        rgb2('-');
        delay(500);
      }
     }
    else{
      rgb1('r');
      rgb2('r');
      constantBuzzerBeat(2,1000,247);
    }

    aa=0;
    while (aa == 0){
      if (radio.available()){
        radio.read(&droneState,sizeof(droneState));
        tone(buzzer,900,100);
        delay(150); 
        tone(buzzer,900,100);
        delay(100);
        aa=1;
      }
    } //cierra while estado del dron

    if (droneState == 0){ 
      for (byte i=0; i<3; i++){
        rgb1('v');
        rgb2('v');
        delay(150);
        rgb1('-');
        rgb2('-');
        delay(150);
      }
     }
    else if (droneState == 1){
      rgb1('r');
      rgb2('r');
      constantBuzzerBeat(2,1000,247);
    }

    mensaje=10;
    radio.stopListening();
    delay(5);
    radio.write(&mensaje,sizeof(mensaje));
    for (byte i=0; i<3; i++){   // iniciará calibración
      rgb1('a');
      rgb2('a');
      tone(buzzer,49,1000);
      delay(1000);
      rgb1('-');
      rgb2('-');
      delay(1000);
    }

    //CALIBRACIÓN
  
    delay(1000);
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
    delay(2000);
    mensaje=120120;
    radio.stopListening();
    delay(5);
    radio.write(&mensaje,sizeof(mensaje));

    

    
    
} //cierra void setup














void loop() {
  


  //RACE

  while (droneState==0){
    
    transmission=mov();

    if (ir.decode(&results)) { muerteEnPruebas(); }

    // alguna otra cosa que no sea del movimiento
    if (transmission!=1111){
      if (transmission==7777){  // cambiar colores de RGBs
        while (!(radio.available())){}
        radio.read(&colorFrente,sizeof(colorFrente)); // CHECAR que sean STRINGS
        while (!(radio.available())){}
        radio.read(&colorAtras,sizeof(colorAtras));
        //rgb1(colorFrente);
        //rgb2(colorAtras);
      }
    }

    

   
      
  

    
  } //cierra race mode






  //SMOOTH

  while (droneState==1){
    
  } //cierra smooth mode
    
} //cierra void loop





























                                  // FUNCIONES

                                  
char rgb1(char color){    // FRENTE
  short rojo=0; short verde=0; short azul=0;
  switch (color){
    case 'r': rojo=255; break;
    case 'v': verde=255; break;
    case 'z': azul=255; break;
    case 'n': rojo=243; verde=156; azul=18; break;
    case 'a': rojo=255; verde=251; break; // amarillo
    case '-': break; 
    case 'c': verde=255; azul=243; break;
    case 'o': rojo=201; azul=255; break;
    case 's': rojo=255; verde=121; azul=247; break;
  }
  analogWrite(rojoRGB1,rojo);
  analogWrite(verdeRGB1,verde);
  analogWrite(azulRGB1,azul);
} // cierra función rgb1("")
  


char rgb2(char color){    // ATRÁS
  short rojo=0; short verde=0; short azul=0;
  switch (color){
    case 'r': rojo=255; break;
    case 'v': verde=255; break;
    case 'z': azul=255; break;
    case 'n': rojo=243; verde=156; azul=18; break;
    case 'a': rojo=255; verde=251; break; // amarillo
    case '-': break; 
    case 'c': verde=255; azul=243; break;
    case 'o': rojo=201; azul=255; break;
    case 's': rojo=255; verde=121; azul=247; break;
  }
  analogWrite(rojoRGB2,rojo);
  analogWrite(verdeRGB2,verde);
  analogWrite(azulRGB2,azul);
} // cierra función rgb2("")


int imuAltura(){
  
}



int mov(){
  radio.startListening();
  delay(5);
  while (!(radio.available())){}
  radio.read(&transmission,sizeof(transmission));
  if (transmission==1111){ 
    while (!(radio.available())){}
    radio.read(&VxD,sizeof(VxD));
    while (!(radio.available())){}
    radio.read(&VyD,sizeof(VyD));
    while (!(radio.available())){}
    radio.read(&VxI,sizeof(VxI));
    while (!(radio.available())){}
    radio.read(&VyI,sizeof(VyI));
  }
  else { return transmission; }


  if (VyD>=181) {}     //no hace nada, valor de error
  else if (VxD==VyD) { // si no hay movimiento en el joystick derecho
    motores(VyI,VyI,VyI,VyI); 
  }
  
  else {               // si sí hay movimiento en el joystick derecho
    if (VxD>=90 && VyD>=90) {  // derecha y adelante
      motor1vel=VyI-(VyI*map(VyD,90,180,0,25)/100);
      motor2vel=VyI-(VyI*map(VxD,90,180,0,25)/100)-(VyI*map(VyD,90,180,0,25)/100);
      motor3vel=VyI;
      motor4vel=VyI-(VyI*map(VxD,90,180,0,25)/100);
    }
    else if (VxD>=90 && VyD<90) {  // derecha y atrás
      motor1vel=VyI;
      motor2vel=VyI-(VyI*map(VxD,90,180,0,25)/100);
      motor3vel=VyI-(VyI*map(VyD,0,90,0,25)/100);
      motor4vel=VyI-(VyI*map(VxD,90,180,0,25)/100)-(VyI*map(VyD,0,90,0,25)/100);
    }
    else if (VxD<90 && VyD>=90) {  // izquierda y adelante
      motor1vel=VyI-(VyI*map(VxD,0,90,0,25)/100)-(VyI*map(VyD,90,180,0,25)/100);;
      motor2vel=VyI-(VyI*map(VxD,0,90,0,25)/100);
      motor3vel=VyI-(VyI*map(VyD,90,180,0,25)/100);
      motor4vel=VyI-(VyI*map(VxD,0,90,0,25)/100)-(VyI*map(VyD,90,180,0,25)/100);
    }
    else if (VxD<90 && VyD<90) {  // izquierda y atrás
      motor1vel=VyI-(VyI*map(VxD,0,90,0,25)/100)-(VyI*map(VyD,0,90,0,25)/100);;
      motor2vel=VyI-(VyI*map(VxD,0,90,0,25)/100);
      motor3vel=VyI-(VyI*map(VyD,0,90,0,25)/100);
      motor4vel=VyI-(VyI*map(VxD,0,90,0,25)/100)-(VyI*map(VyD,0,90,0,25)/100);
    }
    else if (VxD>=90) { // derecha
      motor1vel=VyI;
      motor2vel=VyI-(VyI*map(VxD,90,180,0,25)/100);
      motor3vel=VyI;
      motor4vel=motor2vel;
    }
    else if (VxD<90) { // izquierda
      motor1vel=VyI-(VyI*map(VxD,0,90,0,25)/100);
      motor2vel=VyI;
      motor3vel=motor1vel;
      motor4vel=VyI;
    }
    else if (VyD>=90) { // adelante
      motor1vel=VyI-(VyI*map(VyD,90,180,0,25)/100);
      motor2vel=motor1vel;
      motor3vel=VyI;
      motor4vel=VyI;
    }
    else if (VyD<=90) { // atrás
      motor1vel=VyI;
      motor2vel=VyI;
      motor3vel=VyI-(VyI*map(VyD,0,90,0,25)/100);
      motor4vel=motor3vel;
    }
    motores(motor1vel,motor2vel,motor3vel,motor4vel);
  }
}       // cierra función de movimiento



void motores(int e, int f, int g, int h){
    motor1.write(e);
    motor2.write(f);
    motor3.write(g);
    motor4.write(h);
}

int ultrasonico(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  int duracion=pulseIn(echoPin,HIGH);
  float distancia=(duracion/2)/29.1;
  return distancia;
}


void muerte(short error){
  rgb1('r');  rgb2('r');
  float previousTime=millis();

  while (altura*100 > distanciaPiso+100){
    while (velY > 0.1){
      motor1vel--; motor2vel--; motor3vel--; motor4vel--;
      motores(motor1vel,motor2vel,motor3vel,motor4vel);
      delay(5);
      if ((millis()-previousTime)%1000 == 0) {tone(buzzer,400,100);}
      if (ultrasonico() <= 100) { break; }
    }
    if ((millis()-previousTime)%1000 == 0) {tone(buzzer,400,100);}
    if (ultrasonico() <= 100) { break; }
  }

  while (ultrasonico >= distanciaPiso){
    motor1vel--; motor2vel--; motor3vel--; motor4vel--;
    motores(motor1vel,motor2vel,motor3vel,motor4vel);
    delay(5);
    if ((millis()-previousTime)%1000 == 0) {tone(buzzer,400,100);}
  }

  motor1.detach(); motor2.detach(); motor3.detach(); motor4.detach();
  radio.stopListening(); delay(1); mensaje=911+error; 
  previousTime=millis();
  
  while (1){
    radio.write(&mensaje,sizeof(mensaje));
    if ((millis()-previousTime)%1000 == 0) {
      for (int i=0; i<3; i++){
      tone(buzzer,400,500);
      delay(800);
      }
      tone(buzzer,400,2000);
     }
    }
   }


void muerteEnPruebas(){
  rgb1('r'); rgb2('r');
  motores(50,50,50,50);
  delay(10000);
  motores(0,0,0,0);
  while (1){};
}


void constantBuzzerBeat(int seconds, int duration, int hz){
  float previousTime=millis();

  while (1){
    if ((millis()-previousTime)%(seconds*1000)==0){
      tone(buzzer,hz,duration);
    }
  }
}
