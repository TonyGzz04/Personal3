#include <MotoresRave.h>
#include <Ultrasonicos.h>
#include <Ventilador.h>
#include <Flama.h>
// #include <Seguidor.h>
// #include <Servo.h>
#include "Wire.h"

MotoresRave motores(12, 13, 11, 7, 8, 6, A0, 4, 5);
// Seguidor seguidores(3);
Ultrasonicos sensoresUltrasonicos(A1, A3, 2, A5);

//Flama flama(A4, 100);

//Servo ventiladorServo;
//Ventilador ventilador(ventiladorServo, 5);


int angulo = 0;
int x = 0;
bool vela = false;
bool fuego = false;
bool lineas = true;
bool sonics = false;
bool vela_prendida = false;
int velocidad = 200;
String command = "";

void setup() {

  Serial.begin(9600);

  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), detectar, RISING);
  
  motores.iniciar();
  sensoresUltrasonicos.iniciar();
  Wire.begin();
  
 // ventilador.calibrar();

}

void loop() {

  if (lineas == true){
    motores.movimiento(180,velocidad*0.75);
    delay(300);
    lineas = false;
  }

  // if (lineas == false){
  //   int distanciaIz = sensoresUltrasonicos.getDistanciaIz();
  //   int distanciaDe = sensoresUltrasonicos.getDistanciaDe();
  //   if ((distanciaIz > 0) && (distanciaIz < 20)){ motores.movimiento(300, velocidad); }
  //   if ((distanciaDe > 0) && (distanciaDe < 20)){ motores.movimiento(60, velocidad); }
  //   sonics = false; 
  // }
  
  if (sonics == false){
    Wire.requestFrom(9,1);
    if (Wire.available()){
      command = Wire.read();
      angulo = command.toInt();
      angulo = angulo*4;
      if (angulo < 270 && angulo > 0){ motores.giro(1,velocidad*0.5); }
      else if (angulo > 370 && angulo < 640){ motores.giro(0,velocidad*0.5); }
      else { motores.movimiento(0,velocidad); }
    }
  }
  
  Seria
      
}

/*void detectar(){
  delay(1000);
  motores.alto();
  delay(1000);

  if (digitalRead(A4) == 1){
    delay(2000);
  }
  
  if (digitalRead(A4) == 0){
    motores.giro(1, velocidad);
    delay(1000);
  }
}*/

void detectar(){
  lineas = true;
}