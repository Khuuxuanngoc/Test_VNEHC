#include <Wire.h>
#include "MKE_I2C_RFID.h"

MKE_I2C_RFID_Advanced rfid;

uint8_t currentAddress = 0;

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
    Serial.println(F("   MKE I2C RFID - Change I2C Address"));
    Serial.println(F("========================================"));
    Serial.println(F("WARNING: Ensure ONLY ONE module is connected"));
    Serial.println(F("to the I2C bus during this process!"));
    Serial.println(F("========================================"));
    
    uint8_t foundAddr = scanI2C();
    if (foundAddr == 0) {
        Serial.println(F("No I2C devices found! Check wiring."));
        while (1) delay(10);
    }
    
    currentAddress = foundAddr;
    Serial.print(F("Found I2C device at address: 0x"));
    Serial.println(currentAddress, HEX);
    
    if (!rfid.begin(currentAddress)) {
        Serial.println(F("Device found, but it does not respond correctly."));
        while (1) delay(10);
    }
    
    Serial.println(F("MKE I2C RFID Initialized successfully!"));
    Serial.print(F("Current I2C Address is: 0x"));
    Serial.println(rfid.getI2CAddress(), HEX);
    
    Serial.println(F(""));
    Serial.println(F("Enter a new I2C Address (in HEX, from 08 to 77) and press ENTER:"));
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        
        if (input.length() > 0) {
            long newAddr = strtol(input.c_str(), NULL, 16);
            
            if (newAddr >= 0x08 && newAddr <= 0x77) {
                Serial.println(F("Unlocking Admin Mode..."));
                rfid.unlockAdminMode();
                delay(50);
                
                Serial.print(F("Setting new I2C address to: 0x"));
                Serial.println(newAddr, HEX);
                
                rfid.setI2CAddress((uint8_t)newAddr);
                delay(100); // Required delay after SET command
                
                Serial.println(F("Address changed successfully!"));
                Serial.println(F("Please upload a new sketch with the new address, or restart this board to scan again."));
                
                while(1) delay(100); // Stop here
            } else {
                Serial.println(F("Invalid address! Please enter a value between 08 and 77 (HEX)."));
            }
        }
    }
}
