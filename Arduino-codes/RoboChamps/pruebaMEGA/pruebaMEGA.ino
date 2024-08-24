int pinLed=23;
int pinBoton=22;

void setup(){
  pinMode(pinLed,OUTPUT);
  pinMode(pinBoton,INPUT_PULLUP);
}

void loop(){
  int estado=digitalRead(pinBoton);

  if (estado==LOW){
    digitalWrite(pinLed,HIGH);
  }

  else {
    digitalWrite(pinLed,LOW);
  }
}
