#ifndef MKE_I2C_LOADCELL_H
#define MKE_I2C_LOADCELL_H

#include <Arduino.h>
#include <Wire.h>

#define MKE_I2C_LOADCELL_DEFAULT_ADDR 10

// Mode IDs
#define MKE_LOADCELL_MODE_GET_ADDRESS         10
#define MKE_LOADCELL_MODE_GET_RAW_VALUE       50
#define MKE_LOADCELL_MODE_TARE                51
#define MKE_LOADCELL_MODE_GET_GRAM            52
#define MKE_LOADCELL_MODE_CALIBRATE           53
#define MKE_LOADCELL_MODE_GET_SCALE           54
#define MKE_LOADCELL_MODE_SET_SCALE           55

class MKE_I2C_Loadcell {
public:
    MKE_I2C_Loadcell(TwoWire *wire = &Wire);
    
    bool begin(uint8_t address = MKE_I2C_LOADCELL_DEFAULT_ADDR);
    
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
    
    // Calibration Functions
    void calibrate(float knownWeight);
    float getScale();
    void setScale(float scale);
    
private:
    TwoWire *_wire;
    uint8_t _address;
    float _unitWeightGram;

    uint32_t requestData(uint8_t modeId, uint32_t payload = 0);
    uint32_t floatToUint32(float value);
    float uint32ToFloat(uint32_t value);
};

#endif
