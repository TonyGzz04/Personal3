
void setup() {
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);


}

void loop() {

  analogWrite(3,255);
  digitalWrite(2,1);
  digitalWrite(4,0);
  analogWrite(6,255);
  digitalWrite(7,1);
  digitalWrite(8,0);
  analogWrite(11,255);
  digitalWrite(12,1);
  digitalWrite(13,0);

  // delay(1000);

  // analogWrite(10,25);
  // digitalWrite(8,1);
  // digitalWrite(9,0);
  // analogWrite(13,70);
  // digitalWrite(12,1);
  // digitalWrite(11,0);
  // analogWrite(7,70);
  // digitalWrite(5,0);
  // digitalWrite(6,1);

  // delay(1000);

}
