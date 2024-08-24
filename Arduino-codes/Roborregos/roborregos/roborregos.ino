
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

#define S0_PIN 8
#define S1_PIN 9
#define S2_PIN 10
#define S3_PIN 11
#define OUT_PIN  12

// Ultrasonico delantero
#define echoPinDelantero 2
#define trigPinDelantero 3

// Ultrasonioc derecha
#define echoPinDerecha 4
#define trigPinDerecha 5


void setup() {
  Serial.begin(9600);

  pinMode(trigPinDelantero, OUTPUT);
  pinMode(echoPinDelantero, INPUT);
  pinMode(trigPinDerecha, OUTPUT);
  pinMode(echoPinDerecha, INPUT);

  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);

  digitalWrite(S0_PIN, HIGH);
  digitalWrite(S1_PIN, LOW);

  delay(100);
  avanzar();
  delay(2000);
  color1=checarColor();

}

void loop() {


  if (giroI==true){
    giroI=false;
    dir=dir+1;
    if (dir==5){dir=1;}
    avanzar();
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
    else if (cuadro==12){cuadro=13;}
   }


  else if (giroD==true){
    giroD=false;
    dir=dir-1;
    if (dir==0){dir=4;}
    avanzar();
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
    else if (cuadro==13){cuadro=12;}
   }

   else {
    avanzar();
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
  }
  else if (g < 63)
  {
    Serial.println("Colour Green");
    color=2;
  }
  else if (r < 64)
  {
    color=3;
    Serial.println("Colour Red");
  }
  return color;
}

void avanzar(){

}

int ultrasonico_delantero()
{
  digitalWrite(trigPinDelantero, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDelantero, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDelantero, LOW);
  int duration = pulseIn(echoPinDelantero, HIGH);
  int distanceDelantera = duration * 0.034 / 2;
  Serial.print(distanceDelantera);
  return distanceDelantera;
}

int ultrasonico_derecha()
  {
    digitalWrite(trigPinDerecha, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDerecha, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDerecha, LOW);
    int duration = pulseIn(echoPinDerecha, HIGH);
    int distanceDerecha = duration * 0.034 / 2;
    Serial.print(distanceDerecha);
    return distanceDerecha;
  }
