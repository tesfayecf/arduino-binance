#include "arduino-binance.h"

#include <TypeConversion.h>
#include <bearssl/bearssl.h>
#include <assert.h>

static constexpr uint8_t NATURAL_LENGTH = 32;

String BinanceClient::HMAC_SHA_256(const String &message, const void *hashKey, const size_t hashKeyLength, const size_t hmacLength) {
    return createBearsslHmac(&br_sha256_vtable, NATURAL_LENGTH, message, hashKey, hashKeyLength, hmacLength);
}

String BinanceClient::createBearsslHmac(const br_hash_class *hashType, const uint8_t hashTypeNaturalLength, const String &message, const void *hashKey, const size_t hashKeyLength, const size_t hmacLength) {
    (void) hashTypeNaturalLength;
    assert(1 <= hmacLength && hmacLength <= hashTypeNaturalLength);
    uint8_t hmac[hmacLength];
    createBearsslHmac(hashType, message.c_str(), message.length(), hashKey, hashKeyLength, hmac, hmacLength);
    return experimental::TypeConversion::uint8ArrayToHexString(hmac, hmacLength);
}

void *BinanceClient::createBearsslHmac(const br_hash_class *hashType, const void *data, const size_t dataLength, const void *hashKey, const size_t hashKeyLength, void *resultArray, const size_t outputLength) {
    br_hmac_key_context keyContext; 
    br_hmac_context hmacContext;
    br_hmac_key_init(&keyContext, hashType, hashKey, hashKeyLength);
    br_hmac_init(&hmacContext, &keyContext, outputLength);
    br_hmac_update(&hmacContext, data, dataLength);
    br_hmac_out(&hmacContext, resultArray);
    return resultArray;
}
