// Motor izquierdo
int motor_i_adelante = 5;
int motor_i_atras = 6;

// Motor derecho
int motor_d_adelante = 3;
int motor_d_atras = 4;

// Ultrasonico adelante
#define echoPinDelantero 24
#define trigPinDelantero 25

// Ultrasonico derecha
#define echoPinDerecha 22
#define trigPinDerecha 23 

// Ultrasonico izquierda
#define echoPinIzquierda 27
#define trigPinIzquierda 26

int duration = 0;
int distanceDelantera = 0;
int distanceDerecha = 0;
int distanceIzquierda = 0;




void setup() {
    // Ultrasonicos
  pinMode(trigPinDelantero, OUTPUT);
  pinMode(echoPinDelantero, INPUT);
  pinMode(trigPinDerecha, OUTPUT);
  pinMode(echoPinDerecha, INPUT);
  pinMode(trigPinIzquierda, OUTPUT);
  pinMode(echoPinIzquierda, INPUT);

  // Motores
  pinMode(motor_i_adelante, OUTPUT);
  pinMode(motor_i_atras, OUTPUT);
  pinMode(motor_d_adelante, OUTPUT);
  pinMode(motor_d_atras, OUTPUT);

    Serial.begin(9600); 

    delay(2000);

}

void loop() {

    izquierdaFinal();
  
}


void alto()
{
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
}

void derecha()
{
  // Girar a la izquierda (predefinido)
  digitalWrite(motor_i_adelante, HIGH);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, HIGH); 
}

void izquierda()
{
  // Girar a la izquierda (predefinido)
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, HIGH);
  digitalWrite(motor_d_adelante, HIGH);
  digitalWrite(motor_d_atras, LOW);
}

void adelante()
{
    digitalWrite(motor_i_adelante, HIGH);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, HIGH);
    digitalWrite(motor_d_atras, LOW);
}


void izquierdaFinal(){
  digitalWrite(trigPinDelantero, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDelantero, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDelantero, LOW);
  int duration = 0;
  duration = pulseIn(echoPinDelantero, HIGH);
  float distanceDelantera = 0;
  distanceDelantera = duration * 0.034 / 2;
  
  Serial.println(distanceDelantera);
  digitalWrite(trigPinDerecha, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDerecha, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDerecha, LOW);
  duration = pulseIn(echoPinDerecha, HIGH);
  float distanceDerecha = 0;
  distanceDerecha = duration * 0.034 / 2;

  delay(2000);
  izquierda();
  delay(150);
  alto();

/*
bool salir=false;

  while (salir==false){
  digitalWrite(trigPinDerecha, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDerecha, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDerecha, LOW);
  duration = pulseIn(echoPinDerecha, HIGH);
  float distanceDerecha = 0;
  distanceDerecha = duration * 0.034 / 2;

  if (!(distanceDerecha> (distanceDelantera+1)) && (distanceDerecha<(distanceDelantera-1))){
      izquierda();
      delay(50);
      alto();
      delay(200);
  }
  else{
    salir=true;
    alto();
    }
  }
  */
  while (!(distanceDerecha > distanceDelantera - 1) && (distanceDerecha < distanceDelantera + 1))
  //while (!(distanceDerecha > (distanceDelantera)) && (distanceDerecha < (distanceDelantera-1)))
  {
    izquierda();
    delay(50);
    alto();
    
   digitalWrite(trigPinDerecha, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDerecha, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDerecha, LOW);
  duration = pulseIn(echoPinDerecha, HIGH);
  float distanceDerecha = 0;
  distanceDerecha = duration * 0.034 / 2;
    }
    alto();
  }







void derechaFinal(){
  digitalWrite(trigPinDelantero, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDelantero, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDelantero, LOW);
  int duration = 0;
  duration = pulseIn(echoPinDelantero, HIGH);
  float distanceDelantera = 0;
  distanceDelantera = duration * 0.034 / 2;
  Serial.println(distanceDelantera);
  digitalWrite(trigPinIzquierda, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinIzquierda, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinIzquierda, LOW);
  duration = pulseIn(echoPinIzquierda, HIGH);
  float distanceIzquierda = 0;
  distanceIzquierda = duration * 0.034 / 2;

  delay(2000);
  derecha();
  delay(250);
  alto();

bool salir=false;

  while (salir==false){
    derecha();
    delay(30);
    alto();
    delay(100);
  digitalWrite(trigPinIzquierda, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinIzquierda, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinIzquierda, LOW);
  duration = pulseIn(echoPinIzquierda, HIGH);
  float distanceIzquierda = 0;
  distanceIzquierda = duration * 0.034 / 2;
  distanceIzquierda=distanceIzquierda-0.1;

  Serial.println(distanceIzquierda);
  if (distanceIzquierda<=distanceDelantera+0.2 && distanceIzquierda>=distanceDelantera-0.2){salir=true; alto();}
  }

}






void adelanteFinal(){
  digitalWrite(trigPinDelantero, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDelantero, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDelantero, LOW);
  int duration = 0;
  duration = pulseIn(echoPinDelantero, HIGH);
  float distanceDelantera = 0;
  distanceDelantera = duration * 0.034 / 2;
  Serial.println(distanceDelantera);
  float distanceMeta=distanceDelantera-30;

  adelante();
  delay(350);
  alto();

  bool salir=false;

while (salir==false){
  digitalWrite(trigPinDelantero, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDelantero, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDelantero, LOW);
  int duration = 0;
  duration = pulseIn(echoPinDelantero, HIGH);
  float distanceDelantera = 0;
  distanceDelantera = duration * 0.034 / 2;
  Serial.println(distanceDelantera);

  Serial.println(distanceDelantera);

  if (!(distanceDelantera>distanceMeta)){
      adelante();
      delay(50);
      alto();
      delay(200);
  }
  else{salir=true;}
  }
  alto();
  Serial.println("YA");
}
