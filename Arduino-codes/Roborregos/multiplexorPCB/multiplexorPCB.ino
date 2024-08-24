// #define sig[0][0][0][0][0][0][0][0] A0
int sig[3] = {A0,A1,A2}; 

int maximo[8] = {};
int maxx = 0;

#define sC 7  // pines de 'control'    // MUX 3  FRONTAL A42 B43 C38 sig[0]
#define sB 8
#define sA 9

#define ft0 0  // lecturas de los fototransistores
#define ft1 0
#define ft2 0
#define ft3 0
#define ft4 0
#define ft5 0
#define ft6 0
#define ft7 0



void setup(){
  Serial.begin(9600);
  
  pinMode(sC,OUTPUT);
  pinMode(sB,OUTPUT);
  pinMode(sA,OUTPUT);
  
}

void loop(){

  // DERECHA: 37 - 50
  // PRINCIPAL: 30 - 60
  // IZQUIERDA: 0, 1, 2, 4, 5, 6

  for (byte i=0; i<8; i++){
    
    // Serial.print("Lectura del ft ");
    // Serial.print(i);
    // Serial.print(" : ");
    Serial.println(lectura(1));
    // maximo[i] = lectura(i);

    // if (i > 1){
    //   if (maximo[i] > maximo[i-1]){
    //     maxx = lectura(i);
    //   }
    // }
    
    // if (lectura(i) > 19){
    //   Serial.println("BLANCO");
    //   break;
    // }
  }
  //Serial.println(maxx);
  Serial.println("");

}


int lectura(byte ft){
  switch (ft){
    case 0: binario(0); delay(10); return analogRead(sig[2]); break;
    case 1: binario(1); delay(10); return analogRead(sig[2]); break;
    case 2: binario(2); delay(10); return analogRead(sig[2]); break;
    case 3: binario(3); delay(10); return analogRead(sig[2]); break;
    case 4: binario(4); delay(10); return analogRead(sig[2]); break;
    case 5: binario(5); delay(10); return analogRead(sig[2]); break;
    case 6: binario(6); delay(10); return analogRead(sig[2]); break;
    case 7: binario(7); delay(10); return analogRead(sig[2]); break;
  }
}


void binario(int pin){
  switch (pin){
    case 0: 
      digitalWrite(sC,0); 
      digitalWrite(sB,0); 
      digitalWrite(sA,0); break;
    case 1:
      digitalWrite(sC,0); 
      digitalWrite(sB,0); 
      digitalWrite(sA,1); break;
    case 2:
      digitalWrite(sC,0); 
      digitalWrite(sB,1); 
      digitalWrite(sA,0); break;
    case 3:
      digitalWrite(sC,0); 
      digitalWrite(sB,1); 
      digitalWrite(sA,1); break;
    case 4: 
      digitalWrite(sC,1); 
      digitalWrite(sB,0); 
      digitalWrite(sA,0); break;
    case 5: 
      digitalWrite(sC,1); 
      digitalWrite(sB,0); 
      digitalWrite(sA,1); break;
    case 6: 
      digitalWrite(sC,1); 
      digitalWrite(sB,1); 
      digitalWrite(sA,0); break;
    case 7: 
      digitalWrite(sC,1); 
      digitalWrite(sB,1); 
      digitalWrite(sA,1); break;
  }
}