#include "arduino-binance.h"


BinanceClient Binance("HOLA","HOLA_secret");

void setup() {
  Serial.begin(9600);
  Wifi_Connect();

}

void loop() {

}
