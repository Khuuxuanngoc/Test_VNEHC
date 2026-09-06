/*
  Example 02: Tare and Calibrate
  
  Description:
  This guide shows how to tare (zero the scale) and calibrate the Loadcell 
  using a known reference weight. The Scale Factor will be automatically 
  saved to the I2C module's EEPROM.

  Notes on Loadcell Types:
  - This library supports all load cell capacities (1kg, 5kg, 10kg, 20kg...).
  - The reference weight used for calibration SHOULD BE 10% - 50% of the loadcell's maximum capacity for the best accuracy.
*/

#include <Wire.h>
#include "MKE_I2C_Loadcell.h"

MKE_I2C_Loadcell scale;

// Customize your reference weight (Unit: Grams)
// RECOMMENDED: Use a weight that is 10% - 50% of the Loadcell's max capacity.
// Example: 20kg Loadcell -> Use a 2000g (2kg) reference weight
const float REFERENCE_WEIGHT_GRAM = 500.0; 

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!scale.begin()) {
    Serial.println(F("I2C Loadcell not found. Please check connections!"));
    while (1) delay(100);
  }
  
  Serial.println(F("I2C Loadcell connected successfully!"));
  Serial.println(F("===================================="));
  Serial.print(F("1. Scale Factor (Float): "));
  Serial.println(scale.getScale(), 9); // Print with high precision
  
  // Cast float to uint32_t (4 raw bytes) to print HEX code
  float currentScale = scale.getScale();
  uint32_t hexScale = *((uint32_t*)&currentScale);
  Serial.print(F("2. Scale Factor (HEX)  : 0x"));
  Serial.println(hexScale, HEX);
  Serial.println(F("===================================="));
  
  Serial.println(F("\n--- INSTRUCTIONS ---"));
  Serial.println(F("1. Remove all items from the scale, send 't' to Tare (Zero)"));
  Serial.println(F("2. Place the reference weight (e.g., 500g) on the scale, send 'c' to Calibrate"));
  Serial.println(F("-----------------\n"));
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    
    // TARE (ZERO)
    if (cmd == 't' || cmd == 'T') {
      Serial.println(F("\n[CMD] Taring..."));
      scale.tare();
      Serial.println(F("-> Tare successful. Weight reset to 0."));
    } 
    
    // CALIBRATE
    else if (cmd == 'c' || cmd == 'C') {
      Serial.print(F("\n[CMD] Calibrating with reference weight: "));
      Serial.print(REFERENCE_WEIGHT_GRAM);
      Serial.println(F("g ..."));
      
      // Send calibration command to I2C module
      scale.calibrate(REFERENCE_WEIGHT_GRAM);
      
      delay(500); // Wait a moment for the module to process and save to EEPROM
      
      Serial.print(F("-> Calibration successful! New Scale Factor: "));
      Serial.println(scale.getScale(), 6);
    }
  }

  // Print weight continuously
  float weight = scale.getGram();
  Serial.print(F("Current Weight: "));
  Serial.print(weight, 1);
  Serial.println(F(" g"));
  
  delay(300);
}
