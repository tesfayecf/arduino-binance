#include "arduino-binance.h"
#include "variables.h"


String BinanceClient::MARKET_DATA_ENDPOINTS::Ping() {
  String BASE = "/api/v3/ping";
  String LINK = BASE;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Server_Time() {
  String BASE = "/api/v3/time";
  String LINK = BASE;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Exchange_Info(String symbol, boolean symbols) {
  String PARAMS, LINK;
  String BASE = "/api/v3/exchangeInfo";
  if (!symbols) PARAMS = String("?") + String("symbol=") + symbol;
  else PARAMS = String("?") + String("symbols=") + symbol;
  if (symbol != "") LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Exchange_Info(String symbol) {
  return Exchange_Info(symbol, false);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Exchange_Info() {
  return Exchange_Info("", false);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Depth(String symbol, int limit) {
  if (limit > 5000) limit = 5000;
  String BASE = "/api/v3/depth";
  String LINK;
  String PARAMS = String("?") + String("symbol=") + symbol;
  String PARAMS2 = String("&") + String("limit=") + limit;
  if (limit == 0) LINK = BASE + PARAMS;
  else LINK = BASE + PARAMS + PARAMS2;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Depth(String symbol) {
  return Depth(symbol, 100);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Trades(String symbol, int limit) {
  if (limit > 1000) limit = 1000;
  String BASE = "/api/v3/trades";
  String PARAMS = String("?") + String("symbol=") + symbol + String("&") +
                  String("limit=") + limit;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Trades(String symbol) {
  return Trades(symbol,500);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Historical_Trades(String symbol, long fromId, int limit) {
  if (limit > 1000) limit = 1000;
  String BASE = "/api/v3/historicalTrades";
  String PARAMS = String("?") + String("symbol=") + symbol + String("&") +
                  String("limit=") + limit + String("&") +
                  String("fromId") + fromId;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);

}

String BinanceClient::MARKET_DATA_ENDPOINTS::Historical_Trades(String symbol, int limit) {
  if (limit > 1000) limit = 1000;
  String BASE = "/api/v3/historicalTrades";
  String PARAMS = String("?") + String("symbol=") + symbol + String("&") +
                  String("limit=") + limit;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Historical_Trades(String symbol, long fromId) {
  return Historical_Trades(symbol, fromId, 500);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Historical_Trades(String symbol) {
  return Historical_Trades(symbol, 500);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Agg_Trades(String symbol, long fromId, int limit) {
  if (limit > 1000) limit = 1000;
  String BASE = "/api/v3/aggTrades";
  String PARAMS = String("?") + String("symbol=") + symbol + String("&") +
                  String("fromId=") + fromId  + String("&") + 
                  String("limit") + limit;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Agg_Trades(String symbol, long startTime, long endTime) {
  if (endTime - startTime > 3600000) endTime = startTime + 3600000;
  String BASE = "/api/v3/aggTrades";
  String PARAMS = String("?") + String("symbol=") + symbol + String("&") +
                  String("startTime=") + startTime + String("&") +
                  String("endTime=") + endTime;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Agg_Trades(String symbol, long fromId) {
  return Agg_Trades(symbol, fromId, 500);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Agg_Trades(String symbol, int limit) {
  if (limit > 1000) limit = 1000;
  String BASE = "/api/v3/aggTrades";
  String PARAMS = String("?") + String("symbol=") + symbol + String("&") +
                  String("limit=") + limit;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Agg_Trades(String symbol) {
  return Agg_Trades(symbol, 500);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Get_Klines(String symbol, String interval, long startTime, long endTime) {
  if (!BinanceClient::Check_Interval(interval)) interval = "5m";
  String BASE = "/api/v3/klines";
  String PARAMS = String("?") + String("symbol=") + symbol + String("&") +
                  String("interval=") + interval + String("&") +
                  String("startTime=") + startTime + String("&") +
                  String("endTime=") + endTime;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Get_Klines(String symbol, String interval, int limit) {
  if (limit > 1000) limit = 1000;
  if (!BinanceClient::Check_Interval(interval)) interval = "5m";
  String BASE = "/api/v3/klines";
  String PARAMS = String("?") + String("symbol=") + symbol + String("&") +
                  String("interval=") + interval + String("&") +
                  String("limit=") + limit;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Get_Klines(String symbol, String interval) {
  return Get_Klines(symbol, interval, 500);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Avg_Price(String symbol) {
  String BASE = "/api/v3/avgPrice";
  String PARAMS = String("?") + String("symbol=") + symbol;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::TPC_Statistics_24hr(String symbol, boolean symbols, String type) {
  String PARAMS;
  String BASE = "/api/v3/ticker/24hr";
  if (symbol != "") {
    if (!symbols) PARAMS = String("?") + String("symbol=") + symbol + String("&");
    else PARAMS = String("?") + String("symbols=") + symbol + String("&");
  } else PARAMS = String("?") + String("type=") + type;;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::TPC_Statistics_24hr(String symbol, boolean symbols) {
  return TPC_Statistics_24hr(symbol, symbols, "FULL");
}

String BinanceClient::MARKET_DATA_ENDPOINTS::TPC_Statistics_24hr(String symbol) {
  return TPC_Statistics_24hr(symbol, false, "FULL");
}

String BinanceClient::MARKET_DATA_ENDPOINTS::TPC_Statistics_24hr() {
  return TPC_Statistics_24hr("", false, "FULL");
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Price_Ticker(String symbol, boolean symbols) {
  String PARAMS;
  String BASE = "/api/v3/ticker/price";
  if (!symbols) PARAMS = String("?") + String("symbol=") + symbol + String("&");
  else PARAMS = String("?") + String("symbols=") + symbol + String("&");
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Price_Ticker(String symbol) {
  return Symbol_Order_Book_Ticker(symbol, false);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Price_Ticker() {
  return Symbol_Order_Book_Ticker("", false);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Order_Book_Ticker(String symbol, boolean symbols) {
  String PARAMS;
  String BASE = "/api/v3/ticker/bookTicker";
  if (!symbols) PARAMS = String("?") + String("symbol=") + symbol + String("&");
  else PARAMS = String("?") + String("symbols=") + symbol + String("&");
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Order_Book_Ticker(String symbol) {
  return Symbol_Order_Book_Ticker(symbol, false);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Order_Book_Ticker() {
  return Symbol_Order_Book_Ticker("", false);
}


String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Rolling_Window_Statistics(String symbol, boolean symbols, String windowSize, String type) {
  if (!BinanceClient::Check_WindowSize(windowSize)) windowSize = "1d";
  String PARAMS;
  String BASE = "/api/v3/ticker";
  if (!symbols) PARAMS = String("?") + String("symbol=") + symbol + String("&");
  else PARAMS = String("?") + String("symbols=") + symbol + String("&");
  PARAMS += String("windowSize=") + windowSize + String("&") +
            String("type") + type;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK, __BINANCE_HOST_NAME__);
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Rolling_Window_Statistics(String symbol, boolean symbols, String windowSize) {
  return Symbol_Rolling_Window_Statistics(symbol, symbols, windowSize, "FULL");
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Rolling_Window_Statistics(String symbol, boolean symbols) {
  return Symbol_Rolling_Window_Statistics(symbol, symbols, "1d", "FULL");
}

String BinanceClient::MARKET_DATA_ENDPOINTS::Symbol_Rolling_Window_Statistics(String symbol) {
  return Symbol_Rolling_Window_Statistics(symbol, false, "1d", "FULL");
}

