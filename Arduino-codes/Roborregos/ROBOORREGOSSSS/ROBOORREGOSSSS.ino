// Motor izquierdo
int motor_i_adelante = 5;
int motor_i_atras = 6;

// Motor derecho
int motor_d_adelante = 3;
int motor_d_atras = 4;

// Ultrasonico adelante
#define echoPinDelantero 24
#define trigPinDelantero 25
int ultfrente = 0;

// Ultrasonioc derecha
#define echoPinDerecha 22
#define trigPinDerecha 23
int ultderecha = 0; 

// Ultrasonico general
int duration = 0;
int distanceDelantera = 0;
int distanceDerecha = 0;

// Listas de posicion_x, posicion_y, RGB y numero de movimientos
int x[12] = {};
int y[12] = {};
int rgb[12] = {}; // Red = 0, Green = 1, Blue = 2
int mov[12] = {};

// variables para zona 1
int direccion = 3;
int movimiento = 0;
int posicion_x = 4;
int posicion_y = 5;
int contador = 0;


int ultrasonico_adelante()
  {
    digitalWrite(trigPinDelantero, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDelantero, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDelantero, LOW);
    int duration = 0;
    duration = pulseIn(echoPinDelantero, HIGH);
    int distanceDelantera = 0;
    distanceDelantera = duration * 0.034 / 2;
    Serial.println(distanceDelantera);
    return distanceDelantera;
  }

// Ultrasonico derecha
int ultrasonico_derecha()
  {
    digitalWrite(trigPinDerecha, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDerecha, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDerecha, LOW);
    int duration = 0;
    duration = pulseIn(echoPinDerecha, HIGH);
    int distanceDerecha = 0;
    distanceDerecha = duration * 0.034 / 2;
    Serial.println(distanceDerecha);
    return distanceDerecha;
  }

void setup() 
{
  // Ultrasonicos
  pinMode(trigPinDelantero, OUTPUT);
  pinMode(echoPinDelantero, INPUT);
  pinMode(trigPinDerecha, OUTPUT);
  pinMode(echoPinDerecha, INPUT);

  // Motores
  pinMode(motor_i_adelante, OUTPUT);
  pinMode(motor_i_atras, OUTPUT);
  pinMode(motor_d_adelante, OUTPUT);
  pinMode(motor_d_atras, OUTPUT);

  Serial.begin(9600);  
}

