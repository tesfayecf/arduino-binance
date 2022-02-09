#include <WiFiClientSecure.h> 
#include "Request.h"

String GET_Request(WiFiClientSecure httpsClient, String LINK, char* HOST_NAME) {
  
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
}
