/*
 * 06_Module_Information
 * 
 * This example shows how to read the system information (Module Info)
 * stored in the I2C Loadcell module.
 * This includes: I2C Address, Firmware Version, Product Code, etc.
 */

#include "MKE_I2C_Loadcell.h"

MKE_I2C_Loadcell scale;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  while (!Serial);

  Serial.println(F("\n--- INITIALIZING MODULE ---"));
  
  if (!scale.begin()) {
    Serial.println(F("Error: I2C Loadcell Module not found!"));
    while(1) delay(100);
  }

  Serial.println(F("======================================"));
  Serial.println(F("       I2C MODULE INFORMATION         "));
  Serial.println(F("======================================"));
  
  Serial.print(F("- Current I2C Address  : 0x"));
  Serial.println(scale.getI2CAddress(), HEX);
  
  Serial.print(F("- Module ID            : "));
  Serial.println(scale.getModuleID());
  
  Serial.print(F("- Firmware Version     : "));
  Serial.println(scale.getFirmwareVersion());
  
  Serial.println(F("======================================"));
}

void loop() {
  // Chương trình chỉ chạy 1 lần trong setup()
  delay(1000);
}
