#include <MotoresRave.h>
#include <Ultrasonicos.h>
#include <Ventilador.h>
#include <Flama.h>
// #include <Seguidor.h>
// #include <Servo.h>
// #include "Wire.h"

MotoresRave motores(12, 13, 11, 7, 8, 6, A0, 4, 5);
// Seguidor seguidores(3);
Ultrasonicos sensoresUltrasonicos(A1, A3, 2, A5);


//Flama flama(A4, 100);

//Servo ventiladorServo;
//Ventilador ventilador(ventiladorServo, 5);



bool vela = false;
bool fuego = false;
bool lineas = true;
bool sonics = false;
bool velaCerca = false;
byte velasApagadas = 0;
short seguidorPin = 3;
int angulo = 0;
int x = 0;
int velocidad = 200;
String command = "";

void setup() {

  Serial.begin(9600);

  pinMode(seguidorPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(seguidorPin), detectar, FALLING);
  
  motores.iniciar();
  // seguidores.iniciar();
  sensoresUltrasonicos.iniciar();
  // Wire.begin();
  
  
 // ventilador.calibrar();

}

void loop() {

    if (lineas == true){
      motores.movimiento(180,velocidad*0.75);
      delay(300);
      if (velaCerca == true){ apagarVela(); }
      lineas = false;
    }

    if (lineas == false){
      int distanciaIz = sensoresUltrasonicos.getDistanciaIz();
      int distanciaDe = sensoresUltrasonicos.getDistanciaDe();
      if ((distanciaIz > 0) && (distanciaIz < 20)){
        motores.movimiento(300, velocidad);
        delay(200);
      }
      if ((distanciaDe > 0) && (distanciaDe < 20)){
        motores.movimiento(60, velocidad);
        delay(200);
      }
      sonics = false;
    }


    if (sonics == false){
      x = request();
      if (x < 270){ motores.giro(1, velocidad*0.5); }
      else if (x > 370 && x < 640){ motores.giro(0, velocidad*0.5); } 
      else { motores.movimiento(0,velocidad); velaCerca = true; }
    }

    lineas = true;
    sonics = true; 
    
}


void apagarVela(){
  velasApagadas++; 
  velaCerca = false;
}


void detectar(){
  lineas = true;
}


int request(){
  Serial.print(12);
  String c = "";
  if (Serial.available() > 0){
    c = Serial.readStringUntil("\n");
    c.trim();
    x = c.toInt();
    x = x*4; 
    return x;
  }
}