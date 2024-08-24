int pinIR[13] = {7,0,0,0,0,0,0,0,0,0,0,0,0}; // pins de los sensores IR
float pulseWidth[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float previousPulseWidth[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float countMax15[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float countMin15[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float countMax32[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float countMin32[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float loopcount = 0.00;

short distancia15 = 0;
short distancia0 = 0;
float distancia = 0.0;



void setup() {
  Serial.begin(115200);
  
  for (short i=0; i<13; i++){
    pinMode(pinIR[i],INPUT);
  }
}



void loop() {
  
  distancia15 = 0.0; 
  distancia = 0.0; 

  for (short i=0; i<13; i++){ pulseWidth[i] = 0.0; countMax15[i] = 0.0; countMin15[i] = 0.0; countMax32[i] = 0.0; countMin32[i] = 0.0; }

  for (short i=0; i<50; i++){
    const unsigned long startTime = micros();
      for (short i=0; i<13; i++){
        if (digitalRead(pinIR[i]) == false){
          float deltaPulseWidth = micros() - startTime;
          pulseWidth[i] += deltaPulseWidth;
        }
          if (pulseWidth[0] == 8){ // 15cm
          countMax15[0] += 1.0; 
          }        
          /*          
          else if (pulseWidth[i] > 2950 && pulseWidth[i] < 3050){
          countMax32[i] += 1.0; 
        }       
          else if (pulseWidth[i] > 1300 && pulseWidth[i] < 1400)
          countMin32[i] += 1.0; 
        }              
          else if (pulseWidth[i] < 1500){
          countMin15[i] += 1.0; 
         }
         */
         
        
    
        

    }
  }


  

      if (countMax15[0] >= 35){
        distancia = 15;
      }
      /*
      else if (countMax32[0] >= 4 && countMin32[0] <= 4){
        distancia = 32;
      }
      else {
        distancia = 0;
      }
}
*/
    
  Serial.println(distancia);

} // cierra void loop

