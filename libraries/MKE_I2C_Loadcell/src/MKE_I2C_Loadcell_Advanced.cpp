#include "MKE_I2C_Loadcell_Advanced.h"

void MKE_I2C_Loadcell_Advanced::setLoadcellType(uint8_t type) {
    requestData(MKE_LOADCELL_MODE_SET_LOADCELL_TYPE, (uint32_t)type);
    delay(10);
}

uint8_t MKE_I2C_Loadcell_Advanced::getLoadcellType() {
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_LOADCELL_TYPE);
    return (uint8_t)(res & 0xFF);
}

void MKE_I2C_Loadcell_Advanced::setKalmanParameters(float mea_e, float est_e, float q) {
    requestData(MKE_LOADCELL_MODE_SET_KALMAN_MEA, floatToUint32(mea_e));
    delay(10);
    requestData(MKE_LOADCELL_MODE_SET_KALMAN_EST, floatToUint32(est_e));
    delay(10);
    requestData(MKE_LOADCELL_MODE_SET_KALMAN_Q, floatToUint32(q));
}

float MKE_I2C_Loadcell_Advanced::getKalmanMea() {
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_KALMAN_MEA);
    return uint32ToFloat(res);
}

float MKE_I2C_Loadcell_Advanced::getKalmanEst() {
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_KALMAN_EST);
    return uint32ToFloat(res);
}

float MKE_I2C_Loadcell_Advanced::getKalmanQ() {
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_KALMAN_Q);
    return uint32ToFloat(res);
}

uint16_t MKE_I2C_Loadcell_Advanced::getProductCode() {
    return (uint16_t)(requestData(MKE_LOADCELL_MODE_GET_PRODUCT_CODE) & 0xFFFF);
}

uint32_t MKE_I2C_Loadcell_Advanced::getLastUnixtimeTest() {
    return requestData(MKE_LOADCELL_MODE_GET_LAST_UNIXTIME_TEST);
}

void MKE_I2C_Loadcell_Advanced::setEepromSaveDelay(uint32_t ms) {
    requestData(MKE_LOADCELL_MODE_SET_EEPROM_SAVE_DELAY, ms);
}

uint32_t MKE_I2C_Loadcell_Advanced::getEepromSaveDelay() {
    return requestData(MKE_LOADCELL_MODE_GET_EEPROM_SAVE_DELAY);
}

void MKE_I2C_Loadcell_Advanced::unlockAdminMode(uint32_t password) {
    requestData(MKE_LOADCELL_MODE_UNLOCK_ADMIN, password);
    delay(50);
}

void MKE_I2C_Loadcell_Advanced::lockAdminMode() {
    requestData(MKE_LOADCELL_MODE_UNLOCK_ADMIN, 0);
    delay(50);
}

bool MKE_I2C_Loadcell_Advanced::isAdminMode() {
    uint32_t res = requestData(MKE_LOADCELL_MODE_GET_ADMIN_MODE);
    return (res & 0xFF) == 1;
}

void MKE_I2C_Loadcell_Advanced::setModuleID(uint8_t id) {
    requestData(MKE_LOADCELL_MODE_SET_ID_MODULE, (uint32_t)id);
}

void MKE_I2C_Loadcell_Advanced::setFirmwareVersion(uint32_t version) {
    requestData(MKE_LOADCELL_MODE_SET_FW_VERSION, version);
}

void MKE_I2C_Loadcell_Advanced::setProductCode(uint16_t code) {
    requestData(MKE_LOADCELL_MODE_SET_PRODUCT_CODE, (uint32_t)code);
}

void MKE_I2C_Loadcell_Advanced::setLastUnixtimeTest(uint32_t timestamp) {
    requestData(MKE_LOADCELL_MODE_SET_LAST_UNIXTIME_TEST, timestamp);
}
