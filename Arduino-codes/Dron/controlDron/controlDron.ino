#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  

const byte rojoRGB=6;
const byte verdeRGB=5;
const byte azulRGB=3;
const byte buzzer=10;
const byte botonDerechaLCD=2;
const byte botonCentroLCD=4;
const byte botonIzquierdaLCD=7;
const byte botonDerechaJoystick=0;
const byte botonIzquierdaJoystick=1;
const int VxDerecha=A0;
const int VyDerecha=A1;
const int VxIzquierda=A2;
const int VyIzquierda=A3;
byte startState=0;
byte v1=0;
byte v2=0;
byte v3=0;
byte v4=0;
byte v5=0;
byte v6=0;
byte aa=0;
byte variable1radio=0;
byte variable2radio=0;
byte variable3radio=0;
byte variable4radio=0;
int connection=0;
int aVxD=0;
int aVyD=0;
int aVxI=0;
int aVyI=0;
int altura=0;
int velx=0;
int vely=0;
int velz=0;
int vel=0;
int ax=0;
int ay=0;
int az=0;
int acel=0;
int gx=0;
int gy=0;
int gz=0;
int giro=0;
int transmission=0;
int transmissionR=0;
int VxD=0;
int VyD=0;
int VxI=0;
int VyI=0;
char a='a';
char b='b';
char c='c';
short variable1=0;
short variable2=0;
short variable3=0;
short variable4=0;
short alturaP1;
short alturaP2;
short velocidad;
short distanciaP1;
short distanciaP2;
boolean stateBotonDerechaLCD;
boolean stateBotonCentroLCD;
boolean stateBotonIzquierdaLCD;
boolean stateBotonDerechaJoystick;
boolean stateBotonIzquierdaJoystick;
boolean droneState;
int mensaje;
int arrVarInt[]={0,0,alturaP2,distanciaP1,distanciaP2}; //
String arrVarString[]={"Vel.","Alt.x","Alt.P2","Dist.P1","Dist.P2"};


LiquidCrystal_I2C lcd(0x27,16,2);

RF24 radio(7,8);

const short addresses[][19] = {"Redsupergiantstar1","Redsupergiantstar2"};

void setup() {
  pinMode(rojoRGB,OUTPUT);
  pinMode(verdeRGB,OUTPUT);
  pinMode(azulRGB,OUTPUT);

  pinMode(buzzer,OUTPUT);

  pinMode(botonIzquierdaLCD,INPUT_PULLUP);
  pinMode(botonCentroLCD,INPUT_PULLUP);
  pinMode(botonDerechaLCD,INPUT_PULLUP);
  pinMode(botonIzquierdaJoystick,INPUT_PULLUP);
  pinMode(botonIzquierdaJoystick,INPUT_PULLUP);
  
  Wire.begin();

  lcd.init();
  lcd.backlight();

  lcd.print("Conectando...");

  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);

  int randomNumber=random(0,10);

  radio.stopListening();
  radio.write(&randomNumber,sizeof(randomNumber));
  delay(5);

  radio.startListening();
  radioEspera();
  radio.read(&transmission,sizeof(transmission));
  delay(5);
  radio.stopListening();
  delay(5);

  if (randomNumber == transmission){
    delay(50);
    connection=5;
    radio.write(&connection,sizeof(connection));
    delay(5);
    rgb('v');
    lcd.clear();
    tone(buzzer,400,100);
    delay(200);
    tone(buzzer,400,100);
    delay(500);
  }

  else {
    error(4); 
  }

  lcd.clear();
  lcd.print("¿Dron o avion?");

  boolean aa=0;
  while (aa == 0){
    if (digitalRead(botonIzquierdaLCD)==LOW){ 
      flyState=0; // dron
      lcd.clear(); 
      lcd.print("Dron");
      aa=1;
    }
    else if (digitalRead(botonDerechaLCD)==LOW){ 
      flyState=1; // avión
      lcd.clear(); 
      lcd.print("Avion");
      aa=1;
    } 
  }
  radio.write(&flyState,sizeof(flyState));
  delay(1000);

  lcd.clear();
  lcd.print("¿Race o smooth?");

  aa=0;
  while (aa == 0){
    if (digitalRead(botonIzquierdaLCD)==LOW){ 
      droneState=0; // race
      lcd.clear(); 
      lcd.print("Race");
      aa=1;
    }
    else if (digitalRead(botonDerechaLCD)==LOW){ 
      flyState=1; // smooth
      lcd.clear(); 
      lcd.print("Smooth");
      aa=1;
    } 
  }
  radio.write(&droneState,sizeof(droneState));
  delay(1000);

  radio.startListening();
  radioEspera();
  radio.read(&transmission,sizeof(transmission));
  if (transmission == 10){ // empezará a calibrar
    lcd.clear();
    lcd.print("Calibrando...");
    rgb('a');
  }
  else { error(2); }

  radioEspera();
  radio.read(&transmission,sizeof(transmission));
  if (transmission == 120120){ // terminó la calibración
    lcd.clear();
    lcd.print("Calibrdo!");
    rgb('v');
  }
  else { error(3); }

  
  

  
  
  
  
} //close void setup






