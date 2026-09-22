#ifndef MKE_I2C_RFID_H
#define MKE_I2C_RFID_H

#include <Arduino.h>
#include <Wire.h>

#define MKE_I2C_RFID_DEFAULT_ADDR 0x29

// General Module Info Mode IDs
#define MKE_RFID_MODE_SET_ADDRESS             1
#define MKE_RFID_MODE_GET_ID_MODULE           2
#define MKE_RFID_MODE_SET_ID_MODULE           3
#define MKE_RFID_MODE_GET_FW_VERSION          4
#define MKE_RFID_MODE_SET_FW_VERSION          5
#define MKE_RFID_MODE_GET_PRODUCT_CODE        6
#define MKE_RFID_MODE_SET_PRODUCT_CODE        7
#define MKE_RFID_MODE_SET_LAST_UNIXTIME_TEST  8
#define MKE_RFID_MODE_GET_LAST_UNIXTIME_TEST  9
#define MKE_RFID_MODE_GET_ADDRESS             10

// Specific RFID Mode IDs (from MakerEdu_RFID_Commands.h)
#define MKE_RFID_MODE_GET_UID          50
#define MKE_RFID_MODE_GET_UID_FULL     51
#define MKE_RFID_MODE_GET_UID_SIZE     52
#define MKE_RFID_MODE_GET_CARD_TYPE    53
#define MKE_RFID_MODE_GET_SAK          54
#define MKE_RFID_MODE_IS_CARD_PRESENT  55

#define MKE_RFID_MODE_AUTH_KEY_A       70
#define MKE_RFID_MODE_AUTH_KEY_B       71
#define MKE_RFID_MODE_SET_KEY          72
#define MKE_RFID_MODE_SET_KEY_LOW      73
#define MKE_RFID_MODE_READ_BLOCK       75
#define MKE_RFID_MODE_WRITE_BLOCK_DATA_HIGH 76
#define MKE_RFID_MODE_WRITE_BLOCK_DATA_MID1 77
#define MKE_RFID_MODE_WRITE_BLOCK_DATA_MID2 78
#define MKE_RFID_MODE_WRITE_BLOCK_DATA_LOW  79
#define MKE_RFID_MODE_WRITE_BLOCK_EXECUTE   80
#define MKE_RFID_MODE_GET_LAST_STATUS  81
#define MKE_RFID_MODE_SET_UID_EXECUTE  82

#define MKE_RFID_MODE_GET_VALUE        90
#define MKE_RFID_MODE_SET_VALUE        91
#define MKE_RFID_MODE_SET_TARGET_BLOCK 92
#define MKE_RFID_MODE_INCREMENT        93
#define MKE_RFID_MODE_DECREMENT        94

#define MKE_RFID_MODE_HALT_CARD        100
#define MKE_RFID_MODE_STOP_CRYPTO      101
#define MKE_RFID_MODE_SET_ANTENNA_GAIN 102
#define MKE_RFID_MODE_GET_ANTENNA_GAIN 103
#define MKE_RFID_MODE_SELF_TEST        104
#define MKE_RFID_MODE_GET_FW_RC522     105

#define MKE_RFID_MODE_UNLOCK_ADMIN     200
#define MKE_RFID_MODE_FACTORY_RESET    201

class MKE_I2C_RFID {
public:
    MKE_I2C_RFID(TwoWire *wire = &Wire);
    
    bool begin(uint8_t address = MKE_I2C_RFID_DEFAULT_ADDR);
    
    // General Module Information
    uint8_t getI2CAddress();
    void setI2CAddress(uint8_t newAddress);
    
    uint8_t getModuleID();
    uint32_t getFirmwareVersion();
    
    // Core RFID Functions
    bool isCardPresent();
    uint32_t getUID(); // Returns the first 4 bytes of UID as a uint32_t
    uint8_t getUIDSize();
    uint8_t getCardType();
    uint8_t getSAK();
    
    // Read Full UID (up to 10 bytes)
    // uidBuffer must be at least 10 bytes long. Returns actual size read.
    uint8_t getUIDFull(uint8_t *uidBuffer);
    
    // MIFARE Classic Block Operations
    // Note: status codes correspond to MFRC522::StatusCode. 0 is STATUS_OK.
    void setAuthKey(const uint8_t key[6]);
    uint8_t authenticateKeyA(uint8_t blockAddr);
    uint8_t authenticateKeyB(uint8_t blockAddr);
    
    // Read 16 bytes from a block
    // buffer must be 16 bytes long. Returns status code.
    uint8_t readBlock(uint8_t blockAddr, uint8_t *buffer);
    
    // Write 16 bytes to a block
    // allowSectorTrailerWrite: if false, prevents writing to Sector Trailers to avoid bricking the card
    uint8_t writeBlock(uint8_t blockAddr, const uint8_t *buffer, bool allowSectorTrailerWrite = false);
    
    // Status
    uint8_t getLastStatus();
    
    // MIFARE Classic Value Block Operations
    uint8_t setValue(uint8_t blockAddr, int32_t value, bool allowSectorTrailerWrite = false);
    uint8_t getValue(uint8_t blockAddr, int32_t *value);
    uint8_t incrementValue(uint8_t blockAddr, int32_t delta, bool allowSectorTrailerWrite = false);
    uint8_t decrementValue(uint8_t blockAddr, int32_t delta, bool allowSectorTrailerWrite = false);
    
    // Magic Card (Gen1a) features (Under Development)
    int8_t setUID(uint8_t* newUID, uint8_t uidSize = 4);
    
    // Module Control
    void haltCard();
    void stopCrypto();
    void setAntennaGain(uint8_t gain);
    uint8_t getAntennaGain();
    uint8_t getRC522FirmwareVersion();
    bool performSelfTest();
    
    // Safety Helpers
    bool isSectorTrailer(uint8_t blockAddr);
    
protected:
    TwoWire *_wire;
    uint8_t _address;

    void sendCommand(uint8_t modeId, uint32_t payload = 0);
    uint32_t requestData(uint8_t modeId, uint32_t payload = 0);
    uint32_t floatToUint32(float value);
    float uint32ToFloat(uint32_t value);
};

// ==============================================================================
// ADVANCED CLASS (FOR MANUFACTURERS / FACTORY SETUP)
// ==============================================================================
class MKE_I2C_RFID_Advanced : public MKE_I2C_RFID {
public:
    MKE_I2C_RFID_Advanced(uint8_t address = MKE_I2C_RFID_DEFAULT_ADDR) : MKE_I2C_RFID() {}

    // Advanced Factory Info (Getters)
    uint16_t getProductCode();
    uint32_t getLastUnixtimeTest();
    
    // Factory Reset / Admin Mode
    void unlockAdminMode(uint32_t password = 0xA5A5A5A5);
    void factoryReset();
    
};

#endif
