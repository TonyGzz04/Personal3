#include <Servo.h>

const byte botonPin = 2;
short vel = 0;


Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;


void setup() {
    Serial.begin(9600);

    motor1.attach(2);
    motor2.attach(3);
    motor3.attach(4);
    motor4.attach(5);

    pinMode(botonPin,INPUT_PULLUP);
    delay(100);

    attachInterrupt(digitalPinToInterrupt(botonPin), blinkVoid, CHANGE);

    delay(1000);
    motor1.write(180);
    motor2.write(180);
    motor3.write(180);
    motor4.write(180);
    delay(2000);
    for (int i=150; i>-1; i=i-1){
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
    delay(2000);
    Serial.println("Calibrado!");
  
}

void loop() {

    vel=80;
    motor1.write(vel);
    motor2.write(vel);
    motor3.write(vel);
    motor4.write(vel);

    Serial.println("En el loop");

    Serial.println(digitalRead(2));
    
}



void blinkVoid(){
  delay(1000);
  
  Serial.println("¡SALIMOS!");
  
    motor1.write(0);
    motor2.write(0);
    motor3.write(0);
    motor4.write(0);

    motor1.detach();
    motor2.detach();
    motor3.detach();
    motor4.detach();

}
