#include "MotoresRave.h"
#include "Ultrasonicos.h"
#include <Servo.h>
#include "Wire.h"
// #include "Flama.h"

MotoresRave motores(12, 13, 11, 7, 8, 6, A0, 4, 5);
Ultrasonicos ultrasonicos(A1, A3, 2, 10);
// Flama flama(A2, 90);

volatile bool lineas = false;
bool sonics = true;
bool velaCerca = false;
byte velasApagadas = 0;
byte direccion = 0; // 0 (norte), 1 (este), 2 (sur), 3 (oeste)
byte direccionB = 0;
short seguidorPin = 3;
int ventiladorPin = 9;
Servo ventilador;
short flama = A2;
int angulo = 0;
int x = 0;
int velocidad = 255; 
int giros = 500;

void setup() {
  
  delay(1000);
  ventilador.attach(ventiladorPin);
  ventilador.write(170);
  delay(2000);
  ventilador.write(10);
  
  
  Serial.begin(9600);

  motores.iniciar();
  ultrasonicos.iniciar();

  pinMode(flama,INPUT_PULLUP);
  pinMode(seguidorPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(seguidorPin), detectar, FALLING);

  motores.giro(0,velocidad*0.5);
  delay(giros);
  motores.alto();
  direccion = 3;
  direccionB = 0;

}

void loop() {
  
  motores.movimiento(0,velocidad);

  if (lineas == true){
    if (velaCerca == true){
      motores.movimiento(180,velocidad*0.5);
      delay(500);
      motores.alto();
      apagarVela();
      lineas = false;
    }
    else {
      motores.movimiento(180,velocidad*0.5);
      delay(500);
      motores.alto();
      if (digitalRead(flama) == true){ apagarVela(); }
      else if (direccion == 3) {
        lineas = false;
        motores.giro(1,velocidad*0.5);
        direccion = 0;
        direccionB = 3;
        delay(giros);
        motores.alto();
        delay(giros);
        motores.movimiento(0,velocidad);
        int timeStamp = millis();
        while ((millis() - timeStamp) < giros){ 
          if (lineas == true) { motores.alto(); break; } 
        }
        if (lineas == false) {
          motores.giro(1,velocidad*0.5);
          delay(giros);
          motores.alto();
          delay(giros);
          direccion = 1;
          direccionB = 0;
        }
      }
      else if (direccion == 1){   
        lineas = false;
        motores.giro(0,velocidad*0.5);
        direccion = 0;
        direccionB = 1;
        delay(giros);
        motores.alto();
        delay(giros);
        motores.movimiento(0,velocidad);
        int timeStamp = millis();
        while ((millis() - timeStamp) < giros){ 
          if (lineas == true) { motores.alto(); break; } 
        }
        if (lineas == false) {
          motores.giro(0,velocidad*0.5);
          delay(giros);
          motores.alto();
          delay(giros);
          direccion = 3;
          direccionB = 0;
        }
      }
      else if (direccion == 0){
        if (digitalRead(flama) == true){ apagarVela();}
        else if (direccionB == 3){
          motores.giro(1,velocidad*0.5);
          delay(giros);
          motores.alto();
          delay(giros);
          direccion = 1;
          direccionB = 0;
        }
        else if (direccionB == 1){
          motores.giro(0,velocidad*0.5);
          delay(giros);
          motores.alto();
          delay(giros);
          direccion = 3;
          direccionB = 0;
        }
      }
    }
  }
  
  if (lineas == false){
   
      int distanciaIz = ultrasonicos.getDistanciaIz();
      int distanciaDe = ultrasonicos.getDistanciaDe();

      if ((distanciaIz > 0) && (distanciaIz < 20)){
        motores.giro(1, velocidad*0.75);
        delay(500);
        motores.alto();
      }
          
      if ((distanciaDe > 0) && (distanciaDe < 20)){
        motores.giro(0, velocidad*0.75);
        delay(500);
        motores.alto();
      }
    
    

    sonics = false;
  }


  // if (sonics == false){
  //   x = getInfo();
  //   Serial.println(x);
  //   if (x > 370 && x < 640) {
  //     motores.giro(1,velocidad*0.75);
  //     delay(100);
  //   }
  //   else if (x < 270){
  //     motores.giro(0,velocidad*0.75);
  //     delay(100);
      
  //   }
  //   else if (x >= 270 && x <= 370){
  //     motores.movimiento(0,velocidad);
  //     if (digitalRead(flama) == true){ velaCerca = true; }
  //   }
  // }

  sonics = true;
  

}


void detectar(){
  lineas = true;
}


void apagarVela(){
  Serial.println("1");
  delay(1000);
  ventilador.write(100);
  delay(2000);
  ventilador.write(0);
  delay(3000);
  if (digitalRead(flama) == true){ 
    Serial.println("2");
    ventilador.write(100);
    delay(2000);
    ventilador.write(0);
  }
  velasApagadas++;
}


int getInfo(){
  // Wire.begin(9);
  // delay(10);
  // Wire.onReceive(receiveEvent);
  // delay(10);
  // Wire.end();
  // return x*4;
  String str = "";
  while (!(Serial.available() > 0)){}
  while (Serial.available() > 0){
    char c = '.';
    int lectura = 0;
    lectura = Serial.read();
    if (isnan(lectura)){break;}
    c = asciiToChar(lectura);
    str += c; 
  }
  delay(5);
  while (Serial.available() > 0){
    char c = '.';
    int lectura = 0;
    lectura = Serial.read();
    if (isnan(lectura)){break;}
    c = asciiToChar(lectura);
    str += c; 
  }
  x = str.toInt();

    Serial.println(x);
    return x;
  
}


void receiveEvent(int mensaje){
  while (!(Wire.available() > 0)){}
  if (Wire.available() > 0){
    x = Wire.read();
  }
}


char asciiToChar(int asciiValue) {
  if (asciiValue >= 0 && asciiValue <= 127) {
    return static_cast<char>(asciiValue); // Convert ASCII value to char
  } else {
    return '\0'; // Invalid ASCII value
  }
}