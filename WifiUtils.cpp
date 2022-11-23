#include "variables.h"
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <Dictionary.h>



void Wifi_Connect(const char* ssid, const char* password) {
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(500);
  WiFi.mode(WIFI_STA);  //Only Station No AP, This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.print("Connected to ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(ssid);
}

WiFiClientSecure Client_Config(const char* FINGERPRINT) {
  WiFiClientSecure httpsClient; //Declare object of class WiFiClient
  httpsClient.setFingerprint(FINGERPRINT);
  httpsClient.setTimeout(30000); // 15 Seconds
  return httpsClient;
}

String Timestamp(NTPClient * timeClient) { // TODO: use reference or pointer for function parameter
  timeClient->update();
  unsigned long timestamp = timeClient->getEpochTime();
  return String(timestamp) + "000";
}

String GET_Request(String LINK, String HOST_NAME, const char* FINGERPRINT, String API_KEY, boolean HMAC) {
  WiFiClientSecure httpsClient = Client_Config(FINGERPRINT);
  if (httpsClient.connect(HOST_NAME, __PORT__)) {
    if (!HMAC) {
      httpsClient.print("GET " + LINK + " HTTP/1.1\r\n" +
                        "Host: " + HOST_NAME + "\r\n" +
                        "Connection: close\r\n\r\n");
    } else {
      httpsClient.print("GET " + LINK + " HTTP/1.1\r\n" +
                        "Host: " + HOST_NAME + "\r\n" +
                        "X-MBX-APIKEY: " + API_KEY + "\r\n\r\n");
    }
    unsigned int contentSize = 0;
    while (httpsClient.connected()) {
      String header = httpsClient.readStringUntil('\n');
      if (header.indexOf("Content-Length:") != -1) contentSize = header.substring(16).toInt();
      if (header == "\r") break;
    }
    //char content[contentSize];
    String content;
    while (httpsClient.available()) {
      //      size_t bytesRead = httpsClient.readBytes(content, contentSize);
      //      if (bytesRead == contentSize) Serial.println("SUCCES");
      //        String charhex = String(character, HEX);
      //        String charbin = String(character, BIN);
      char character = httpsClient.read();
      content += character;
      //        Serial.println("text: " + String(character) + " hex: " + charhex + " bin: " + charbin);
    }
    //Serial.println(contentSize);
    httpsClient.stop();
    return content;
  } else {
    return "{\"status\": \"error\"}";
  }
}

String POST_Request(String CONTENT, String LINK, String HOST_NAME, const char* FINGERPRINT, String API_KEY, boolean HMAC) {
  WiFiClientSecure httpsClient = Client_Config(FINGERPRINT);
  if (httpsClient.connect(HOST_NAME, __PORT__)) {
    if (!HMAC) {
      httpsClient.print("POST " + LINK + " HTTP/1.1\r\n" +
                        "Host: " + HOST_NAME + "\r\n" +
                        "Content-Type: application/json\r\n" +
                        "Content-Length: " + CONTENT.length() + "\r\n\r\n" +
                        CONTENT + "\r\n\r\n");
    } else {
      httpsClient.print("POST " + LINK + " HTTP/1.1\r\n" +
                        "Host: " + HOST_NAME + "\r\n" +
                        "Content-Type: application/json\r\n" +
                        "X-MBX-APIKEY: " + API_KEY + "\r\n" +
                        "Content-Length: " + CONTENT.length() + "\r\n\r\n" +
                        CONTENT + "\r\n\r\n");
    }
    unsigned int contentSize = 0;
    while (httpsClient.connected()) {
      String header = httpsClient.readStringUntil('\n');
      if (header.indexOf("Content-Length:") != -1) contentSize = header.substring(16).toInt();
      if (header == "\r") break;
    }
    String content;
    while ( httpsClient.available() ) {
      char character = httpsClient.read();
      content += character;
    }
    Serial.println(contentSize);
    httpsClient.stop();
    return content;
  } else {
    return "{\"status\": \"error\"}";
  }
}

String HMAC_SHA_256_online(String inputString, String secretKey) {
  String content = "{\"inputString\":\"" + inputString + "\",\"secretKey\":\"" + secretKey + "\",\"algo\":\"SHA-256\",\"outputFormat\":\"text\"}";
  String response = POST_Request(content , __DEVGLAN_LINK__, __DEVGLAN_HOST_NAME__, __DEVGLAN_FINGERPRINT__,__API_KEY__,false);
  response = response.substring(response.indexOf('{'), response.indexOf('}'));
  Dictionary &hashData = *(new Dictionary());
  hashData.jload(response);
  return hashData["outputString"];
}
