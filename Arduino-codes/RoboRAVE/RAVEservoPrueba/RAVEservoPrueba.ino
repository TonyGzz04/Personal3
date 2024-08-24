#include "Servo.h"
#include "Flama.h"

Servo servo;


void setup() {
  Serial.begin(9600);

  servo.attach(2);
  // servo.write(0);

}

void loop() {


  // servo.write(90);
  // Serial.println(servo.read());
  

  for (short i=0; i<181; i++){
      servo.write(i);
      delay(10);
     
    }

}
