#include "Ultrasonicos.h"
#include "MotoresRave.h"
#include "Flama.h"
#include "Seguidor.h"
#include "Ventilador.h"

const short valorVela = 50;
const short propellerPin = 5;
int timeStamp = 0;
byte velasApagadas = 0;
bool wait = false;
bool lineas =  true;
bool sonics = true;
bool velaCerca = false;

Flama flama(A5, valorVela); // pin, valor de vela máximo
Ultrasonicos sonic(9, 17, 10, 18); // trigIz, echoIz, trigDe, echoDe
MotoresRave motores(12, 13, 11, 7, 8, 6, 2, 4, 3); // derecha, izquierda, atrás, viéndolo de frente
Seguidor seguidores(14, 15, 16);  // adelante, izquierda, derecha
Ventilador propeller(5);




void setup(){

  Serial.begin(9600);

  propeller.calibrar();
  sonic.iniciar();
  motores.iniciar();
  seguidores.iniciar();


}  // cierra void setup




void loop(){

  // LINEAS
  if (true){
    if (seguidores.lineaCheckIndividual(1)){      // ve línea al CENTRO
      stop();    
      if (flama.check() == true){
        timeStamp = back();
        propeller.fuego();
        if (flama.check() == true){ propeller.fuego(); }
        if (flama.check() == false){ velasApagadas++; }
      }
    }

    if (seguidores.lineaCheckIndividual(2) == true) {     // ve línea a la DERECHA
      timeStamp = derecha90();
    
    }
    
    if (seguidores.lineaCheckIndividual(3) == true) {   // ve línea a la IZQUIERDA
      timeStamp = izquierda90();
    }
    lineas = false;
  }


  // ULTRASONICOS
  if (lineas == false){
    if (velaCerca == false){    // barrera?
      if ((sonic.getDistanciaDe() <= 5) || (sonic.getDistanciaIz() <= 5)){ stop(); }
      sonics = false;
    }
    else { // hay vela cerca
      // apagarVela();
      sonics = false;
    }
  }


  // VISIÓN
  if (sonics == false){
    if (Serial.available()){
      String command = Serial.readString();
      String x = getCoordenadaX(command);

      if (command == "1"){  // barrera
      }
      else if (command == "2"){  // vela prendida

      }
      else if (command == "3"){  // vela apagada
      }
    }
  }

  // MOVIMIENTO
  if (wait == true){
    if ((millis()-timeStamp) >= 500){
      stop();
      wait = false;
    }
  }

  sonics = true;

}  // cierra void loop




//
//              FUNCIONES
//



int back(){
  motores.movimiento(180,200);
  int timeStamp = millis();
  wait = true;
  return timeStamp;
}

int izquierda(){
  motores.movimiento(270,200);
  int timeStamp = millis();
  wait = true;
  return timeStamp;
}

int derecha(){
  motores.movimiento(90,200);
  int timeStamp = millis();
  wait = true;
  return timeStamp;
}

int derecha90(){
  motores.giro(1);
  int timeStamp = millis();
  wait = true;
  return timeStamp;
}

int izquierda90(){
  motores.giro(1);
  int timeStamp = millis();
  wait = true;
  return timeStamp;
}

void stop(){
  motores.movimiento(0,0);
}

String getCoordenadaX(String command){
  int nueve = command.indexOf('9');
  String x = command.substring(nueve);
  return x;  
}









/*
void velaAlCentro(){
  short error = 5;
  if (flama.degreePromedio() < 90){
    while ((flama.checkPromedio() >= (valorVela - error)) && (flama.checkPromedio() <= (valorVela + error))){
      motores.giro(0);  // giro izquierda
      delay(10);
    }
  }
  else if (flama.degreePromedio() > 90){
    while ((flama.checkPromedio() >= (valorVela - error)) && (flama.checkPromedio() <= (valorVela + error))){
      motores.giro(1);  // giro derecha
      delay(10);
    }
  }
}
*/
