//Librerías
#include <ICM_20948.h>
#include <HTInfraredSeeker.h>
#include "Porteria.h"
#include "Motores.h"
#include "Imu.h"
#include "PID.h"
#include "AroIR.h"

Motores motoresRobot(8,41,27,7,25,24,6,23,22);

Imu imu;
PID pid;

int v = 180;

void setup() {
  Serial.begin(9600);

  motoresRobot.iniciar();
  pid.setKP(0.3);
  imu.iniciar();

}

void loop() {
  
  for (int i=180; i>90; i--){
    motoresRobot.movimientoLineal(i,v);
    delay(15);
  }
  motoresRobot.movimientoLineal(0,0);

  while(1){}

}


int correccionesImu(){
  
  imu.readValues();
      int change = pid.calcularError(0,imu.getYaw(),v);
//      Serial.print("Change: ");
//        Serial.println(change);

//        if (change > 0) {
//          motoresRobot.giro(change, imu.isRight());
//        } else {
//          motoresRobot.apagarMotores();
//        }

        return change;
}