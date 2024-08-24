// Motor izquierdo
int motor_i_adelante = 5;
int motor_i_atras = 6;

// Motor derecho
int motor_d_adelante = 3;
int motor_d_atras = 4;

// Ultrasonico adelante
#define echoPinDelantero 24
#define trigPinDelantero 25
int ultfrente = 0;

// Ultrasonioc derecha
#define echoPinDerecha 22
#define trigPinDerecha 23
int ultderecha = 0; 

// Ultrasonico general
int duration = 0;
int distanceDelantera = 0;
int distanceDerecha = 0;

#define S0_PIN 8
#define S1_PIN 9
#define S2_PIN 10
#define S3_PIN 11
#define OUT_PIN  12

#define ledRojo 40
#define ledVerde 41
#define ledAzul 42


byte dir=4; 
bool giroI=false;
bool giroD=false;
short cuadro=0;
short color=0;
short color1=0;
short color2=0;
short color3=0;
short color4=0;
short color5=0;
short color6=0;
short color7=0;
short color8=0;
short color9=0;
short color10=0;
short color11=0;
short color12=0;
short cuadroCruz=0;

int arrColor[]={color1,color2,color3,color4,color5,color6,color7,color8,color9,color10,color11,color12};




int ultrasonico_adelante()
  {
    digitalWrite(trigPinDelantero, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDelantero, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDelantero, LOW);
    int duration = 0;
    duration = pulseIn(echoPinDelantero, HIGH);
    int distanceDelantera = 0;
    distanceDelantera = duration * 0.034 / 2;
    Serial.println(distanceDelantera);
    return distanceDelantera;
  }

// Ultrasonico derecha
int ultrasonico_derecha()
  {
    digitalWrite(trigPinDerecha, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDerecha, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDerecha, LOW);
    int duration = 0;
    duration = pulseIn(echoPinDerecha, HIGH);
    int distanceDerecha = 0;
    distanceDerecha = duration * 0.034 / 2;
    Serial.println(distanceDerecha);
    return distanceDerecha;
  }

void setup() 
{
  // Ultrasonicos
  pinMode(trigPinDelantero, OUTPUT);
  pinMode(echoPinDelantero, INPUT);
  pinMode(trigPinDerecha, OUTPUT);
  pinMode(echoPinDerecha, INPUT);

  // Motores
  pinMode(motor_i_adelante, OUTPUT);
  pinMode(motor_i_atras, OUTPUT);
  pinMode(motor_d_adelante, OUTPUT);
  pinMode(motor_d_atras, OUTPUT);

  pinMode(ledRojo,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledAzul,OUTPUT);

  Serial.begin(9600);  

  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);

  digitalWrite(S0_PIN, HIGH);
  digitalWrite(S1_PIN, LOW);
}

