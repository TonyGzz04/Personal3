#include "Flama.h"

// Flama flama(A2, A0, A1, 50, 2, 3, 4); // pines 10cm, 20cm, 40cm, valor de detección de vela, pines de servos en el mismo orden

void setup() {

  Serial.begin(9600);
  // flama.iniciar();
  // flama.servoMove(3,90);
  // flama.servoMove(2,90);
  
}


void loop() {

  
  Serial.println(analogRead(A0));

}

