int motor_i_adelante = 5;
int motor_i_atras = 6;

// Motor derecho
int motor_d_adelante = 3;
int motor_d_atras = 4;

void setup() {
   pinMode(motor_i_adelante, OUTPUT);
  pinMode(motor_i_atras, OUTPUT);
  pinMode(motor_d_adelante, OUTPUT);
  pinMode(motor_d_atras, OUTPUT);

  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

}

void loop() {
  
    digitalWrite(motor_i_adelante, HIGH);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, HIGH);
    digitalWrite(motor_d_atras, LOW);
    analogWrite(10,255);
    analogWrite(11,255);
    analogWrite(12,255);
    analogWrite(13,255);

    delay(1000);
    

    analogWrite(10,255);
    analogWrite(11,0);
    analogWrite(12,0);
    analogWrite(13,255);

    delay(1000);
    
    /*

    digitalWrite(motor_i_adelante, LOW);
      digitalWrite(motor_i_atras, LOW);
      digitalWrite(motor_d_adelante, LOW);
      digitalWrite(motor_d_atras, LOW);

      delay(1000);
      */

}