void loop() {



                                    // DRONE
          //RACE  
   while (droneState==0){
      joysticks();

      radio.startListening();
      delay(5);
      radioEsperaLoop(1);
      radio.read(mensaje,sizeof(mensaje));

      switch (mensaje){
        case 1111: 
          radioEsperaLoop(1111); radio.read(&mensaje,sizeof(mensaje)); 
          velx=mensaje; break; 
        case 1112: 
          radioEsperaLoop(1112); radio.read(&mensaje,sizeof(mensaje)); 
          vely=mensaje; break; 
        case 1113: 
          radioEsperaLoop(1113); radio.read(&mensaje,sizeof(mensaje)); 
          velz=mensaje; break; 
      }
      
      
      if (radio.available()){
        radio.read(&mensaje,sizeof(mensaje));
        if (mensaje==1111){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          velx=mensaje;
          }
        else if (mensaje==1112){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          vely=mensaje;
        }
        else if (mensaje==1113){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          velz=mensaje;
        }
        else if (mensaje==1121){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          ax=mensaje;
        }
        else if (mensaje==1122){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          ay=mensaje;
        }
        else if (mensaje==1123){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          az=mensaje;
        }
        else if (mensaje==1131){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          gx=mensaje;
        }
        else if (mensaje==1132){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          gy=mensaje;
        }
        else if (mensaje==1133){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          gz=mensaje;
        }
        else if (mensaje==1141){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          pMotor1=map(mensaje,0,180,0,100);
        }
        else if (mensaje==1142){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          pMotor2=map(mensaje,0,180,0,100);
        }
        else if (mensaje==1143){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          pMotor3=map(mensaje,0,180,0,100);
        }
        else if (mensaje==1144){
          while (!(radio.available())){}
          radio.read(&mensaje,sizeof(mensaje));
          pMotor4=map(mensaje,0,180,0,100);
        }
        
      }

      vel=sqrt(velx*velx+vely*vely+velz*velz);
      acel=sqrt(ax*ax+ay*ay+az*az);
      giro=sqrt(gx*gx+gy*gy+gz*gz);
      pMotores=(pMotor1+pMotor2+pMotor3+pMotor4)/4;
      
        
        

        
    
   } //close racing while


         //SMOOTH
   while (droneState==1){
    
   } //close smooth while
   
    
  } //close if while






//PLANE

 if (state==1){
    
  } //close if plane

  


} //close void loop






                          // FUNCIONES




void joysticks(){
  radio.stopListening();

  aVxD=analogRead(VxDerecha);
  VxD=map(aVxD,0,1023,0,160);
  radio.write(&VxD,sizeof(VxD));
  delay(5);

  if (digitalRead(botonIzquierdaJoystick)==LOW) { // burst   
    VyD=177;
    radio.write(&VyD,sizeof(VyD));
    delay(5);
  }
  else {
    aVyD=analogRead(VyDerecha);
    VyD=map(aVyD,0,1023,0,160);
    radio.write(&VyD,sizeof(VyD));
    delay(5);
  }
  
  aVxI=analogRead(VxIzquierda);
  VxI=map(aVxI,0,1023,0,160);
  radio.write(&VxI,sizeof(VxI));
  delay(5);
  
  aVyI=analogRead(VyIzquierda);
  VyI=map(aVyI,0,1023,0,160);
  radio.write(&VxI,sizeof(VxI));
  delay(5);

  
  
}










