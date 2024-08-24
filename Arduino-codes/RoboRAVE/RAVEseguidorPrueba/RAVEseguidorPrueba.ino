#include "Seguidor.h"

Seguidor seguidores(14, 15, 16);

void setup() {
  Serial.begin(9600);
  seguidores.iniciar();
}

void loop() {

  Serial.println(digitalRead(15));
  
  // if (seguidores.lineaCheckIndividual(1)){
  //   Serial.println("Línea Adelante");
  // }
  // if (seguidores.lineaCheckIndividual(2) == true){
  //   Serial.println("Línea derecha");
  // }
  // if (seguidores.lineaCheckIndividual(3) == true){
  //   Serial.println("Línea izquierda");
  // }
  

}



