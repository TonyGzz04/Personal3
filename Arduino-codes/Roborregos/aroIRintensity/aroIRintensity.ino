int pinIR = 14;

short distancia15 = 0;
short distancia0 = 0;
float distancia = 0.0;

int count = 0;
double intensity = 0;



void setup() {
  Serial.begin(9600);
  pinMode(pinIR,INPUT);
}



void loop() {
  

  const unsigned long startTime = micros();
  do{
    if (digitalRead(pinIR) == false){   // si detecta algo
      count += 1;
    }
  } while ((micros() - startTime) < 833);

  Serial.print("Cuenta: ");
  Serial.println(count);

  intensity = count / 0.000833 * 0.33;
  Serial.print("Intensidad: ");
  Serial.println(intensity);

  while(1){}

} // cierra void loop

