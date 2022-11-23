#include "arduino-binance.h"
#include "variables.h"

String BinanceClient::WALLET_ENDPOINTS::System_Status() {
  String BASE = "/sapi/v1/system/status";
  String LINK = BASE;
  return GET_Request(LINK,__BINANCE_HOST_NAME__);
}

String BinanceClient::WALLET_ENDPOINTS::All_Coins_Info() {
  String TIMESTAMP = Timestamp(timeClient_p);
  Serial.println(TIMESTAMP);
  String BASE = "/sapi/v1/capital/config/getall";
  String CONN = String("?"); 
  String PARAMS = String("recvWindow=") + __RECV_WINDOW__  + String("&") + 
                  String("timestamp=") + TIMESTAMP;
  String SIGNATURE = HMAC_SHA_256(PARAMS,__API_SECRET__, __API_KEY_LENGTH__, __HASH_LENGTH__);
  String LINK = BASE + CONN + PARAMS + String("&") + String("signature=") + SIGNATURE;
  return GET_Request(LINK,__BINANCE_HOST_NAME__,__BINANCE_FINGERPRINT__,__API_KEY__,true);
}

String BinanceClient::WALLET_ENDPOINTS::Daily_Account_Snapshot(String type, int limit) {
  String TIMESTAMP = Timestamp(timeClient_p);
  String BASE = "/sapi/v1/accountSnapshot";
  String CONN = String("?"); 
  String PARAMS = String("type=") + type  + String("&") +
                  String("limit=") + limit  + String("&") +
                  String("recvWindow=") + __RECV_WINDOW__  + String("&") + 
                  String("timestamp=") + TIMESTAMP;
  String SIGNATURE = HMAC_SHA_256(PARAMS,__API_SECRET__, __API_KEY_LENGTH__, __HASH_LENGTH__);
  String LINK = BASE + CONN + PARAMS + String("&") + String("signature=") + SIGNATURE;
  return GET_Request(LINK,__BINANCE_HOST_NAME__,__BINANCE_FINGERPRINT__,__API_KEY__,true); 
}

String BinanceClient::WALLET_ENDPOINTS::Disable_Fast_Withdraw_Switch() {
  String TIMESTAMP = Timestamp(timeClient_p);
  String BASE = "/sapi/v1/account/disableFastWithdrawSwitch";
  String CONN = String("?"); 
  String PARAMS = String("recvWindow=") + __RECV_WINDOW__  + String("&") + 
                  String("timestamp=") + TIMESTAMP;
  String SIGNATURE = HMAC_SHA_256(PARAMS,__API_SECRET__, __API_KEY_LENGTH__, __HASH_LENGTH__);
  String BODY = PARAMS + String("&") + String("signature=") + SIGNATURE;
  String LINK = BASE + CONN + PARAMS + String("&") + String("signature=") + SIGNATURE;
  return POST_Request(BODY,BASE,__BINANCE_HOST_NAME__,__BINANCE_FINGERPRINT__,__API_KEY__,true);
}

String BinanceClient::WALLET_ENDPOINTS::Enable_Fast_Withdraw_Switch() {
  String TIMESTAMP = Timestamp(timeClient_p);
  String BASE = "/sapi/v1/account/enableFastWithdrawSwitch";
  String CONN = String("?"); 
  String PARAMS = String("recvWindow=") + __RECV_WINDOW__  + String("&") + 
                  String("timestamp=") + TIMESTAMP;
  String SIGNATURE = HMAC_SHA_256(PARAMS,__API_SECRET__, __API_KEY_LENGTH__, __HASH_LENGTH__);
  String LINK = BASE + CONN + PARAMS + String("&") + String("signature=") + SIGNATURE;
  return POST_Request(" ",LINK,__BINANCE_HOST_NAME__,__BINANCE_FINGERPRINT__,__API_KEY__,true);
}
