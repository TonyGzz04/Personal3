#include <Servo.h>

int pot=0;
int potV=0;
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor1.attach(2,1000,2000);
  motor2.attach(3,1000,2000);
  motor3.attach(4,1000,2000);
  motor4.attach(5,1000,2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  pot=analogRead(A0);
  potV=map(pot,0,1023,0,180);

  Serial.print(pot);
  Serial.print("    ");
  Serial.println(potV);

  motor1.write(potV);
  motor2.write(potV);
  motor3.write(potV);
  motor4.write(potV);

}
