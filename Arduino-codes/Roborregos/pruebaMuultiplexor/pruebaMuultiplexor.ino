#define sig A0

void setup() {
  Serial.begin(9600);
  
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  digitalWrite(8,1);
  digitalWrite(10,1);
  digitalWrite(9,1);
  

}

void loop() {
  Serial.println(analogRead(sig));

}
