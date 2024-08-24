#include "MotoresRave.h"

MotoresRave motores(12, 13, 11, 7, 8, 6, A0, 4, 5);

void setup(){
  Serial.begin(9600);
  motores.iniciar();
}

void loop(){
  motores.giro(0,255*0.5);
}


void adelante(){
  motores.movimiento(0,255*0.5);
}