#include "MKE_I2C_RFID.h"

MKE_I2C_RFID::MKE_I2C_RFID(TwoWire *wire) {
    _wire = wire;
    _address = MKE_I2C_RFID_DEFAULT_ADDR;
}

bool MKE_I2C_RFID::begin(uint8_t address) {
    _address = address;
    
    // Check if the module responds by querying the module ID
    uint8_t id = getModuleID();
    if (id == 0 || id == 0xFF) {
        return false;
    }
    return true;
}

void MKE_I2C_RFID::sendCommand(uint8_t modeId, uint32_t payload) {
    uint8_t v0 = (payload >> 24) & 0xFF;
    uint8_t v1 = (payload >> 16) & 0xFF;
    uint8_t v2 = (payload >> 8) & 0xFF;
    uint8_t v3 = payload & 0xFF;
    uint8_t chkTx = _address ^ modeId ^ v0 ^ v1 ^ v2 ^ v3;

    _wire->beginTransmission(_address);
    _wire->write(_address);
    _wire->write(modeId);
    _wire->write(v0);
    _wire->write(v1);
    _wire->write(v2);
    _wire->write(v3);
    _wire->write(chkTx);
    _wire->endTransmission();
}

uint32_t MKE_I2C_RFID::requestData(uint8_t modeId, uint32_t payload) {
    sendCommand(modeId, payload);
    
    unsigned long startT = millis();
    while (millis() - startT < 100) {
        _wire->requestFrom(_address, (uint8_t)6);
        if (_wire->available() >= 6) {
            uint8_t rxMode = _wire->read();
            uint8_t d0 = _wire->read();
            uint8_t d1 = _wire->read();
            uint8_t d2 = _wire->read();
            uint8_t d3 = _wire->read();
            uint8_t rxChk = _wire->read();
            
            if (rxMode == modeId) {
                if (rxChk == (rxMode ^ d0 ^ d1 ^ d2 ^ d3)) {
                    uint32_t value = ((uint32_t)d0 << 24) | ((uint32_t)d1 << 16) | ((uint32_t)d2 << 8) | d3;
                    return value;
                }
            }
        }
        while (_wire->available()) _wire->read();
        delay(2);
    }
    return 0; // Timeout
}

