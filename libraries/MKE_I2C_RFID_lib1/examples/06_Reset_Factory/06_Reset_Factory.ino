#include <Wire.h>
#include "MKE_I2C_RFID.h"

MKE_I2C_RFID_Advanced rfidAdv;

// Function to scan and find the first responding I2C device
uint8_t scanI2C() {
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      return addr;
    }
  }
  return 0;
}

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    Serial.println(F("========================================"));
    Serial.println(F("   MKE I2C RFID - Factory Reset"));
    Serial.println(F("========================================"));
    Serial.println(F("WARNING: Ensure ONLY ONE module is connected"));
    Serial.println(F("to the I2C bus during this process!"));
    Serial.println(F("========================================"));
    
    uint8_t foundAddr = scanI2C();
    if (foundAddr == 0) {
        Serial.println(F("No I2C devices found! Check wiring."));
        while (1) delay(10);
    }
    
    Serial.print(F("Found I2C device at address: 0x"));
    Serial.println(foundAddr, HEX);
    
    if (!rfidAdv.begin(foundAddr)) {
        Serial.println(F("Device found, but it does not respond correctly."));
        while (1) delay(10);
    }
    
    Serial.println(F("MKE I2C RFID Initialized successfully!"));
    Serial.print(F("Current I2C Address is: 0x"));
    Serial.println(rfidAdv.getI2CAddress(), HEX);
    
    Serial.println(F(""));
    Serial.println(F("WARNING: This will reset the module to Factory Defaults!"));
    Serial.println(F("- I2C Address will be reset to 0x29"));
    Serial.println(F("- Module ID and configurations will be reset to default"));
    Serial.println(F("Type 'YES' and press ENTER to confirm..."));
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        input.toUpperCase();
        
        if (input == "YES") {
            Serial.println(F("\nExecuting Factory Reset..."));
            
            // 1. Unlock Admin Mode
            Serial.println(F("Unlocking Admin Mode..."));
            rfidAdv.unlockAdminMode(); // Default password 0xA5A5A5A5
            delay(50); // Delay after SET
            
            // 2. Execute Factory Reset Command
            Serial.println(F("Sending Factory Reset Command..."));
            rfidAdv.factoryReset();
            delay(100); // Allow on-board MCU time to save EEPROM and restart I2C
            
            Serial.println(F(""));
            Serial.println(F("Factory Reset Completed!"));
            Serial.println(F("Please restart the Arduino or cycle power to the module."));
            
            while(1) delay(100);
        } else {
            Serial.println(F("Reset cancelled. Type 'YES' if you change your mind."));
        }
    }
}
