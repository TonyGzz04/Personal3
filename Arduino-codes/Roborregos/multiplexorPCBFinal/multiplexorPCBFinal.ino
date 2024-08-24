#include "Motores.h"

Motores motoresRobot(8,41,27,7,25,24,6,23,22);

int degree = 0;
int comple = 0;   // ángulo complementario
int tri = 0;   // ángulo de triángulo
int spd = 0;    // velocidad
long ctime = 0;

//Variables
double DIAMETRO = 0.11; //m

int sig[3] = {A0,A1,A2}; // pines signal: DERECHA,PRINCIPAL,  DERECHA, 

const int sC[3] = {8,13,51};  // pines de 'control' ABC 
const int sB[3] = {9,11,49};
const int sA[3] = {10,12,53};

int fotoMinB[3][8] = {{100,100,100,100,100,100,100,100},{100,100,100,100,100,100,100,100},{100,100,100,100,100,100,100,100}};
int fotoMaxB[3][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};

// int fotoD[8] = {0,0,0,0,0,0,0,0};     // lecturas de los fototransistores
// int fotoI[8] = {0,0,0,0,0,0,0,0}; 
// int fotoP[8] = {0,0,0,0,0,0,0,0}; 

int fotot[3][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
double angulo[3][8] = {{271.2,279.6,287.8,296.3,307.6,315.7,323.8,332.3},{212.7,205.8,195.2,180,180,167,156,149},{88.8,80.4,72.2,63.7,52.4,36.2,27.7,44.3}};

#define blanco 20      // detección del blanco
#define error 2     // rango de detección del blanco




void setup(){
  Serial.begin(115200);

  motoresRobot.iniciar();

  pinMode(31,OUTPUT);
  pinMode(7,INPUT_PULLUP);
  
  for (int i=0; i<3; i++){  
    pinMode(sC[i],OUTPUT);
    pinMode(sB[i],OUTPUT);
    pinMode(sA[i],OUTPUT);
  }
  
  // for (int a=0; a<8; a++){
  //   for (int i=0; i<100; i++){
  //     int lec = lectura(a,0);
  //     if (lec < fotoMinB[0][a]){ fotoMinB[0][a] = lec; }
  //     else if (lec > fotoMaxB[0][a]){ fotoMaxB[0][a] = lec; }
  //   }
  // }

    // for (int i=0; i<100; i++){
    //   int lec = lectura(a,0);
    //   if (lec < fotoMinB[0][a]){ fotoMinB[0][a] = lec; }
    //   else if (lec > fotoMaxB[0][a]){ fotoMaxB[0][a] = lec; }
    // }

  
  // for (int i=0; i<3; i++){
  //   for (int j=0; j<8; j++){
  //     for (int k=0; k<25; k++){
  //       int lec = lectura(j,i);
  //       if (lec < fotoMinB[i][j]){ fotoMinB[i][j] = lec; }
  //       else if (lec > fotoMaxB[i][j]){ fotoMaxB[i][j] = lec; }
  //     }
  //   }
  // }
  
  // delay(4000);

  ctime = millis();
  
}



void loop(){
  
  double degree = 0;
  double count = 0;

  // long div = millis() / ctime;

  // if (div % ctime >= 0 && div % ctime <= 20){
  //     for (int i=0; i<3; i++){
  //     for (int j=0; j<8; j++){
  //     for (int k=0; k<5; k++){
  //       int lec = lectura(j,i);
  //       if (lec < fotoMinB[i][j]){ fotoMinB[i][j] = lec; }
  //       else if (lec > fotoMaxB[i][j]){ fotoMaxB[i][j] = lec; }
  //     }
  //   }
  // }
  // }

  for (int i=0; i<3; i++){
    for (int j=0; j<8; j++){
      if (j == 0){ if (lectura(0,i) > 60){ 
        Serial.print(lectura(j,i));
        Serial.print(" en ");
        Serial.print(j);
        Serial.print(" de ");
        Serial.print(i);
        Serial.print("  ");
        Serial.println(angulo[i][j]);
        degree += angulo[1][i];
        count++;}
      else {Serial.println("NADOTA");}
      }
      else if (lectura(j,i) > 85){
        Serial.print(lectura(j,i));
        Serial.print(" en ");
        Serial.print(j);
        Serial.print(" de ");
        Serial.print(i);
        Serial.print("  ");
        Serial.println(angulo[i][j]);
        degree += angulo[1][i];
        count++;
      }
      else {Serial.println("NADOTA");}
    }
  }

  Serial.println(degree/count);
  motoresRobot.movimientoLineal(degree/count,180);

  // for (int i=0; i<8; i++){    // checar placa derecha
  //   // Serial.print("Lectura del ft DERECHA ");
  //   // Serial.print(i);
  //   // Serial.print(" : ");
  // Serial.println(lectura(6,2)); // ES EL 6 DE LA PRINCIPAL, 5 ES 7, 6 ES 5, 7 ES 6
  // }



}




int lectura(int ft, int placa){   // 1: derecha (1,3,4)
  switch (ft){
    case 0: binario(0,placa); delay(10); return analogRead(sig[placa]); break;
    case 1: binario(1,placa); delay(10); return analogRead(sig[placa]); break;
    case 2: binario(2,placa); delay(10); return analogRead(sig[placa]); break;
    case 3: binario(3,placa); delay(10); return analogRead(sig[placa]); break;
    case 4: binario(4,placa); delay(10); return analogRead(sig[placa]); break;
    case 5: binario(5,placa); delay(10); return analogRead(sig[placa]); break;
    case 6: binario(6,placa); delay(10); return analogRead(sig[placa]); break;
    case 7: binario(7,placa); delay(10); return analogRead(sig[placa]); break;
  }
}


void binario(int pin, int lado){
  switch (pin){
    case 0: 
      digitalWrite(sC[lado],0); 
      digitalWrite(sB[lado],0); 
      digitalWrite(sA[lado],0); break;
    case 1:
      digitalWrite(sC[lado],0); 
      digitalWrite(sB[lado],0); 
      digitalWrite(sA[lado],1); break;
    case 2:
      digitalWrite(sC[lado],0); 
      digitalWrite(sB[lado],1); 
      digitalWrite(sA[lado],0); break;
    case 3:
      digitalWrite(sC[lado],0); 
      digitalWrite(sB[lado],1); 
      digitalWrite(sA[lado],1); break;
    case 4: 
      digitalWrite(sC[lado],1); 
      digitalWrite(sB[lado],0); 
      digitalWrite(sA[lado],0); break;
    case 5: 
      digitalWrite(sC[lado],1); 
      digitalWrite(sB[lado],0); 
      digitalWrite(sA[lado],1); break;
    case 6: 
      digitalWrite(sC[lado],1); 
      digitalWrite(sB[lado],1); 
      digitalWrite(sA[lado],0); break;
    case 7: 
      digitalWrite(sC[lado],1); 
      digitalWrite(sB[lado],1); 
      digitalWrite(sA[lado],1); break;
  }
}


int complementario(int degree){
  if (degree < 180){
    return degree + 180;
  }
  else{
    return degree - 180;
  }
}

int triangulo(int degree){
  if (degree < 90){
    return degree + 270;
  }
  else{
    return degree - 90;
  }
}
