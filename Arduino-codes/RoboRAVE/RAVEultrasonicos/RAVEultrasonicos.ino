#include "Ultrasonicos.h"

Ultrasonicos sonic(53, 52, 51, 50); // trigIz, echoIz, trigDe, echoDe


void setup(){
  Serial.begin(9600);
  
  sonic.iniciar();


}


void loop()
{
  Serial.println(sonic.getDistanciaDe());

}
