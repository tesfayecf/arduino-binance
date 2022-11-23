#ifndef arduino_binance
#define arduino_binance

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "variables.h"
#include <WiFiClientSecure.h>
#include <NTPClient.h>


/*
variables -> name_second
function -> Name_Second()
class -> NAME_SECOND()
*/


class BinanceClient{
  private:
    String api_key;
    String api_secret;
    
    static NTPClient * timeClient_p;

    static String valid_intervals[16];
    static boolean Check_Interval(String interval);

    static String valid_windowSize[89];
    static boolean Check_WindowSize(String interval);

    //sha256
    static String HMAC_SHA_256(const String &message, const void *hashKey, const size_t hashKeyLength, const size_t hmacLength);
    static String createBearsslHmac(const br_hash_class *hashType, const uint8_t hashTypeNaturalLength, const String &message, const void *hashKey, const size_t hashKeyLength, const size_t hmacLength);
    static void *createBearsslHmac(const br_hash_class *hashType, const void *data, const size_t dataLength, const void *hashKey, const size_t hashKeyLength, void *resultArray, const size_t outputLength);

  public:

    BinanceClient();
    BinanceClient(String apiKey, String apiSecret);
    
    class MARKET_DATA_ENDPOINTS {
      
      public:
        MARKET_DATA_ENDPOINTS() {}; 
    
        String Ping();
        
        String Server_Time();
        
        String Exchange_Info(String symbol, boolean symbols);
        String Exchange_Info(String symbol);
        String Exchange_Info();
        
        String Depth(String symbol, int limit);
        String Depth(String symbol);

        String Trades(String symbol, int limit);
        String Trades(String symbol);
        
        String Historical_Trades(String symbol, long fromId, int limit);
        String Historical_Trades(String symbol, int limit);
        String Historical_Trades(String symbol, long tradeID);
        String Historical_Trades(String symbol);

        String Agg_Trades(String symbol, long fromId, int limit);
        String Agg_Trades(String symbol, long startTime, long endTime);
        String Agg_Trades(String symbol, long fromId);
        String Agg_Trades(String symbol, int limit);
        String Agg_Trades(String symbol);

        String Get_Klines(String symbol, String interval, long startTime, long endTime);
        String Get_Klines(String symbol, String interval, int limit);
        String Get_Klines(String symbol, String interval);

        String Avg_Price(String symbol);

        String TPC_Statistics_24hr(String symbol, boolean symbols, String type);
        String TPC_Statistics_24hr(String symbol, boolean symbols);
        String TPC_Statistics_24hr(String symbol);
        String TPC_Statistics_24hr();

        String Symbol_Price_Ticker(String symbol, boolean symbols);
        String Symbol_Price_Ticker(String symbol);
        String Symbol_Price_Ticker();


        String Symbol_Order_Book_Ticker(String symbol, boolean symbols);
        String Symbol_Order_Book_Ticker(String symbol);
        String Symbol_Order_Book_Ticker();

        String Symbol_Rolling_Window_Statistics(String symbol, boolean symbols, String windowSize, String type);
        String Symbol_Rolling_Window_Statistics(String symbol, boolean symbols, String windowSize);
        String Symbol_Rolling_Window_Statistics(String symbol, boolean symbols);
        String Symbol_Rolling_Window_Statistics(String Symbol);

      
    };

    class WALLET_ENDPOINTS {

      public:
        WALLET_ENDPOINTS() {};

        String System_Status();

        String All_Coins_Info();
        
        String Daily_Account_Snapshot(String type = "SPOT", int limit = 7);
        
        String Disable_Fast_Withdraw_Switch();
        
        String Enable_Fast_Withdraw_Switch();
    };

    MARKET_DATA_ENDPOINTS  MARKET_DATA;

    WALLET_ENDPOINTS WALLET;
};




// wifi utils start

void Wifi_Connect(const char* ssid = __ssid__, const char* password = __password__);

WiFiClientSecure Client_Config(const char* FINGERPRINT);

String Timestamp(NTPClient * timeClient);

String GET_Request(String LINK, String HOST_NAME, const char* FINGERPRINT = __BINANCE_FINGERPRINT__, String API_KEY = "", boolean HMAC = false);

String POST_Request(String CONTENT, String LINK, String HOST_NAME, const char* FINGERPRINT = __BINANCE_FINGERPRINT__, String API_KEY = "", boolean HMAC = false);

String HMAC_SHA_256_online(String inputString, String secretKey);

// wifi utils end


#endif
