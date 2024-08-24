#include "MotoresRave.h"
#include "Ultrasonicos.h"
#include <Servo.h>
// #include "Flama.h"

MotoresRave motores(12, 13, 11, 7, 8, 6, A0, 4, 5);
Ultrasonicos ultrasonicos(A1, A3, 2, 10);
// Flama flama(A2, 90);

bool lineas = false;
bool sonics = true;
bool velaCerca = false;
byte velasApagadas = 0;
short seguidorPin = 3;
int ventiladorPin = 9;
Servo ventilador;
short flama = A2;
int angulo = 0;
int x = 0;
int velocidad = 255; 

void setup() {
  
  delay(1000);
  ventilador.attach(ventiladorPin);
  ventilador.write(25);
  delay(2000);
  ventilador.write(10);
  
  
  Serial.begin(9600);

  motores.iniciar();
  ultrasonicos.iniciar();

  pinMode(flama,INPUT_PULLUP);
  pinMode(seguidorPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(seguidorPin), detectar, FALLING);

}

void loop() {
  
  motores.movimiento(0,velocidad);
  delay(150);

  if (digitalRead(flama) == true){
    apagarVela();
  }

  if (lineas == true){
    if (velaCerca == true){
      motores.alto();
      apagarVela();
      lineas = false;
    }
    else {
      motores.movimiento(180,velocidad*0.5);
      delay(500);
      motores.alto();
      delay(500);
      motores.giro(0,velocidad*0.5);
      delay(200);
      motores.alto();
      delay(500);
      lineas = false;
    }
  }
  
  if (lineas == false){
    int distanciaIz = ultrasonicos.getDistanciaIz();
    int distanciaDe = ultrasonicos.getDistanciaDe();

    if ((distanciaIz > 0) && (distanciaIz < 20)){
      motores.alto();
      delay(250);
      motores.giro(1, velocidad*0.75);
      delay(100);
    }
        
    if ((distanciaDe > 0) && (distanciaDe < 20)){
      motores.alto();
      delay(250);
      motores.giro(0, velocidad*0.75);
      delay(100);
      
    }

    sonics = false;
  }

  if (sonics == false){
    x = getInfo();
    if (x > 420 && x < 640) {
      motores.giro(1,velocidad*0.75);
      delay(100);
    }
    else if (x > 5 && x < 220){
      motores.giro(0,velocidad*0.75);
      delay(100);
      
    }
    else if (x >= 220 && x <= 420){      
      motores.movimiento(0,velocidad);
      int distanciaIz = ultrasonicos.getDistanciaIz();
      int distanciaDe = ultrasonicos.getDistanciaDe();
      if (digitalRead(flama) == true){ velaCerca = true; apagarVela(); }
      else if (distanciaIz <= 20 || distanciaDe <= 20) { apagarVela(); }
    }
  }

  sonics = true;

}


void detectar(){
  lineas = true;
}


void apagarVela(){
  Serial.println("1");
  delay(1000);
  ventilador.write(30);
  delay(2000);
  ventilador.write(0);
  delay(3000);
  if (digitalRead(flama) == true){ 
    Serial.println("2");
    ventilador.write(30);
    delay(2000);
    ventilador.write(0);
  }
  velaCerca = false;
  velasApagadas++;
}


int getInfo(){
  Serial.println(12);
  String c = "";
  while (!(Serial.available() > 0)){}
  if (Serial.available() > 0){
    c = Serial.readStringUntil('\n');
    c.trim();
    x = c.toInt();
    int y = x*4;
    return y;
  }
}


// void receiveEvent(int mensaje){
//   while (!(Wire.available() > 0)){}
//   if (Wire.available() > 0){
//     x = Wire.read();
//   }
// }


// char asciiToChar(int asciiValue) {
//   if (asciiValue >= 0 && asciiValue <= 127) {
//     return static_cast<char>(asciiValue); // Convert ASCII value to char
//   } else {
//     return '\0'; // Invalid ASCII value
//   }
// }