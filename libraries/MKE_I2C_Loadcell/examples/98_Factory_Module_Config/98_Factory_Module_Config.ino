/*
 * 98_Factory_Module_Config
 * 
 * FACTORY CONFIGURATION TOOL
 * 
 * This example is designed for manufacturers to program system information
 * into the PY32 module via I2C.
 * Includes:
 *  - Changing I2C Address (Useful for resolving address conflicts)
 *  - Updating Firmware Version, Product Code
 *  - Saving successful QC Test timestamp
 *  
 * NOTE: These functions are protected by Admin Mode and require
 * unlockAdminMode() to write data to the PY32's EEPROM.
 */

#include <Wire.h>
#include "MKE_I2C_Loadcell_Advanced.h"

// Using the Advanced class for factory operations
MKE_I2C_Loadcell_Advanced scale;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  while (!Serial);

  Serial.println(F("\n============================================="));
  Serial.println(F("     FACTORY MODULE CONFIGURATION TOOL       "));
  Serial.println(F("============================================="));

  // Initialize at the default I2C address
  if (!scale.begin()) {
    Serial.println(F("Error: I2C Loadcell Module not found!"));
    while (1) delay(100);
  }

  Serial.println(F("\n[1] CURRENT info before update:"));
  Serial.print(F("- I2C Address      : 0x")); Serial.println(scale.getI2CAddress(), HEX);
  Serial.print(F("- Module ID        : ")); Serial.println(scale.getModuleID());
  Serial.print(F("- Firmware Version : ")); Serial.println(scale.getFirmwareVersion());
  
  // -------------------------------------------------------------
  // BEGIN UPDATE PROCESS (ADMIN ONLY)
  // -------------------------------------------------------------
  
  Serial.println(F("\n[2] Unlocking Admin Mode on PY32..."));
  scale.unlockAdminMode(0x12345678); 
  
  // Example 1: Update Firmware Version to 20250101 (Jan 1, 2025)
  Serial.println(F("- Updating Firmware Version -> 20250101"));
  scale.setFirmwareVersion(20250101);
  
  // Example 2: Update Product Code to 9999
  Serial.println(F("- Updating Product Code -> 9999"));
  scale.setProductCode(9999);
  
  // Example 3: Change I2C Address (Uncomment to use)
  // NOTE: After changing the address, you must power-cycle the module
  // or reset the ESP32, and update the address in scale.begin(type, new_address)
  // uint8_t new_address = 0x30;
  // Serial.print(F("- Changing I2C Address to -> 0x")); Serial.println(new_address, HEX);
  // scale.setI2CAddress(new_address);
  
  // LOCK ADMIN MODE WHEN DONE
  Serial.println(F("-> Locking Admin Mode!"));
  scale.lockAdminMode();

  // -------------------------------------------------------------
  // VERIFY UPDATES
  // -------------------------------------------------------------
  Serial.println(F("\n[3] Info AFTER update:"));
  Serial.print(F("- Firmware Version : ")); Serial.println(scale.getFirmwareVersion());
  Serial.print(F("- Product Code     : ")); Serial.println(scale.getProductCode());
  
  Serial.println(F("\nDONE!"));
}

void loop() {
  delay(1000);
}
