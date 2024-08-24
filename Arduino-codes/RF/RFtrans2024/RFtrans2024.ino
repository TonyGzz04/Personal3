#include <RH_NRF24.h>

RH_NRF24 nrf24(4, 3); // CSN, CE


void setup() {
  Serial.begin(115200);
  if (!nrf24.init()) { Serial.println("init failed"); }


  if (!nrf24.setChannel(3)) 
  {
    Serial.println("setChannel failed");
  }
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) {
    Serial.println("setRF failed");
  }
  Serial.println("Transmitter started");

}

void loop() {
  // put your main code here, to run repeatedly:

}
