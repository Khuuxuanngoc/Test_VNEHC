#ifndef kxnTaskTest_I2C_RFID_H
#define kxnTaskTest_I2C_RFID_H

#include "kxnTask.h"
#include <Wire.h>
#include "MKE_I2C_RFID.h"

CREATE_TASK(kxnTaskTest_I2C_RFID)

MKE_I2C_RFID rfid;

// Define your authorized card UID here.
// For example, if your card's UID is "41 D1 47 01", the uint32_t value is 0x41D14701
const uint32_t AUTHORIZED_UID_KXN = 0x41D14701; 
const uint32_t AUTHORIZED_UID_HSHOP = 0x93294408; 

void setup() {
    // Serial.begin(115200);
    // Wire.begin();
    
    Serial.println(F("Initializing MKE_I2C_RFID..."));
    if (!rfid.begin()) {
        Serial.println(F("Failed to communicate with MKE_I2C_RFID. Check connections."));
        while (1) {
            delay(10);
        }
    }

    Serial.print(F("RFID Module Found! Firmware Version: "));
    Serial.println(rfid.getFirmwareVersion());
    
    Serial.println(F("RFID System Ready."));
    Serial.println(F("Bring a card close to the reader..."));
    
    kxnTaskManager.add(this);
    setState(0);
}

void loop() {
    if (rfid.isCardPresent()) {
        Serial.println(F("-------------------------"));
        
        // Read 4 bytes UID
        uint32_t uid = rfid.getUID();
        
        Serial.print(F("Scanned UID (HEX): "));
        Serial.println(uid, HEX);
        
        // Compare UID
        if (uid == AUTHORIZED_UID_KXN || uid == AUTHORIZED_UID_HSHOP) {
            Serial.println(F("ACCESS GRANTED! GOOD!"));
            // Add your logic here (e.g., open a door, turn on a green LED)
        } else {
            Serial.println(F("ACCESS DENIED! Unknown card."));
            // Add your logic here (e.g., trigger an alarm, turn on a red LED)
        }
        
        // Halt card (put into sleep state to prevent continuous reading)
        rfid.haltCard();
        
        kDelay(1000); // Wait 1 second before allowing a new card to be scanned
        return; // Exit the loop to avoid multiple reads of the same card
    }
    
    kDelay(50); // Polling delay
}

END

#endif