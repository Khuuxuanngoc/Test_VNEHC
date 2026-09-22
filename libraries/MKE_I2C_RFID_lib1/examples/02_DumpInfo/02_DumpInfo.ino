#include <Wire.h>
#include "MKE_I2C_RFID.h"

MKE_I2C_RFID rfid;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    Serial.println(F("Initializing MKE_I2C_RFID..."));
    if (!rfid.begin()) {
        Serial.println(F("Failed to communicate with MKE_I2C_RFID. Check connections."));
        while (1) {
            delay(10);
        }
    }
    
    Serial.print(F("RFID Module Found! Firmware Version: "));
    Serial.println(rfid.getFirmwareVersion());
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
    if (rfid.isCardPresent()) {
        Serial.println(F("---------------------------------------------------------"));
        Serial.println(F("Card Detected!"));
        
        // Read UID
        uint8_t uidSize = rfid.getUIDSize();
        uint8_t uidFull[10];
        if (uidSize > 0 && uidSize <= 10) {
            rfid.getUIDFull(uidFull);
            Serial.print(F("Card UID: "));
            for (int i = 0; i < uidSize; i++) {
                if (uidFull[i] < 0x10) Serial.print(F("0"));
                Serial.print(uidFull[i], HEX);
                Serial.print(F(" "));
            }
            Serial.println();
        }
        
        // Read SAK
        Serial.print(F("Card SAK: "));
        uint8_t sak = rfid.getSAK();
        if (sak < 0x10) Serial.print(F("0"));
        Serial.println(sak, HEX);
        
        // Set Default Key A: FF FF FF FF FF FF
        uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        rfid.setAuthKey(key);
        
        Serial.println(F("Sector Block   0  1  2  3   4  5  6  7   8  9 10 11  12 13 14 15"));
        
        // Read and print all 16 sectors of a MIFARE Classic 1K card
        for (int sector = 15; sector >= 0; sector--) {
            Serial.print(F("  "));
            if (sector < 10) Serial.print(F(" "));
            Serial.print(sector);
            Serial.print(F("   "));
            
            int firstBlock = sector * 4;
            for (int blockOffset = 3; blockOffset >= 0; blockOffset--) {
                int blockAddr = firstBlock + blockOffset;
                
                if (blockOffset != 3) {
                    Serial.print(F("       "));
                }
                
                if (blockAddr < 10) Serial.print(F(" "));
                Serial.print(blockAddr);
                Serial.print(F("   "));
                
                // Authenticate with Key A
                uint8_t status = rfid.authenticateKeyA(blockAddr);
                if (status == 0) { // 0 = STATUS_OK
                    uint8_t buffer[16];
                    // Read block content
                    status = rfid.readBlock(blockAddr, buffer);
                    if (status == 0) {
                        for (int i = 0; i < 16; i++) {
                            if (i == 4 || i == 8 || i == 12) Serial.print(F(" "));
                            if (buffer[i] < 0x10) Serial.print(F("0"));
                            Serial.print(buffer[i], HEX);
                            Serial.print(F(" "));
                        }
                    } else {
                        Serial.print(F("Read failed (status: "));
                        Serial.print(status);
                        Serial.print(F(")"));
                    }
                } else {
                    Serial.print(F("Auth failed (status: "));
                    Serial.print(status);
                    Serial.print(F(")"));
                }
                Serial.println();
            }
        }
        
        // Halt card and stop crypto
        rfid.haltCard();
        rfid.stopCrypto();
        
        delay(2000); // Wait 2 seconds before allowing a new scan
    }
    
    delay(50); // Polling delay
}
