#include <LiquidCrystal_I2C.h>  //se incluye la librería para la LCD
LiquidCrystal_I2C lcd(0x27,16,2);     //se declara la memoria que usará la LCD y su tamaño


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Hola Mundo");
  delay(1000);

}

void loop() {
  String mensaje = "0";
  lcd.clear();
  lcd.setCursor(0,0);
  while (Serial.available()){
    String command = Serial.readString();
    mensaje = mensaje + command;
  }
  lcd.print(mensaje);
  // else {lcd.print("Nada");}
  delay(100);


}
// #include <LiquidCrystal_I2C.h>  //se incluye la librería para la LCD
// LiquidCrystal_I2C lcd(0x27,16,2);     //se declara la memoria que usará la LCD y su tamaño

// void setup() {
//   Serial.begin(9600);
//   // lcd.init();  // Change these numbers for your LCD
//   // lcd.backlight();
// }

// void loop() {
//   // lcd.clear();
//   // lcd.setCursor(0,0);
//   while (Serial.available()) {

//     int dato=Serial.read();         //lee el dato
//     int mensaje=mensaje+dato;     //junta todos los caracteres
//     Serial.println(mensaje);      //se imprime el mensaje en el monitor serie
//   }
//     // Parse the data to get the coordinates
//     // int x_min = data.substring(0, data.indexOf(',')).toInt();
//     // data = data.substring(data.indexOf(',') + 1);
//     // int y_min = data.substring(0, data.indexOf(',')).toInt();

    
//     // // Display the coordinates on the LCD
//     // lcd.setCursor(0, 1);  // Move cursor to the second line
//     // lcd.print("x1: ");
//     // lcd.print(x_min);
//     // lcd.print(" y1: ");
//     // lcd.print(y_min);
//     delay(500);

// }