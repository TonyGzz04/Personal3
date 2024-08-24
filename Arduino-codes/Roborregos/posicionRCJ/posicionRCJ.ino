int trig[4] = {31, 29, 33, 35};
int echo[4] = {10, 28, 32, 34};

volatile double distancia[4] = {0, 0, 0, 0};  
volatile double pos[2] = {0, 0};

/* 

  0 = NORTE
  1 = ESTE
  2 = SUR
  3 = OESTE

*/

void setup() {
  Serial.begin(9600);
  
  for (byte i=0; i<4; i++){
    pinMode(trig[i],OUTPUT);
    pinMode(echo[i],INPUT);
  }

}

void loop() {

  for (int i=0; i<4; i++){
  Serial.print("Posicion 1");
  Serial.print(": ");
  Serial.println(dist(i));

  delay(1000);
  }
  
}



double dist(byte i){
    digitalWrite(trig[i],LOW);
    delayMicroseconds(2);
    digitalWrite(trig[i],HIGH);
    delayMicroseconds(10);
    digitalWrite(trig[i],LOW);
    int duracion=pulseIn(echo[i],HIGH);
    distancia[i]=(duracion/2)/29.1;  
    return distancia[i];
    
}

/*
double posicion(bool e){  // 0 = NE, 1 = SO

  if (e == 0){
    dist(0) - 
  }

  else {
    double anguloDist = asin(dist(0)/(sqrt(sq(dist(0))+sq(dist(1)))));
    distancia[0] = sin(anguloDist) * dist(1) / sin(135-anguloDist);
    anguloDist = asin(dist(2)/(sqrt(sq(dist(2))+sq(dist(3)))));
    distancia[2] = sin(anguloDist) * dist(3) / sin(135-anguloDist);
    pos[1] = distancia[0] + distancia[2]; 
    return pos[1];
  }

}
*/