#include "arduino-binance.h"
#include "variables.h"
#include <WiFiClientSecure.h>

#include <NTPClient.h>
#include <WiFiUdp.h>


//String BinanceClient::api_key = "";
//String BinanceClient::api_secret = "";

WiFiUDP ntpUDP;
NTPClient* BinanceClient::timeClient_p = new NTPClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

String valid_intervals[16] = {"1m", "3m", "5m", "15m", "30m", "1h", "2h", "4h", "6h", "8h", "12h", "1d", "3d", "1w", "1M"};
String valid_windowSize[89] = {"1m", "2m", "3m", "4m", "5m", "6m", "7m", "8m", "9m", "10m", "11m", "12m", "13m", "14m", "15m", 
                              "16m", "17m", "18m", "19m", "20m", "21m", "22m", "23m", "24m", "25m", "26m", "27m", "28m", "29m", "30m", 
                              "31m", "32m", "33m", "34m", "35m", "36m", "37m", "38m", "39m", "40m", "41m", "42m", "43m", "44m", "45m", 
                              "46m", "47m", "48m", "49m", "50m", "51m", "52m", "53m", "54m", "55m", "56m", "57m", "58m", "59m",
                              "1h", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "10h", "11h", "12h", "13h", "14h", "15h", 
                              "16h", "17h", "18h", "19h", "20h", "21h", "22h", "23h", "1d", "2d", "3d", "4d", "5d", "6d", "7d"};


BinanceClient::BinanceClient() {
  this->api_key = __API_KEY__;
  this->api_secret = __API_SECRET__;
}

BinanceClient::BinanceClient(String apiKey, String apiSecret) {
  this->api_key = apiKey;
  this->api_secret = apiSecret;
}

boolean BinanceClient::Check_Interval(String interval) {
  for (unsigned i = 0; i < (sizeof(valid_intervals)); i++) {
    if (valid_intervals[i] == interval) {
      return true;
    }
  }
  return false;
}

boolean BinanceClient::Check_WindowSize(String interval) {
  for (unsigned i = 0; i < (sizeof(valid_intervals)); i++) {
    if (valid_intervals[i] == interval) {
      return true;
    }
  }
  return false;
}