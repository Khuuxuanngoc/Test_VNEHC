#include "MKE_I2C_Loadcell.h"

// Struct gói tin 6 bytes
typedef struct __attribute__((packed)) {
  uint8_t addressId;
  uint8_t modeId;
  uint8_t value[4];
} I2C_Packet;

MKE_I2C_Loadcell::MKE_I2C_Loadcell(TwoWire *wire) {
    _wire = wire;
    _address = MKE_I2C_LOADCELL_DEFAULT_ADDR;
    _unitWeightGram = 1.0;
}

bool MKE_I2C_Loadcell::begin(uint8_t address) {
    _address = address;
    
    // Thử gửi lệnh lấy địa chỉ để kiểm tra kết nối
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_ADDRESS);
    if (res == 0xFFFFFFFF) {
        return false;
    }
    
    return true;
}

uint8_t MKE_I2C_Loadcell::getI2CAddress() {
    return (uint8_t)(requestData(MKE_LOADCELL_MODE_GET_ADDRESS) & 0xFF);
}

uint8_t MKE_I2C_Loadcell::getModuleID() {
    return (uint8_t)(requestData(MKE_LOADCELL_MODE_GET_ID_MODULE) & 0xFF);
}

uint32_t MKE_I2C_Loadcell::getFirmwareVersion() {
    return requestData(MKE_LOADCELL_MODE_GET_FW_VERSION);
}

void MKE_I2C_Loadcell::tare() {
    requestData(MKE_LOADCELL_MODE_TARE);
}

float MKE_I2C_Loadcell::getGram() {
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_GRAM);
    return uint32ToFloat(res);
}

int32_t MKE_I2C_Loadcell::getRawValue() {
    return (int32_t)requestData(MKE_LOADCELL_MODE_GET_RAW_VALUE);
}

float MKE_I2C_Loadcell::getKilogram() {
    return getGram() / 1000.0f;
}

float MKE_I2C_Loadcell::getOunce() {
    return getGram() / 28.3495231f;
}

float MKE_I2C_Loadcell::getPound() {
    return getGram() / 453.59237f;
}

float MKE_I2C_Loadcell::getNewton() {
    return getGram() / 101.971621f;
}

float MKE_I2C_Loadcell::getCarat() {
    return getGram() / 0.2f;
}

void MKE_I2C_Loadcell::setPieceWeight(float unitWeightGram) {
    if (unitWeightGram > 0) {
        _unitWeightGram = unitWeightGram;
    }
}

int32_t MKE_I2C_Loadcell::getPCS() {
    float gram = getGram();
    if (_unitWeightGram > 0.0) {
        return (int32_t)((gram / _unitWeightGram) + 0.5); // Add 0.5 for rounding
    }
    return 0;
}

void MKE_I2C_Loadcell::autoRefinePieceWeight() {
    int32_t currentPCS = getPCS();
    if (currentPCS > 0) {
        float currentTotalWeight = getGram();
        _unitWeightGram = currentTotalWeight / (float)currentPCS;
    }
}

void MKE_I2C_Loadcell::calibrate(float knownWeight) {
    requestData(MKE_LOADCELL_MODE_CALIBRATE, floatToUint32(knownWeight));
}

float MKE_I2C_Loadcell::getScale() {
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_SCALE);
    return uint32ToFloat(res);
}

void MKE_I2C_Loadcell::setScale(float scale) {
    requestData(MKE_LOADCELL_MODE_SET_SCALE, floatToUint32(scale));
}

void MKE_I2C_Loadcell::setFilterLevel(uint8_t level) {
    requestData(MKE_LOADCELL_MODE_SET_FILTER_LEVEL, (uint32_t)level);
}

uint8_t MKE_I2C_Loadcell::getFilterLevel() {
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_FILTER_LEVEL);
    return (uint8_t)(res & 0xFF);
}

void MKE_I2C_Loadcell::setI2CAddress(uint8_t newAddress) {
    requestData(MKE_LOADCELL_MODE_SET_ADDRESS, (uint32_t)newAddress);
    _address = newAddress; // Cập nhật địa chỉ mới cho object ESP32
    delay(50); // Chờ PY32 khởi động lại I2C
}

uint32_t MKE_I2C_Loadcell::floatToUint32(float value) {
    uint32_t result;
    memcpy(&result, &value, sizeof(float));
    return result;
}

float MKE_I2C_Loadcell::uint32ToFloat(uint32_t value) {
    float result;
    memcpy(&result, &value, sizeof(float));
    return result;
}

uint32_t MKE_I2C_Loadcell::requestData(uint8_t modeId, uint32_t payload) {
    I2C_Packet pkt;
    pkt.addressId = _address;
    pkt.modeId = modeId;
    
    pkt.value[0] = (uint8_t)(payload >> 24);
    pkt.value[1] = (uint8_t)(payload >> 16);
    pkt.value[2] = (uint8_t)(payload >> 8);
    pkt.value[3] = (uint8_t)(payload & 0xFF);

    _wire->beginTransmission(_address);
    _wire->write((uint8_t*)&pkt, sizeof(I2C_Packet));
    if (_wire->endTransmission() != 0) {
        return 0xFFFFFFFF; 
    }

    // Đợi slave (PY32) xử lý gói tin I2C trong hàm loop() và cập nhật dataToReply
    delay(5);

    // Yêu cầu phản hồi 4 bytes
    _wire->requestFrom((uint16_t)_address, (uint8_t)4, (uint8_t)true);
    uint8_t buf[4];
    int i = 0;
    while (_wire->available() && i < 4) {
        buf[i++] = _wire->read();
    }

    if (i == 4) {
        return ((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16) |
               ((uint32_t)buf[2] << 8) | (uint32_t)buf[3];
    }
    
    return 0xFFFFFFFF;
}
