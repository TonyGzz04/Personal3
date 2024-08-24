int pinIR[13] = {14,0,0,0,0,0,0,0,0,0,0,0,0}; // pins de los sensores IR
float pulseWidth[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float previousPulseWidth[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float countMax[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 
float countMin[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; 

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
  distancia0 = 0.0; 

  for (short i=0; i<13; i++){ pulseWidth[i] = 0.0; countMax[i] = 0.0; countMin[i] = 0.0; }

  const unsigned long startTime = micros();
      for (short i=0; i<13; i++){
        if (digitalRead(pinIR[i]) == false){
          float deltaPulseWidth = micros() - startTime;
          pulseWidth[i] += deltaPulseWidth;
          
      }
      Serial.println(pulseWidth[0]);
    }

    
  //Serial.println(pulseWidth[0]);

} // cierra void loop

