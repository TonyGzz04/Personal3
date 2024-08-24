#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;



void setup() {
  Serial.begin(9600);

  delay(5000);

  motor1.attach(2,1000,2000);
  motor2.attach(3,1000,2000);
  motor3.attach(4,1000,2000);
  motor4.attach(5,1000,2000);

  delay(2000);

  motor1.write(170);
  motor2.write(170);
  motor3.write(170);
  motor4.write(170);
  Serial.println("170");

  delay(2000);

  for (int i=170; i>-1; i=i-1){
    motor1.write(i);
    motor2.write(i);
    motor3.write(i);
    motor4.write(i);
    delay(8);
    Serial.println(i);
  }

  motor1.write(0);
  motor2.write(0);
  motor3.write(0);
  motor4.write(0);

  delay(3000);

}

void loop() {
  int pot=analogRead(A0);
  int valor=map(pot,0,1023,0,150);

  motor1.write(valor);
  motor2.write(valor);
  motor3.write(valor);
  motor4.write(valor);

}
