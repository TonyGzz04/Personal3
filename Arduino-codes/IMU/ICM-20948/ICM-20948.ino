#include <ICM_20948.h>

ICM_20948_I2C icm;

#define WIRE_PORT Wire
#define AD0_VAL 1

float promedio=0;
float suma=0;


void setup() {
  
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  icm.begin(WIRE_PORT, AD0_VAL);

  Serial.print(F("Initialization of the sensor returned: "));
  Serial.println(icm.statusString());
  if (icm.status != ICM_20948_Stat_Ok)
    {
      Serial.println("Not initialized!");
      while(1){}
    }
/*
   for (int i=0; i<500; i++){
    if (icm.dataReady()){
    icm.getAGMT();
    float val=data(&icm);
    suma=suma+val;
    delay(10);
    }
   }
   promedio=suma/500;
  Serial.print("Promedio: ");
  Serial.println(promedio);
  delay(2000);
  */
}


void loop() {
  
  if (icm.dataReady()){
    icm.getAGMT();
    float val=data(&icm);
    Serial.println(val);
    delay(10);
  }
  else {
    Serial.println("Waiting for data");
    delay(500);
  }

}


float data(ICM_20948_I2C *sensor){
  Serial.print("Z: ");
  float val=printFormattedFloat(sensor->gyrZ(), 5, 2);
  return val;
  /* Serial.print("Y: ");
  printFormattedFloat(sensor->gyrX(), 5, 2);
  Serial.print("Z: ");
  printFormattedFloat(sensor->gyrX(), 5, 2); */
  
}


float printFormattedFloat(float val, uint8_t leading, uint8_t decimals){
  float aval = abs(val);
  if (val < 0){
    Serial.print("-");
  }
  else{
    Serial.print(" ");
  }

  for (uint8_t indi = 0; indi < leading; indi++){
    uint32_t tenpow = 0;
    if (indi < (leading-1)){ tenpow = 1; }
    for (uint8_t c = 0; c < (leading - 1 - indi); c++){ tenpow *= 10; }
    if (aval < tenpow){ Serial.print("0"); }
    else { break; }
  }
  
  if (val < 0){ return(-val,decimals); } //Serial.println(-val+promedio, decimals); }
  else { return(val,decimals); }// Serial.println(val-promedio, decimals); }

}
