#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int ok=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<10; i++)
  {
    lcd.println(i);
    ok=lcd._cols;
    Serial.println(ok);
    delay(500);
  }

  
  
  
}
