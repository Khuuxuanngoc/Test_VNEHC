#ifndef MKE_I2C_LOADCELL_H
#define MKE_I2C_LOADCELL_H

#include <Arduino.h>
#include <Wire.h>

#define MKE_I2C_LOADCELL_DEFAULT_ADDR 10

// General Module Info Mode IDs
#define MKE_LOADCELL_MODE_GET_ADDRESS             10
#define MKE_LOADCELL_MODE_SET_ADDRESS             1
#define MKE_LOADCELL_MODE_GET_ID_MODULE           2
#define MKE_LOADCELL_MODE_GET_FW_VERSION          4

#define MKE_LOADCELL_MODE_GET_RAW_VALUE       50
#define MKE_LOADCELL_MODE_TARE                51
#define MKE_LOADCELL_MODE_GET_GRAM            52
#define MKE_LOADCELL_MODE_CALIBRATE           53
#define MKE_LOADCELL_MODE_GET_SCALE           54
#define MKE_LOADCELL_MODE_SET_SCALE           55
#define MKE_LOADCELL_MODE_GET_FILTER_LEVEL    58
#define MKE_LOADCELL_MODE_SET_FILTER_LEVEL    59

class MKE_I2C_Loadcell {
public:
    MKE_I2C_Loadcell(TwoWire *wire = &Wire);
    
    bool begin(uint8_t address = MKE_I2C_LOADCELL_DEFAULT_ADDR);
    
    // General Module Information
    uint8_t getI2CAddress();
    void setI2CAddress(uint8_t newAddress);
    
    uint8_t getModuleID();
    uint32_t getFirmwareVersion();
    
    // Core Functions
    void tare();
    float getGram();
    int32_t getRawValue();
    
    // Converter Functions
    float getKilogram();
    float getOunce();
    float getPound();
    float getNewton();
    float getCarat();
    
    // Counting Functions (PCS)
    void setPieceWeight(float unitWeightGram);
    int32_t getPCS();
    void autoRefinePieceWeight();
    
    // Calibration Functions
    void calibrate(float knownWeight);
    float getScale();
    void setScale(float scale);
    
    void setFilterLevel(uint8_t level); // 0: Raw, 1: Fast, 2: Medium, 3: Slow
    uint8_t getFilterLevel();
    
protected:
    TwoWire *_wire;
    uint8_t _address;
    float _unitWeightGram;

    uint32_t requestData(uint8_t modeId, uint32_t payload = 0);
    uint32_t floatToUint32(float value);
    float uint32ToFloat(uint32_t value);
};

#endif
