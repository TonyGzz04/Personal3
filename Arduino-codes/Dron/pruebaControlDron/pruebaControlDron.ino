#include <Wire.h>
#include <LiquidCrystal_I2C.h>  

byte botonIzquierdaLCD=8;
byte botonCentroLCD=9;
byte botonDerechaLCD=10;
int variable1=0;
int variable2=0;
int variable3=0;
int variable4=0;
int arrVarInt[]={0,1,2,3,4}; //
String arrVarString[]={"Vel.","Alt.x","Alt.P2","Dist.P1","Dist.P2"};

LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
  Serial.begin(9600);

  pinMode(botonIzquierdaLCD,INPUT_PULLUP);
  pinMode(botonCentroLCD,INPUT_PULLUP);
  pinMode(botonDerechaLCD,INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Listo!");
  delay(1000);
  lcd.clear();

}

void loop() {
  elegirVariables();

}



void elegirVariables(){

   int aa=0;
   boolean decVar1=0;
   while (decVar1==0){
    if (aa>4){aa=0;}
    while (arrVarString[aa]=="none"){aa=aa+1;}
    if (aa>4){aa=0;}
    lcd.clear();
    lcd.print("Var.1: ");
    lcd.print(arrVarString[aa]);
      while (1){
        Serial.println(digitalRead(botonCentroLCD));
        if ((digitalRead(botonDerechaLCD)==LOW) && (!(aa<=4))){ aa=0; break; }
        else if ((digitalRead(botonDerechaLCD)==LOW) && (aa<=4)){ aa=aa+1; break;}
        else if (digitalRead(botonCentroLCD)==LOW){ variable1=arrVarInt[aa]; arrVarString[aa]="none"; decVar1=1; break;}
      } 
   delay(170);
   }

  delay(200);
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
      if ((digitalRead(botonDerechaLCD)==LOW) && (!(aa<=4))){ aa=0; break; }
      else if ((digitalRead(botonDerechaLCD)==LOW) && (aa<=4)){ aa=aa+1; break; }
      else if ((digitalRead(botonCentroLCD))==LOW){ variable2=arrVarInt[aa]; arrVarString[aa]="none"; decVar2=1; break;}
    }
   delay(170);
   }
   
    delay(200);
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
      if ((digitalRead(botonDerechaLCD)==LOW) && (!(aa<=4))){ aa=0; break; }
      else if ((digitalRead(botonDerechaLCD)==LOW) && (aa<=4)){ aa=aa+1; break;}
      else if ((digitalRead(botonCentroLCD))==LOW){ variable3=arrVarInt[aa]; arrVarString[aa]="none"; decVar3=1; break;}
    }
    delay(170);
   }

    delay(200);
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
      if ((digitalRead(botonDerechaLCD)==LOW) && (!(aa<=4))){ aa=0; break; }
      else if ((digitalRead(botonDerechaLCD)==LOW) && (aa<=4)){ aa=aa+1; break;}
      else if (digitalRead(botonCentroLCD)==LOW){ variable4=arrVarInt[aa]; arrVarString[aa]="none"; decVar4=1; break;}
    }
    delay(170);
   }
}
