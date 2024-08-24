#include <Servo.h>

int pot=0;
int potV=0;
Servo ESC1;

void setup() {
  // put your setup code here, to run once:
  ESC1.attach(10,1000,2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  pot=analogRead(A0);
  potV=map(pot,0,1023,0,180);
  ESC1.write(potV);

}
