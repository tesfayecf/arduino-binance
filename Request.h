#ifndef Request 
#define Request
#include <WiFiClientSecure.h> 

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


String GET_Request(WiFiClientSecure httpsClient, String LINK, char* HOSTNAME = "api.binance.com");

#endif
