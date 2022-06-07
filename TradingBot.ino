#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include "MARKET_DATA_ENDPOINTS.H"
#include "Request.h"

//#include <CustomJWT.h>

const char *ssid = "";  //ENTER YOUR WIFI SETTINGS
const char *password = "";

const char API_KEY[] = "";
const char API_SECRET[] = "";


const char *HOST_NAME = "api.binance.com";
const int HTTP_PORT = 443;  //HTTPS= 443 and HTTP = 80
const char fingerprint[] PROGMEM = "";

//Get timestamp
#include <NTPClient.h>
#include <WiFiUdp.h>
#define NTP_OFFSET   60 * 0      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "europe.pool.ntp.org"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(500);
  WiFi.mode(WIFI_STA);        //Only Station No AP, This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  timeClient.begin();
}

void loop() {
  

  WiFiClientSecure httpsClient;    //Declare object of class WiFiClient
  
  Serial.println(HOST_NAME);
  //httpsClient.setInsecure();

  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000); // 15 Seconds
  
  Serial.printf("\n[Connecting to %s ... ", HOST_NAME);
  if (httpsClient.connect(HOST_NAME, HTTP_PORT)) {

    Serial.println("Connected]");
    String pair = "BTCUSDT";
    String interval = "1m";
    int limit = 5;
    
    
    //Serial.println(depth(httpsClient, pair, limit));
    Serial.println(serverTime(httpsClient));
    Serial.println(getTimestamp(timeClient));
    //Serial.println(getKlines(httpsClient, pair, interval, limit));

  } else {
    Serial.println("Connection Failed");
  }
    
  delay(5000);  //GET Data at every 2 seconds
}



//---------------------------------------------------------
//                 MARKET DATA ENDPOINTS
//---------------------------------------------------------


//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------








unsigned long getTimestamp(NTPClient timeClient) {
  timeClient.update();
  unsigned long timestamp = timeClient.getEpochTime();
  //unsigned long timeMilli = timestamp * 1000;
  return timestamp;
}
