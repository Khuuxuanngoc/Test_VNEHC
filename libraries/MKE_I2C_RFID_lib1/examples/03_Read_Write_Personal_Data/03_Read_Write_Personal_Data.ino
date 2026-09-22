#include <Wire.h>
#include "MKE_I2C_RFID.h"

MKE_I2C_RFID rfid;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    Serial.println(F("Initializing MKE_I2C_RFID..."));
    if (!rfid.begin()) {
        Serial.println(F("Failed to communicate. Check connections."));
        while (1) delay(10);
    }
    
    Serial.println(F("========================================"));
    Serial.println(F("   MKE I2C RFID - Personal Data"));
    Serial.println(F("========================================"));
    Serial.println(F("Example: How to read and write Text (Strings)"));
    Serial.println(F("to a MIFARE Classic Card."));
    Serial.println(F("Please place a card on the reader..."));
}

void printBlockAsText(uint8_t *buffer) {
    Serial.print(F("'"));
    for (int i = 0; i < 16; i++) {
        // Only print printable ASCII characters (from 32 to 126)
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            Serial.print((char)buffer[i]);
        }
    }
    Serial.println(F("'"));
}

void loop() {
    if (rfid.isCardPresent()) {
        Serial.println(F("\n--- Card Detected ---"));
        
        uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        rfid.setAuthKey(key);
        
        // Select Block 4 (First block of Sector 1)
        uint8_t targetBlock = 4; 
        Serial.println(F("Authenticating Block 4..."));
        
        if (rfid.authenticateKeyA(targetBlock) == 0) {
            Serial.println(F("Auth Success!"));
            uint8_t rwBuffer[16];
            
            // 1. Read data BEFORE writing
            Serial.println(F("1. Reading data BEFORE write..."));
            if (rfid.readBlock(targetBlock, rwBuffer) == 0) {
                Serial.print(F("   Current Data: "));
                printBlockAsText(rwBuffer);
            } else {
                Serial.println(F("   Read Failed!"));
            }
            
            // 2. Data to write (max 16 characters per block)
            String personalData = "Hello MakerEdu!";
            memset(rwBuffer, 0, 16); // Clear the buffer with 0s
            
            // Copy data from String to byte array
            personalData.getBytes(rwBuffer, 16); 
            
            Serial.print(F("\n2. Writing new data: '"));
            Serial.print(personalData);
            Serial.println(F("' to Block 4..."));
            
            if (rfid.writeBlock(targetBlock, rwBuffer) == 0) {
                Serial.println(F("   Write Success!"));
            } else {
                Serial.println(F("   Write Failed!"));
            }
            
            // 3. Read back data AFTER writing to verify
            Serial.println(F("\n3. Reading data AFTER write..."));
            if (rfid.readBlock(targetBlock, rwBuffer) == 0) {
                Serial.print(F("   New Data: "));
                printBlockAsText(rwBuffer);
            } else {
                Serial.println(F("   Read Failed!"));
            }
            
        } else {
            Serial.println(F("Auth Failed. Make sure it's a MIFARE Classic card."));
        }
        
        rfid.haltCard();
        rfid.stopCrypto();
        Serial.println(F("\nRemove card to restart."));
        
        // Wait until the user removes the card
        while (rfid.isCardPresent()) {
            delay(100);
        }
    }
    delay(50);
}
