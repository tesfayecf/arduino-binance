#ifndef M_D_E //MARKET_DATA_ENDPOINTS
#define M_D_E
#include <WiFiClientSecure.h> 
#include "Request.h"

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

String ping(WiFiClientSecure httpsClient);

String serverTime(WiFiClientSecure httpsClient);

String exchangeInfo(WiFiClientSecure httpsClient, String pair);

String depth(WiFiClientSecure httpsClient, String pair, int limit);

String trades(WiFiClientSecure httpsClient, String pair, int limit);

String historicalTrades(WiFiClientSecure httpsClient, String pair, int limit);

String aggTrades(WiFiClientSecure httpsClient, String pair, int limit);

String getKlines(WiFiClientSecure httpsClient, String pair, String interval, int limit);

String avgPrice(WiFiClientSecure httpsClient, String pair);

String TPC_Statistics_24hr(WiFiClientSecure httpsClient, String pair);

String Symbol_Price_Ticker(WiFiClientSecure httpsClient, String pair);

String Symbol_Order_Book_Ticker(WiFiClientSecure httpsClient, String pair);

#endif
