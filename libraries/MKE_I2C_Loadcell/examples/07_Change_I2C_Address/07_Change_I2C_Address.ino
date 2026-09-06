/*
 * 07_Change_I2C_Address
 * 
 * This example shows how to change the I2C address of the Loadcell Module.
 * This is highly useful when you need to connect multiple sensors on the 
 * same I2C bus and they have conflicting default addresses (10).
 * 
 * IMPORTANT WARNING:
 * Please connect ONLY ONE I2C module to the Arduino when running this sketch.
 * This prevents accidentally changing the address of other I2C devices.
 */

#include "MKE_I2C_Loadcell.h"

MKE_I2C_Loadcell scale;

// The new I2C address you want to set (e.g., 0x30)
// Valid I2C addresses are usually from 0x08 to 0x77
const uint8_t NEW_I2C_ADDRESS = 0x30;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  while (!Serial);

  Serial.println(F("\n============================================="));
  Serial.println(F("      I2C ADDRESS CONFIGURATION TOOL         "));
  Serial.println(F("============================================="));
  
  Serial.println(F("\n[1] Scanning I2C bus (1 to 127) for the Loadcell Module..."));
  
  uint8_t found_address = 0;
  
  for (uint8_t addr = 1; addr < 127; addr++) {
    // scale.begin() returns true    // Try to initialize scale at current loop address
    if (scale.begin(addr)) {
      found_address = addr;
      Serial.print(F("Found I2C Loadcell at address 0x"));
      break;
    }
  }

  if (found_address == 0) {
    Serial.println(F("-> ERROR: No Loadcell Module found! Please check your wiring."));
    while(1) delay(100);
  }
  
  Serial.println(F("-> Loadcell Module found!"));
  Serial.print(F("-> Current I2C Address: 0x"));
  Serial.println(found_address, HEX);

  // Begin address change process
  Serial.println(F("\n[2] Changing I2C address..."));
  Serial.print(F("-> Updating to new address: 0x"));
  Serial.println(NEW_I2C_ADDRESS, HEX);
  
  // Call setI2CAddress
  scale.setI2CAddress(NEW_I2C_ADDRESS);
  
  Serial.println(F("\n[3] Address changed successfully!"));
  Serial.println(F("-> The module has automatically rebooted with the new I2C address."));
  
  // Verify connection with the new address
  if (scale.begin(NEW_I2C_ADDRESS)) {
    Serial.println(F("-> Verification with new address: SUCCESS!"));
    Serial.print(F("-> Please use address 0x"));
    Serial.print(NEW_I2C_ADDRESS, HEX);
    Serial.println(F(" in your future projects."));
  } else {
    Serial.println(F("-> Verification with new address: FAILED! (Please restart the module)"));
  }
}

void loop() {
  delay(1000);
}
