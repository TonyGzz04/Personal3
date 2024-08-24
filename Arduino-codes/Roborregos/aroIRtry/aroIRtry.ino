unsigned short pinIR[13] = {7,0,0,0,0,0,0,0,0,0,0,0,0}; // pins de los sensores IR
unsigned short pulseWidth[13][500] = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {} };




void setup() {
  Serial.begin(115200);
  
  for (short i=0; i<13; i++){
    pinMode(pinIR[i],INPUT);
  }
}



void loop() {
  

  // for (short i=0; i<13; i++){ pulseWidth[i] = 0.0; countMax[i] = 0.0; countMin[i] = 0.0; }

      Serial.println(leer0());

      

      
      

    
  //Serial.println(pulseWidth[0]);

} // cierra void loop


int leer0(){
  const unsigned long startTime = micros();
   if (digitalRead(pinIR[0]) == false){
    float deltaPulseWidth = micros() - startTime;
    return pulseWidth[0][0] = deltaPulseWidth;
   }
}


void leerIR(){
  for (int j=0; j<500; j++){
    const unsigned long startTime = micros();
      for (short i=0; i<13; i++){
        if (digitalRead(pinIR[i]) == false){
          float deltaPulseWidth = micros() - startTime;
          pulseWidth[i][j] = deltaPulseWidth;
      }
    }
  }
}



