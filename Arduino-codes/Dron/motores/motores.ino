#include <AFMotor.h>
#include <SoftwareSerial.h>  

SoftwareSerial miBT(9,10);

AF_DCMotor motorUno(1);
AF_DCMotor motorDos(2);
AF_DCMotor motorTres(3);
AF_DCMotor motorCuatro(4);

char dato;
byte movimiento;

void setup()
{
  miBT.begin(9600);
  Serial.begin(9600);  
  Serial.println("Listo");
  
  motorUno.setSpeed(250);
  motorDos.setSpeed(250);
  motorTres.setSpeed(250);
  motorCuatro.setSpeed(250);
  
}
void loop()
{
  if(miBT.available())
  { dato=miBT.read();
    Serial.println(dato);
    Serial.println("");
    
  if  (dato=='F') 
  {
    adelante();    
  }

  if (dato=='B')
   {
    reversa();
  }
if (dato=='R')
 {
    derecha();
  }

  if (dato=='L')
 {
   izquierda();
  }

if (dato=='S')
{alto(); }
  }


  if (dato=='X'){
  motorUno.setSpeed(50);
  motorDos.setSpeed(50);
  motorTres.setSpeed(50);
  motorCuatro.setSpeed(50);
  }

if (dato=='x'){
  motorUno.setSpeed(250);
  motorDos.setSpeed(250);
  motorTres.setSpeed(250);
  motorCuatro.setSpeed(250);   
  }
  
  
 }

 

void adelante(){
  motorUno.run(FORWARD);
  motorDos.run(FORWARD);
  motorTres.run(FORWARD);
  motorCuatro.run(FORWARD);
  }

void reversa(){
  motorUno.run(BACKWARD);
  motorDos.run(BACKWARD);
  motorTres.run(BACKWARD);
  motorCuatro.run(BACKWARD);
  }


void derecha(){  
  motorUno.run(BACKWARD);
  motorDos.run(BACKWARD);
  motorTres.run(FORWARD);
  motorCuatro.run(FORWARD);
  }

  void izquierda(){
  motorUno.run(FORWARD);
  motorDos.run(FORWARD);
  motorTres.run(BACKWARD);
  motorCuatro.run(BACKWARD);
  }

  void alto (){
  motorUno.run(RELEASE);
  motorDos.run(RELEASE);
  motorTres.run(RELEASE);
  motorCuatro.run(RELEASE);}