void loop() 
{
  bool zona1=true;
  while (zona1==true){
    digitalWrite(trigPinDelantero, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDelantero, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDelantero, LOW);
    int duration = 0;
    duration = pulseIn(echoPinDelantero, HIGH);
    int distanceDelantera = 0;
    distanceDelantera = duration * 0.034 / 2;
    
    digitalWrite(trigPinDerecha, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDerecha, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDerecha, LOW);
    duration = pulseIn(echoPinDerecha, HIGH);
    int distanceDerecha = 0;
    distanceDerecha = duration * 0.034 / 2;

  // 1 pared a la derecha y 0 adelante  Se mueve adelante
  if((distanceDerecha <= 30) && (distanceDelantera > 30))
  {
    adelante();
    delay(2000);
    color=checarColor();
    if (cuadro==1){cuadro=2; color2=color;}
    else if (cuadro==2){cuadro=3; color3=color;}
    else if (cuadro==3){cuadro=4; color4=color;}
    else if (cuadro==5){cuadro=6; color6=color;}
    else if (cuadro==6){cuadro=7; color7=color;}
    else if (cuadro==7){cuadro=8; color8=color;}
    else if (cuadro==9){cuadro=10; color10=color;}
    else if (cuadro==10){cuadro=11; color11=color;}
    else if (cuadro==11){cuadro=12; color12=color;}
  }

  // 0 pared a la derecha y 1 adelante  Gira derecha y se mueve adelante
  else if((distanceDerecha > 30) && (distanceDelantera <= 30))
  {
    derecha();
    dir=dir+1;
    if (dir==5){dir=1;}
    delay(2000);
    adelante();
    delay(2000);
    color=checarColor();
    if (cuadro==5){cuadro=1; color1=color;}
    else if (cuadro==6){cuadro=2; color2=color;}
    else if (cuadro==7){cuadro=3; color3=color;}
    else if (cuadro==8){cuadro=4; color4=color;}
    else if (cuadro==9){cuadro=5; color5=color;}
    else if (cuadro==10){cuadro=6; color6=color;}
    else if (cuadro==11){cuadro=7; color7=color;}
    else if (cuadro==12){cuadro=8; color8=color;}
  }

  // 1 pared a la derecha y 1 adelante  Gira izquierda y se mueve adelante 
  else if((distanceDerecha <= 30) && (distanceDelantera <= 30))
  {
    izquierda();
    dir=dir-1;
    if (dir==0){dir=4;}
    delay(2000);
    adelante();
    delay(2000);
    color=checarColor();
    if (cuadro==1){cuadro=5; color5=color;}
    else if (cuadro==2){cuadro=6; color6=color;}
    else if (cuadro==3){cuadro=7; color7=color;}
    else if (cuadro==4){cuadro=8; color8=color;}
    else if (cuadro==5){cuadro=9; color9=color;}
    else if (cuadro==6){cuadro=10; color10=color;}
    else if (cuadro==7){cuadro=11; color11=color;}
    else if (cuadro==8){cuadro=12; color12=color;}
  }

  // 0 pared a la derecha y 0 adelante  Gira derecha y se mueve adelante 
  else if((distanceDerecha > 30) && (distanceDelantera > 30))
  {
    derecha();
    dir=dir+1;
    if (dir==5){dir=1;}
    delay(2000);
    adelante();
    delay(2000);
    color=checarColor();
    if (cuadro==5){cuadro=1; color1=color;}
    else if (cuadro==6){cuadro=2; color2=color;}
    else if (cuadro==7){cuadro=3; color3=color;}
    else if (cuadro==8){cuadro=4; color4=color;}
    else if (cuadro==9){cuadro=5; color5=color;}
    else if (cuadro==10){cuadro=6; color6=color;}
    else if (cuadro==11){cuadro=7; color7=color;}
    else if (cuadro==12){cuadro=8; color8=color;}
  }

  // por si ve algo más
  else
  {
    alto();
    delay(2000);
  }

  if (cuadro==12){
    color12=checarColor();
    if (dir==4){derecha(); dir=1; delay(2000);}
    else if (dir==3){derecha(); delay(2000); derecha(); delay(2000); dir=1;}
    else if (dir==2){izquierda(); delay(2000); dir=1;}
    
    cuadroCruz=cruz();

    int cont=0;
    for (int i=0; i<12; i++){ if (arrColor[i]!=0){cont=cont+1;}}
    
    if((distanceDerecha <= 30) && (distanceDelantera > 30)){
      adelante();
      delay(2000);
    }
  }
}





bool zona2=true;
while (zona2==true){
  cambiarDireccion(3);
  
}



bool zona3=true;
while (zona3==true){
  
}





bool zona4=true;
while (zona4==true){
  
}




  
} //CIERRA VOID LOOP







//Movimientos básicos del robot
void adelante()
{
    digitalWrite(motor_i_adelante, HIGH);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, HIGH);
    digitalWrite(motor_d_atras, LOW);
    delay(480);
    digitalWrite(motor_i_adelante, LOW);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, LOW);
    digitalWrite(motor_d_atras, LOW);
}

void atras()
{
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, HIGH);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, HIGH);
  delay(100);
  digitalWrite(motor_i_adelante, HIGH);
  digitalWrite(motor_i_atras, HIGH);
  digitalWrite(motor_d_adelante, HIGH);
  digitalWrite(motor_d_atras, HIGH);
  delay(100);
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
  
}

void izquierda()
{
  // Girar a la izquierda (predefinido)
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, HIGH);
  digitalWrite(motor_d_adelante, HIGH);
  digitalWrite(motor_d_atras, LOW);
  delay(360);                               // Ajustar tiempo para establecer bien el giro
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
  delay(400);                               // Ajustar tiempo para establecer bien el giro
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
}

void alto()
{
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
}

int checarColor(){
  int color=0;
 int r, g, b;
  r = process_red_value();
  delay(200);
  g = process_green_value();
  delay(200);
  b = process_blue_value();
  delay(200);
  Serial.print("r = ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print("g = ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print("b = ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println();
  if (b < 42)
  {
    Serial.println("Colour Blue");
    color=1;
    digitalWrite(ledAzul,HIGH);
    delay(2000);
  }
  else if (g < 63)
  {
    Serial.println("Colour Green");
    color=2;
    digitalWrite(ledVerde,HIGH);
    delay(2000);
  }
  else if (r < 64)
  {
    color=3;
    Serial.println("Colour Red");
    digitalWrite(ledRojo,HIGH);
    delay(2000);
  }
  
  digitalWrite(ledRojo,LOW);
  digitalWrite(ledRojo,LOW);
  digitalWrite(ledRojo,LOW);
  
  return color;
}

int process_red_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, LOW);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
int process_green_value()
{
  digitalWrite(S2_PIN, HIGH);
  digitalWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
int process_blue_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}

int cruz(){
  if ((color1==color3) && (color1==color9) && (color1==color11)){
    cuadroCruz=6;
  }
  else{
    cuadroCruz=7;
  }
  return cuadroCruz; 
}

void cambiarDireccion(int a){
  if (dir==
}
