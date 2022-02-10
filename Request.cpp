#include <WiFiClientSecure.h> 
#include "Request.h"

String GET_Request(String LINK, char* HOST_NAME, int PORT) {
  char FINGERPRINT[] = "5B 5F CA EA D0 43 FC 52 2F D9 E2 EC A0 6C A8 57 70 DB 58 F7";
  WiFiClientSecure httpsClient = serverConnect(FINGERPRINT);
  Serial.printf("\n[Connecting to %s ... ", HOST_NAME);
  if (httpsClient.connect(HOST_NAME, PORT)) { 
    Serial.println("Connected]");
    httpsClient.print(String("GET ") + LINK + " HTTP/1.1\r\n" +
                             "Host: " + HOST_NAME + "\r\n" +               
                             "Connection: close\r\n\r\n");
    while (httpsClient.connected()) {
      String HEADERS = httpsClient.readStringUntil('\n');
      if (HEADERS == "\r") {
      break;
      }
    }
    String line;
    while(httpsClient.available()){        
      line = httpsClient.readStringUntil('\n');  //Read Line by Line
      }
    return line;    
    httpsClient.stop();                       
  } else {
    Serial.println("Connection Failed");
  }
}


WiFiClientSecure serverConnect(char fingerprint[]) {
  WiFiClientSecure httpsClient; //Declare object of class WiFiClient
  //httpsClient.setInsecure();
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000); // 15 Seconds
  return httpsClient;
}
