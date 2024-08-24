#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  

//create an RF24 object
RF24 radio(7, 8);  // CE, CSN

LiquidCrystal_I2C lcd(0x27,16,2);

const byte address1[6] = "00001";
const byte address2[6] = "00002";

int mensaje=0;
int transmission;
byte led=3;
byte x=0;
int valor;
byte swPin=4;


void setup() {
  
  Wire.begin();

  pinMode(swPin,INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  delay(2000);

  lcd.print("Conectando...");

  radio.begin();
  radio.openWritingPipe(address2);
  radio.openReadingPipe(1,address1);
  radio.setPALevel(RF24_PA_MIN);

  int randomNumber=13;

  radio.stopListening();
  radio.write(&randomNumber,sizeof(randomNumber));
  delay(5);

  radio.startListening();
  radioEspera();
  radio.read(&transmission,sizeof(transmission));
  delay(500);
  radio.stopListening();
  delay(5);

  if (randomNumber == transmission){
    delay(500);
    int connection=5;
    radio.write(&connection,sizeof(connection));
    radio.startListening();
    delay(5);
    radioEsperando();
    radio.stopListening();
    delay(5);
    lcd.clear();
    lcd.print("Conectado!");
    delay(200);
  }

  lcd.clear();
  lcd.print("Dron o avion?");

  boolean aa=0;
  int flyState=0;
  radio.write(&flyState,sizeof(flyState));
  delay(5);
  radio.startListening();
  delay(5);
  radioEsperando();
  radio.stopListening();
  delay(5);

  lcd.clear();
  lcd.print("Race o smooth?");

  int droneState=0;
  radio.write(&droneState,sizeof(droneState));
  delay(5);
  radio.startListening();
  delay(5);
  radioEsperando();
  radio.stopListening();
  delay(5);
  radio.startListening();
  delay(5);

  while (!(radio.available())){lcd.clear(); lcd.print("Esperando...");}
  if (radio.available()){
    radio.read(&transmission,sizeof(transmission));
    if (transmission == 10){ // empezará a calibrar
      lcd.clear();
      lcd.print("Calibrando...");
    }
    else { lcd.clear(); lcd.print(transmission); delay(1000); error(2); }
  }

  while (!(radio.available())){}
  if (radio.available()){
    radio.read(&transmission,sizeof(transmission));
    if (transmission == 120){ // terminó la calibración
      lcd.clear();
      lcd.print("Calibrado!");
    }
    else { error(3); }
  }

  radio.stopListening();
  delay(5);

  delay(3000);
  
  
} //close void setup




void loop()
{
  int x=analogRead(A3);
  int y=analogRead(A2);

  radio.write(&x,sizeof(x));
  delay(5);
  radio.write(&y,sizeof(y));

  if (digitalRead(swPin) == LOW){
    mensaje=2000;
    radio.write(&mensaje,sizeof(mensaje));
  }
  



}


void radioEspera(){
  float previousTime=millis();
  while (!(radio.available())){
    float tiempo=(millis()-previousTime)/1000;
    if (tiempo == 5){    // si han pasado 5 seg sin respuesta de RF
      error(1);
    }
  }
} // cierra función radioEspera()


void radioEsperando(){
  float previousTime=millis();
  while (!(radio.available())){
    float tiempo=(millis()-previousTime)/1000;
    if (tiempo == 5){    // si han pasado 5 seg sin respuesta de RF
      error(1);
    }  
  }
  radio.read(&transmission,sizeof(transmission));
  if (!(transmission == 3)){
    error(1);
  }
}


void error(int numero){
  lcd.clear();
  if (numero == 1 || numero == 2 || numero == 3 || numero == 4 || numero == 1111 || numero == 1112 || numero == 1113){ // errores de RF
    lcd.print("Error ");
    lcd.print(numero);
    lcd.print(": RF");
  }
  while(1);
}
