#include "Ventilador.h"

Ventilador propeller(5);

void setup() {

  Serial.begin(9600);

  propeller.calibrar();

  // delay(1000);

  // propeller.write(0);
  // delay(2000);
  
  // propeller.write(140);
  // delay(1500);

  // // for (int i=0; i<171; i++){
  // //   propeller.write(i);
  // //   delay(10);
  // // }
  // // delay(2000);
  // for (int i=140; i>-1; i=i-1){
  //   propeller.write(i);
  //   delay(10);
  // }
  // delay(2000);

}

void loop() {
  
  propeller.fuego();

}