// Utility conversions
uint32_t MKE_I2C_RFID::floatToUint32(float value) {
    uint32_t result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

float MKE_I2C_RFID::uint32ToFloat(uint32_t value) {
    float result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

// --------------------------------------------------------
// General Module Information
// --------------------------------------------------------
uint8_t MKE_I2C_RFID::getI2CAddress() {
    return requestData(MKE_RFID_MODE_GET_ADDRESS);
}

void MKE_I2C_RFID::setI2CAddress(uint8_t newAddress) {
    requestData(MKE_RFID_MODE_SET_ADDRESS, newAddress);
    _address = newAddress;
}

uint8_t MKE_I2C_RFID::getModuleID() {
    return requestData(MKE_RFID_MODE_GET_ID_MODULE);
}

uint32_t MKE_I2C_RFID::getFirmwareVersion() {
    return requestData(MKE_RFID_MODE_GET_FW_VERSION);
}

// --------------------------------------------------------
// Core RFID Functions
// --------------------------------------------------------
bool MKE_I2C_RFID::isCardPresent() {
    return requestData(MKE_RFID_MODE_IS_CARD_PRESENT) != 0;
}

uint32_t MKE_I2C_RFID::getUID() {
    return requestData(MKE_RFID_MODE_GET_UID);
}

uint8_t MKE_I2C_RFID::getUIDSize() {
    return requestData(MKE_RFID_MODE_GET_UID_SIZE);
}

uint8_t MKE_I2C_RFID::getCardType() {
    return requestData(MKE_RFID_MODE_GET_CARD_TYPE);
}

uint8_t MKE_I2C_RFID::getSAK() {
    return requestData(MKE_RFID_MODE_GET_SAK);
}

uint8_t MKE_I2C_RFID::getUIDFull(uint8_t *uidBuffer) {
    uint8_t size = getUIDSize();
    if (size == 0 || size > 10) return 0;
    
    sendCommand(MKE_RFID_MODE_GET_UID_FULL);
    
    uint8_t expectedBytes = size + 2;
    unsigned long startT = millis();
    while (millis() - startT < 100) {
        _wire->requestFrom(_address, expectedBytes);
        if (_wire->available() >= expectedBytes) {
            uint8_t rxMode = _wire->read();
            if (rxMode == MKE_RFID_MODE_GET_UID_FULL) {
                uint8_t chk = rxMode;
                for (int i = 0; i < size; i++) {
                    uidBuffer[i] = _wire->read();
                    chk ^= uidBuffer[i];
                }
                uint8_t rxChk = _wire->read();
                if (rxChk == chk) {
                    return size;
                }
            }
        }
        while (_wire->available()) _wire->read();
        delay(2);
    }
    return 0;
}

// --------------------------------------------------------
// MIFARE Classic Block Operations
// --------------------------------------------------------
bool MKE_I2C_RFID::isSectorTrailer(uint8_t blockAddr) {
    if (blockAddr < 128) {
        return ((blockAddr + 1) % 4 == 0); // MIFARE 1K & 4K (Sectors 0-31)
    }
    return ((blockAddr + 1) % 16 == 0); // MIFARE 4K (Sectors 32-39)
}

void MKE_I2C_RFID::setAuthKey(const uint8_t key[6]) {
    uint32_t high = ((uint32_t)key[0] << 24) | ((uint32_t)key[1] << 16) | ((uint32_t)key[2] << 8) | key[3];
    uint32_t low = ((uint32_t)key[4] << 8) | key[5];
    requestData(MKE_RFID_MODE_SET_KEY, high);
    requestData(MKE_RFID_MODE_SET_KEY_LOW, low);
}

uint8_t MKE_I2C_RFID::authenticateKeyA(uint8_t blockAddr) {
    requestData(MKE_RFID_MODE_AUTH_KEY_A, blockAddr);
    return getLastStatus();
}

uint8_t MKE_I2C_RFID::authenticateKeyB(uint8_t blockAddr) {
    requestData(MKE_RFID_MODE_AUTH_KEY_B, blockAddr);
    return getLastStatus();
}

uint8_t MKE_I2C_RFID::readBlock(uint8_t blockAddr, uint8_t *buffer) {
    sendCommand(MKE_RFID_MODE_READ_BLOCK, blockAddr);
    
    unsigned long startT = millis();
    while (millis() - startT < 100) {
        _wire->requestFrom(_address, (uint8_t)18);
        if (_wire->available() >= 18) {
            uint8_t rxMode = _wire->read();
            if (rxMode == MKE_RFID_MODE_READ_BLOCK) {
                uint8_t chk = rxMode;
                for (int i = 0; i < 16; i++) {
                    buffer[i] = _wire->read();
                    chk ^= buffer[i];
                }
                uint8_t rxChk = _wire->read();
                if (rxChk == chk) {
                    return getLastStatus();
                }
            }
        }
        while (_wire->available()) _wire->read();
        delay(2);
    }
    return 4; // MFRC522::STATUS_TIMEOUT
}

uint8_t MKE_I2C_RFID::writeBlock(uint8_t blockAddr, const uint8_t *buffer, bool allowSectorTrailerWrite) {
    if (!allowSectorTrailerWrite && isSectorTrailer(blockAddr)) {
        return 1; // STATUS_ERROR: Prevent accidental overwrite of Sector Trailer (Password/Access Bits)
    }
    
    uint32_t word0 = ((uint32_t)buffer[0] << 24) | ((uint32_t)buffer[1] << 16) | ((uint32_t)buffer[2] << 8) | buffer[3];
    uint32_t word1 = ((uint32_t)buffer[4] << 24) | ((uint32_t)buffer[5] << 16) | ((uint32_t)buffer[6] << 8) | buffer[7];
    uint32_t word2 = ((uint32_t)buffer[8] << 24) | ((uint32_t)buffer[9] << 16) | ((uint32_t)buffer[10] << 8) | buffer[11];
    uint32_t word3 = ((uint32_t)buffer[12] << 24) | ((uint32_t)buffer[13] << 16) | ((uint32_t)buffer[14] << 8) | buffer[15];
    
    requestData(MKE_RFID_MODE_WRITE_BLOCK_DATA_HIGH, word0);
    requestData(MKE_RFID_MODE_WRITE_BLOCK_DATA_MID1, word1);
    requestData(MKE_RFID_MODE_WRITE_BLOCK_DATA_MID2, word2);
    requestData(MKE_RFID_MODE_WRITE_BLOCK_DATA_LOW, word3);
    
    requestData(MKE_RFID_MODE_WRITE_BLOCK_EXECUTE, blockAddr);
    return getLastStatus();
}

int8_t MKE_I2C_RFID::setUID(uint8_t* newUID, uint8_t uidSize) {
    if (uidSize == 0 || uidSize > 10) return 1; // STATUS_ERROR
    
    // Clear and fill a local 16-byte buffer
    uint8_t tempBuf[16] = {0};
    memcpy(tempBuf, newUID, uidSize);
    
    // Chunk the data into 32-bit words
    uint32_t word0 = ((uint32_t)tempBuf[0] << 24) | ((uint32_t)tempBuf[1] << 16) | ((uint32_t)tempBuf[2] << 8) | tempBuf[3];
    uint32_t word1 = ((uint32_t)tempBuf[4] << 24) | ((uint32_t)tempBuf[5] << 16) | ((uint32_t)tempBuf[6] << 8) | tempBuf[7];
    uint32_t word2 = ((uint32_t)tempBuf[8] << 24) | ((uint32_t)tempBuf[9] << 16) | ((uint32_t)tempBuf[10] << 8) | tempBuf[11];
    uint32_t word3 = ((uint32_t)tempBuf[12] << 24) | ((uint32_t)tempBuf[13] << 16) | ((uint32_t)tempBuf[14] << 8) | tempBuf[15];
    
    requestData(MKE_RFID_MODE_WRITE_BLOCK_DATA_HIGH, word0);
    requestData(MKE_RFID_MODE_WRITE_BLOCK_DATA_MID1, word1);
    requestData(MKE_RFID_MODE_WRITE_BLOCK_DATA_MID2, word2);
    requestData(MKE_RFID_MODE_WRITE_BLOCK_DATA_LOW, word3);
    
    // Execute Set UID Mode
    requestData(MKE_RFID_MODE_SET_UID_EXECUTE, uidSize);
    
    // According to MKE_I2C_product_Rules.md: Always append a delay(50); after any SET command
    delay(50);
    
    return getLastStatus();
}

uint8_t MKE_I2C_RFID::getLastStatus() {
    return requestData(MKE_RFID_MODE_GET_LAST_STATUS);
}

// --------------------------------------------------------
// MIFARE Classic Value Block Operations
// --------------------------------------------------------
uint8_t MKE_I2C_RFID::setValue(uint8_t blockAddr, int32_t value, bool allowSectorTrailerWrite) {
    if (!allowSectorTrailerWrite && isSectorTrailer(blockAddr)) {
        return 1; // STATUS_ERROR: Prevent accidental overwrite of Sector Trailer
    }
    requestData(MKE_RFID_MODE_SET_TARGET_BLOCK, blockAddr);
    requestData(MKE_RFID_MODE_SET_VALUE, (uint32_t)value);
    return getLastStatus();
}

uint8_t MKE_I2C_RFID::getValue(uint8_t blockAddr, int32_t *value) {
    requestData(MKE_RFID_MODE_SET_TARGET_BLOCK, blockAddr);
    *value = (int32_t)requestData(MKE_RFID_MODE_GET_VALUE, blockAddr);
    return getLastStatus();
}

uint8_t MKE_I2C_RFID::incrementValue(uint8_t blockAddr, int32_t delta, bool allowSectorTrailerWrite) {
    if (!allowSectorTrailerWrite && isSectorTrailer(blockAddr)) {
        return 1;
    }
    requestData(MKE_RFID_MODE_SET_TARGET_BLOCK, blockAddr);
    requestData(MKE_RFID_MODE_INCREMENT, (uint32_t)delta);
    return getLastStatus();
}

uint8_t MKE_I2C_RFID::decrementValue(uint8_t blockAddr, int32_t delta, bool allowSectorTrailerWrite) {
    if (!allowSectorTrailerWrite && isSectorTrailer(blockAddr)) {
        return 1;
    }
    requestData(MKE_RFID_MODE_SET_TARGET_BLOCK, blockAddr);
    requestData(MKE_RFID_MODE_DECREMENT, (uint32_t)delta);
    return getLastStatus();
}

// --------------------------------------------------------
// Module Control
// --------------------------------------------------------
void MKE_I2C_RFID::haltCard() {
    requestData(MKE_RFID_MODE_HALT_CARD);
}

void MKE_I2C_RFID::stopCrypto() {
    requestData(MKE_RFID_MODE_STOP_CRYPTO);
}

void MKE_I2C_RFID::setAntennaGain(uint8_t gain) {
    requestData(MKE_RFID_MODE_SET_ANTENNA_GAIN, gain);
}

uint8_t MKE_I2C_RFID::getAntennaGain() {
    return requestData(MKE_RFID_MODE_GET_ANTENNA_GAIN);
}

uint8_t MKE_I2C_RFID::getRC522FirmwareVersion() {
    return requestData(MKE_RFID_MODE_GET_FW_RC522);
}

bool MKE_I2C_RFID::performSelfTest() {
    requestData(MKE_RFID_MODE_SELF_TEST);
    return getLastStatus() == 0;
}

// ==============================================================================
// ADVANCED CLASS
// ==============================================================================

uint16_t MKE_I2C_RFID_Advanced::getProductCode() {
    return requestData(MKE_RFID_MODE_GET_PRODUCT_CODE);
}

uint32_t MKE_I2C_RFID_Advanced::getLastUnixtimeTest() {
    return requestData(MKE_RFID_MODE_GET_LAST_UNIXTIME_TEST);
}

void MKE_I2C_RFID_Advanced::unlockAdminMode(uint32_t password) {
    requestData(MKE_RFID_MODE_UNLOCK_ADMIN, password);
}

void MKE_I2C_RFID_Advanced::factoryReset() {
    requestData(MKE_RFID_MODE_FACTORY_RESET);
}

