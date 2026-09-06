/*
 * 99_Factory_Calibration
 * Designed for manufacturers (Factory) to calibrate various Loadcell capacities 
 * (300g, 1kg, 5kg, 10kg, 20kg) and save them to the I2C Module's EEPROM.
 * 
 * Instructions:
 * 1. Ensure the Loadcell module is connected to the Arduino via I2C.
 * 2. Open the Serial Monitor with a baudrate of 115200.
 * 3. Follow the on-screen instructions to select the Loadcell type
 *    and input the reference weight to automatically save the calibration profile.
 */

#include <Wire.h>
#include "MKE_I2C_Loadcell_Advanced.h"

MKE_I2C_Loadcell_Advanced scale;

uint8_t current_type = MKE_LOADCELL_CUSTOM;

void printMenu() {
  Serial.println(F("\n============================================="));
  Serial.println(F("Select the Loadcell capacity you are calibrating:"));
  Serial.println(F("1: 300g"));
  Serial.println(F("2: 1kg"));
  Serial.println(F("3: 5kg"));
  Serial.println(F("4: 10kg"));
  Serial.println(F("5: 20kg"));
  Serial.println(F("C: Display current Raw value"));
  Serial.println(F("T: Tare (Zero)"));
  Serial.println(F("V: View all saved Scale Factors"));
  Serial.print(F("Enter your choice: "));
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  while(!Serial); // Wait for Serial to initialize

  Serial.println(F("\n============================================="));
  Serial.println(F("FACTORY CALIBRATION PROGRAM"));
  Serial.println(F("============================================="));

  // Initialize in // Khởi tạo I2C Loadcell
  if (!scale.begin()) {
    Serial.println(F("I2C Loadcell not found. Check connections!"));
    while(1) delay(100);
  }

  printMenu();
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') return; // Ignore newline characters

    if (c == 'C' || c == 'c') {
      Serial.print(F("Raw Value: "));
      Serial.println(scale.getRawValue());
      printMenu();
    } 
    else if (c == 'T' || c == 't') {
      scale.tare();
      Serial.println(F("Tare successful."));
      printMenu();
    }
    else if (c == 'V' || c == 'v') {
      Serial.println(F("\n--- All Saved Scale Factors ---"));
      
      // Profile 0: CUSTOM (saved by normal user calibration, no Admin Mode)
      scale.setLoadcellType(MKE_LOADCELL_CUSTOM);
      delay(50);
      float s0 = scale.getScale();
      uint32_t hexScale0;
      memcpy(&hexScale0, &s0, sizeof(float));
      Serial.print(F("Profile ID 0 (CUSTOM): "));
      Serial.print(s0, 4);
      Serial.print(F(" (HEX: 0x"));
      Serial.print(hexScale0, HEX);
      Serial.println(F(")"));

      // Profiles 1-5: Factory profiles (requires Admin Mode to save)
      for (int i = 1; i <= 5; i++) {
        scale.setLoadcellType(i);
        delay(50); // wait for PY32 to load EEPROM and apply new scale
        float s = scale.getScale();
        uint32_t hexScale;
        memcpy(&hexScale, &s, sizeof(float));
        
        Serial.print(F("Profile ID "));
        Serial.print(i);
        Serial.print(F(": "));
        Serial.print(s, 4);
        Serial.print(F(" (HEX: 0x"));
        Serial.print(hexScale, HEX);
        Serial.println(F(")"));
      }
      // restore current type
      scale.setLoadcellType(current_type);
      Serial.println(F("-------------------------------"));
      printMenu();
    }
    else if (c >= '1' && c <= '5') {
      current_type = c - '0';
      scale.setLoadcellType(current_type);
      Serial.print(F("\n[STEP 1] Selected Loadcell Profile ID = "));
      Serial.println(current_type);
      
      Serial.println(F("Please remove all weight from the scale, then type 'OK' to Tare (Zero)."));
      
      while(true) {
        if (Serial.available() > 0) {
          String s = Serial.readStringUntil('\n');
          s.trim();
          s.toUpperCase();
          if (s == "OK") {
            scale.tare();
            Serial.println(F("Tare successful."));
            break;
          }
        }
      }
      
      Serial.println(F("\n[STEP 2] Place a reference weight (e.g., 100g, 500g) on the scale."));
      Serial.print(F("Enter the exact weight of the reference weight (unit: grams) and press Enter: "));
      
      while(true) {
        if (Serial.available() > 0) {
          float weight = Serial.parseFloat();
          if (weight > 0) {
            Serial.println(weight);
            
            // IMPORTANT: Unlock Admin Mode so PY32 saves to the correct
            // profile slot (1-5) instead of the CUSTOM slot (0).
            // We VERIFY the unlock succeeded before calibrating.
            Serial.println(F("Unlocking Admin Mode on PY32..."));
            bool adminOk = false;
            for (int retry = 0; retry < 5; retry++) {
              scale.unlockAdminMode(0x12345678);
              delay(150); // Wait for PY32 to finish HX711 read and process
              if (scale.isAdminMode()) {
                adminOk = true;
                break;
              }
              Serial.print(F("Retry unlock... "));
              Serial.println(retry + 1);
            }

            if (!adminOk) {
              Serial.println(F("[ERROR] Failed to unlock Admin Mode! Calibration aborted."));
              Serial.println(F("Check PY32 connection and try again."));
              break;
            }
            Serial.println(F("Admin Mode confirmed active!"));

            // Calibrate: PY32 computes new scaleValue and calls ForceSaveEeprom
            // (writes to Flash immediately - no debounce wait needed)
            scale.calibrate(weight);
            delay(200); // Wait for PY32 to finish Flash write
            
            // Lock Admin Mode to protect factory profiles
            scale.lockAdminMode();
            Serial.println(F("Admin Mode locked."));

            // Read back the result to confirm
            float newScale = scale.getScale();
            Serial.print(F("Calibration complete! The new Scale Value is: "));
            Serial.print(newScale, 4);
            
            uint32_t hexScale;
            memcpy(&hexScale, &newScale, sizeof(float));
            Serial.print(F(" (HEX: 0x"));
            Serial.print(hexScale, HEX);
            Serial.println(F(")"));
            
            Serial.print(F("\nThis value has been saved to the Module's EEPROM, under Profile ID: "));
            Serial.println(current_type);
            break;
          }
        }
      }
      
      Serial.println(F("\nProcess complete. Press Enter to return to the main menu..."));
      while(Serial.available() == 0) delay(10);
      while(Serial.available() > 0) Serial.read(); // clear buffer
      printMenu();
    }
  }
}