void loop() 
{

  while (zona1==true){
    digitalWrite(trigPinDelantero, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDelantero, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDelantero, LOW);
    int duration = 0;
    duration = pulseIn(echoPinDelantero, HIGH);
    int distanceDelantera = 0;
    distanceDelantera = duration * 0.034 / 2;
    
    digitalWrite(trigPinDerecha, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinDerecha, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinDerecha, LOW);
    duration = pulseIn(echoPinDerecha, HIGH);
    int distanceDerecha = 0;
    distanceDerecha = duration * 0.034 / 2;
    contador = contador + 1;

// Para cuando esta en zona 1
  if ((posicion_x != 0) && (posicion_y != 4))
  {
    // 1 pared a la derecha y 0 adelante  Se mueve adelante
    if((distanceDerecha <= 30) && (distanceDelantera > 30))
    {
      adelante();
      movimiento = movimiento + 1;
      if (direccion == 0)
      {
        posicion_y = posicion_y + 1;
      }
      else if (direccion == 1)
      {
        posicion_x = posicion_x + 1;
      }
      else if (direccion == 2)
      {
        posicion_y = posicion_y - 1;
      }
      else if (direccion == 3)
      {
        posicion_x = posicion_x - 1;
      }
      x[movimiento] = posicion_x;
      y[movimiento] = posicion_y;
      //rgb[movimiento] = insertar sensor de color
      mov[movimiento] = movimiento;
      delay(500);  
    }
  
    // 0 pared a la derecha y 1 adelante  Gira derecha y se mueve adelante
    else if((distanceDerecha > 30) && (distanceDelantera <= 30))
    {
      derecha();
      direccion = direccion + 1;
      if (direccion == 4)
      {
        direccion = 0;
      }
      delay(500);
      adelante();
      movimiento = movimiento + 1;
      if (direccion == 0)
      {
        posicion_y = posicion_y + 1;
      }
      else if (direccion == 1)
      {
        posicion_x = posicion_x + 1;
      }
      else if (direccion == 2)
      {
        posicion_y = posicion_y - 1;
      }
      else if (direccion == 3)
      {
        posicion_x = posicion_x - 1;
      }
      x[movimiento] = posicion_x;
      y[movimiento] = posicion_y;
      //rgb[movimiento] = insertar sensor de color
      mov[movimiento] = movimiento;
      delay(500);
    }
  
    // 1 pared a la derecha y 1 adelante  Gira izquierda y se mueve adelante 
    else if((distanceDerecha <= 30) && (distanceDelantera <= 30))
    {
      izquierda();
      direccion = direccion - 1;
      if (direccion == -1)
      {
        direccion = 0;
      }
      delay(500);
      atras();
      delay(500);
      corto_adelante();
      delay(500);
    }
  
    // 0 pared a la derecha y 0 adelante  Gira derecha y se mueve adelante 
    else if((distanceDerecha > 30) && (distanceDelantera > 30))
    {
      derecha();
      direccion = direccion + 1;
      if (direccion == 4)
      {
        direccion = 0;
      }
      delay(500);
      atras();
      delay(500);
      corto_adelante();
      delay(500);
      adelante();
      movimiento = movimiento + 1;
      if (direccion == 0)
      {
        posicion_y = posicion_y + 1;
      }
      else if (direccion == 1)
      {
        posicion_x = posicion_x + 1;
      }
      else if (direccion == 2)
      {
        posicion_y = posicion_y - 1;
      }
      else if (direccion == 3)
      {
        posicion_x = posicion_x - 1;
      }
      x[movimiento] = posicion_x;
      y[movimiento] = posicion_y;
      //rgb[movimiento] = insertar sensor de color
      mov[movimiento] = movimiento;
      delay(500);
    }
  
    // por si ve algo mas
    else
    {
      alto();
      delay(500);
    }
  }

  else if ((posicion_x == 0) && (posicion_y = 3))
  {
    derecha();
    direccion = direccion + 1;
    if (direccion == 4)
      {
        direccion = 0;
      }
    delay(100);
    derecha();
    direccion = direccion + 1;
    if (direccion == 4)
      {
        direccion = 0;
      }
    delay(100);
    adelante();
  }

  else if (((posicion_x == 4) && (posicion_y == 5)) && (contador != 0))
  {
    //insertar la comparacion para la "x"
  }
  } //cierra zona 1

adelante(); //para avanzar al primer cuadrado de la zona 3

  while (zona3==true){
    
    distanceDelantera=ultrasonico_adelante();
    distanceDerecha=ultrasonico_derecha();
    digitalWrite(motor_i_adelante, HIGH);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, HIGH);
    digitalWrite(motor_d_atras, LOW);
    while (color==1){ color=detectarColor(); }
    zona3_atras();
    
    
    
  } //cierra zona 3


  
}

// movimientos basicos del robot
void adelante()
{
    digitalWrite(motor_i_adelante, HIGH);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, HIGH);
    digitalWrite(motor_d_atras, LOW);
    delay(750);
    digitalWrite(motor_i_adelante, LOW);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, LOW);
    digitalWrite(motor_d_atras, LOW);
}

void atras()
{
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, HIGH);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, HIGH);
  delay(800);
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
}

void izquierda()
{
  // Girar a la izquierda (predefinido)
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, HIGH);
  digitalWrite(motor_d_adelante, HIGH);
  digitalWrite(motor_d_atras, LOW);
  delay(800); // Ajustar tiempo para establecer bien el giro
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
}

void derecha()
{
  // Girar a la izquierda (predefinido)
  digitalWrite(motor_i_adelante, HIGH);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, HIGH);
  delay(800);                               // Ajustar tiempo para establecer bien el giro
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
}

void corto_adelante()
{
    digitalWrite(motor_i_adelante, HIGH);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, HIGH);
    digitalWrite(motor_d_atras, LOW);
    delay(150);
    digitalWrite(motor_i_adelante, LOW);
    digitalWrite(motor_i_atras, LOW);
    digitalWrite(motor_d_adelante, LOW);
    digitalWrite(motor_d_atras, LOW);
}

void zona3_atras()
{
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, HIGH);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, HIGH);
  delay(200);
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
}

void alto()
{
  digitalWrite(motor_i_adelante, LOW);
  digitalWrite(motor_i_atras, LOW);
  digitalWrite(motor_d_adelante, LOW);
  digitalWrite(motor_d_atras, LOW);
}

void 
