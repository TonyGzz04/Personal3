/*
===============================================================================================================
QMC5883LCompass.h Library Azimuth Example Sketch
Learn more at [https://github.com/mprograms/QMC5883Compas]
===============================================================================================================
v0.3 - June 12, 2019
Written by MRPrograms 
Github: [https://github.com/mprograms/]

Release under the GNU General Public License v3
[https://www.gnu.org/licenses/gpl-3.0.en.html]
===============================================================================================================
*/


#include <QMC5883LCompass.h>

QMC5883LCompass compass;

// Motor izquierdo
int motor_i_adelante = 5;
int motor_i_atras = 6;

// Motor derecho
int motor_d_adelante = 3;
int motor_d_atras = 4;

int first=0;
int f=0;
int aDir0=65;
int aDir1=61;
int aDir2=110;
int aDir3=26;
byte dir=0;

void setup() {
  Serial.begin(9600);
  compass.init();





pinMode(motor_i_adelante, OUTPUT);
  pinMode(motor_i_atras, OUTPUT);
  pinMode(motor_d_adelante, OUTPUT);
  pinMode(motor_d_atras, OUTPUT);








   compass.read();
    first = compass.getAzimuth();
    

  
  
}

void loop() {
  int a;
  
  // Read compass values
  compass.read();

  // Return Azimuth reading
  f = compass.getAzimuth();
  
  Serial.print("A: ");
  Serial.print(f);
  Serial.println();

derecha();

  if (dir==0 && (f>=aDir1-3 && f<=aDir1+3)){
    alto(); dir=1; Serial.println("YA"); delay(2000);
  }

  else if (dir==1 && (f>=aDir2-3 && f<=aDir2+3)){
    alto(); dir=2; Serial.println("YA"); delay(2000);
  }

  else if (dir==2 && (f>=aDir3-3 && f<= aDir3+3)){
    alto(); dir=3; Serial.println("YA"); delay(2000); 
  }

  else if (dir==3 && (f>=aDir0-3 && f<=aDir0+3)){
    alto(); dir=0; Serial.println("YA"); delay(2000);
  }

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
