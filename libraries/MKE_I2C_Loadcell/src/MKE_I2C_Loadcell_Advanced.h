#ifndef MKE_I2C_LOADCELL_ADVANCED_H
#define MKE_I2C_LOADCELL_ADVANCED_H

#include "MKE_I2C_Loadcell.h"

// Advanced Module Info Mode IDs (Factory / Calibration)
#define MKE_LOADCELL_MODE_SET_ID_MODULE           3
#define MKE_LOADCELL_MODE_SET_FW_VERSION          5
#define MKE_LOADCELL_MODE_GET_PRODUCT_CODE        6
#define MKE_LOADCELL_MODE_SET_PRODUCT_CODE        7
#define MKE_LOADCELL_MODE_SET_LAST_UNIXTIME_TEST  8
#define MKE_LOADCELL_MODE_GET_LAST_UNIXTIME_TEST  9
#define MKE_LOADCELL_MODE_GET_ZERO_TRACKING   56
#define MKE_LOADCELL_MODE_SET_ZERO_TRACKING   57
#define MKE_LOADCELL_MODE_GET_KALMAN_MEA      60
#define MKE_LOADCELL_MODE_SET_KALMAN_MEA      61
#define MKE_LOADCELL_MODE_GET_KALMAN_EST      62
#define MKE_LOADCELL_MODE_SET_KALMAN_EST      63
#define MKE_LOADCELL_MODE_GET_KALMAN_Q        64
#define MKE_LOADCELL_MODE_SET_KALMAN_Q        65
#define MKE_LOADCELL_MODE_GET_EEPROM_SAVE_DELAY 66
#define MKE_LOADCELL_MODE_SET_EEPROM_SAVE_DELAY 67
#define MKE_LOADCELL_MODE_GET_LOADCELL_TYPE   68
#define MKE_LOADCELL_MODE_SET_LOADCELL_TYPE   69
#define MKE_LOADCELL_MODE_UNLOCK_ADMIN        200
#define MKE_LOADCELL_MODE_GET_ADMIN_MODE      201

enum MKE_Loadcell_Type {
    MKE_LOADCELL_CUSTOM = 0,
    MKE_LOADCELL_300G = 1,
    MKE_LOADCELL_1KG = 2,
    MKE_LOADCELL_5KG = 3,
    MKE_LOADCELL_10KG = 4,
    MKE_LOADCELL_20KG = 5
};

class MKE_I2C_Loadcell_Advanced : public MKE_I2C_Loadcell {
public:
    MKE_I2C_Loadcell_Advanced(TwoWire *wire = &Wire) : MKE_I2C_Loadcell(wire) {}

    void setLoadcellType(uint8_t type);
    uint8_t getLoadcellType();

    void setKalmanParameters(float mea_e, float est_e, float q);
    float getKalmanMea();
    float getKalmanEst();
    float getKalmanQ();
    
    uint16_t getProductCode();
    uint32_t getLastUnixtimeTest();
    
    void setEepromSaveDelay(uint32_t ms);
    uint32_t getEepromSaveDelay();
    
    void unlockAdminMode(uint32_t password = 0x12345678);
    void lockAdminMode();
    bool isAdminMode();
    
    void setModuleID(uint8_t id);
    void setFirmwareVersion(uint32_t version);
    void setProductCode(uint16_t code);
    void setLastUnixtimeTest(uint32_t timestamp);
};

#endif
