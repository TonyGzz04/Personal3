#include <Servo.h>

int valor=0;
int valorF=0;

Servo motor;

void setup() {
  Serial.begin(9600);
  motor.attach(11,1000,2000);

}

void loop(){
  valor=analogRead(A0);
  valorF=map(valor,0,1023,0,150);
  motor.write(valorF);
  Serial.println(valorF);
  
}