void elegirVariables(){

   aa=0;
   boolean decVar1=0;
   while (decVar1==0){
    if (aa>4){aa=0;}
    while (arrVarString[aa]=="none"){aa=aa+1;}
    if (aa>4){aa=0;}
    lcd.clear();
    lcd.print("Var.1: ");
    lcd.print(arrVarString[aa]);
    while (1){
      if ((digitalRead(botonDerechaLCD)==LOW) && (aa<=4)){ aa=aa+1; break; }
      else if ((digitalRead(botonDerechaLCD)==LOW) && (!(aa<=4))){ aa=0; break;}
      else if (digitalRead(botonCentroLCD)==LOW){ variable1=arrVarInt[aa]; variable1radio=aa; arrVarString[aa]="none"; decVar1=1; break;}
    }
    delay(200);
   }

   aa=0;
   boolean decVar2=0;
   while (decVar2==0){
    if (aa>4){aa=0;}
    while (arrVarString[aa]=="none"){aa=aa+1;}
    if (aa>4){aa=0;}
    lcd.clear();
    lcd.print("Var.2: ");
    lcd.print(arrVarString[aa]);
    while (1){
      if ((digitalRead(botonDerechaLCD)==LOW) && (aa<=4)){ aa=aa+1; break; }
      else if ((digitalRead(botonDerechaLCD)==LOW) && (!(aa<=4))){ aa=0; break;}
      else if (digitalRead(botonCentroLCD)==LOW){ variable2=arrVarInt[aa]; variable2radio=aa; arrVarString[aa]="none"; decVar2=1; break;}
    }
    delay(200);
   }

   aa=0;
   boolean decVar3=0;
   while (decVar3==0){
    if (aa>4){aa=0;}
    while (arrVarString[aa]=="none"){aa=aa+1;}
    if (aa>4){aa=0;}
    lcd.clear();
    lcd.print("Var.3: ");
    lcd.print(arrVarString[aa]);
    while (1){
      if ((digitalRead(botonDerechaLCD)==LOW) && (aa<=4)){ aa=aa+1; break; }
      else if ((digitalRead(botonDerechaLCD)==LOW) && (!(aa<=4))){ aa=0; break;}
      else if (digitalRead(botonCentroLCD)==LOW){ variable3=arrVarInt[aa]; variable3radio=aa; arrVarString[aa]="none"; decVar3=1; break;}
    }
    delay(200);
   }

   aa=0;
   boolean decVar4=0;
   while (decVar4==0){
    if (aa>4){aa=0;}
    while (arrVarString[aa]=="none"){aa=aa+1;}
    if (aa>4){aa=0;}
    lcd.clear();
    lcd.print("Var.4: ");
    lcd.print(arrVarString[aa]);
    while (1){
      if ((digitalRead(botonDerechaLCD)==LOW) && (aa<=4)){ aa=aa+1; break; }
      else if ((digitalRead(botonDerechaLCD)==LOW) && (!(aa<=4))){ aa=0; break;}
      else if (digitalRead(botonCentroLCD)==LOW){ variable4=arrVarInt[aa]; variable4radio=aa; arrVarString[aa]="none"; decVar4=1; break;}
    }
    delay(200);
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



char rgb(char color){    
  short rojo=0; short verde=0; short azul=0;
  switch (color){
    case 'r': rojo=255; break;
    case 'v': verde=255; break;
    case 'z': azul=255; break;
    case 'n': rojo=243; verde=156; azul=18; break; // naranja
    case 'a': rojo=255; verde=251; break; // amarillo
    case '-': break;  // nada
    case 'c': verde=255; azul=243; break; // celeste
    case 'o': rojo=201; azul=255; break; // morado 
    case 's': rojo=255; verde=121; azul=247; break; // rosa
  }
  analogWrite(rojoRGB,rojo);
  analogWrite(verdeRGB,verde);
  analogWrite(azulRGB,azul);
} // cierra función rgb("")


void error(int numero){
  lcd.clear();
  rgb('r');
  tone(buzzer,49,1000);
  if (numero == 1 || numero == 2 || numero == 3 || numero == 4 || numero == 1111 || numero == 1112 || numero == 1113){ // errores de RF
    lcd.print("Error ");
    lcd.print(numero);
    lcd.print(": RF");
  }
  while(1);
}


void radioEsperaLoop(int mensaje){
  float previousTime=millis();
  while (!(radio.available())){
    float tiempo=(millis()-previousTime)/1000;
    if (tiempo == 2){    // si han pasado 2 seg sin respuesta de RF
      error(mensaje);
    }
  }
} // cierra función radioEsperaLoop()





  
/*                                 ERRORES
 *                                  
 * 1: Pasaron 5 segundos sin una respuesta esperada del RF del dron. 
 * 2: No se recibió el valor correcto de inicio de calibración de motores.
 * 3: No se recibió el valor correcto de finalización de calibración de motores.
 * 4: No se recibió el valor correcto de regreso al hacer la prueba de conexión inicial.
 * 
 * 
 * 
 * 1111: no se recibió el valor de velx.
 * 1112: no se recibió el valor de vely.
 * 1113: no se recibió el valor de velz.
 * 1121: no se recibió el valor de ax.
 * 1122: no se recibió el valor de ay.
 * 1123: no se recibió el valor de az.

 */
