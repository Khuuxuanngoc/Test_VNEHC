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
    Serial.println(F("Bring a card close to the reader..."));
}

void loop() {
    if (rfid.isCardPresent()) {
        Serial.println(F("-------------------------"));
        Serial.println(F("Card Detected!"));
        
        // Read 4 bytes UID
        uint32_t uid = rfid.getUID();
        Serial.print(F("UID (4 bytes - Hex): "));
        Serial.println(uid, HEX);
        
        // Read full UID (cards may have 4, 7, or 10 bytes UID)
        uint8_t uidSize = rfid.getUIDSize();
        if (uidSize > 0 && uidSize <= 10) {
            uint8_t uidFull[10];
            rfid.getUIDFull(uidFull);
            
            Serial.print(F("Full UID ("));
            Serial.print(uidSize);
            Serial.print(F(" bytes): "));
            for (int i = 0; i < uidSize; i++) {
                if (uidFull[i] < 0x10) Serial.print(F("0"));
                Serial.print(uidFull[i], HEX);
                Serial.print(F(" "));
            }
            Serial.println();
        }
        
        // Card Type and SAK
        Serial.print(F("SAK: "));
        Serial.println(rfid.getSAK(), HEX);
        
        Serial.print(F("Card Type: "));
        Serial.println(rfid.getCardType());
        
        // Halt card (put into sleep state to prevent continuous reading)
        rfid.haltCard();
        
        delay(1000); // Wait 1 second before allowing a new card to be scanned
    }
    
    delay(50); // Polling delay
}
