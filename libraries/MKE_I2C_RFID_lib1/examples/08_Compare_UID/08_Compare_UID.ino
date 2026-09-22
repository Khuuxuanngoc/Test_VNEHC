#include <Wire.h>
#include "MKE_I2C_RFID.h"

MKE_I2C_RFID rfid;

// Define your authorized card UID here.
// For example, if your card's UID is "41 D1 47 01", the uint32_t value is 0x41D14701
const uint32_t AUTHORIZED_UID = 0x41D14701; 

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
    
    Serial.println(F("RFID System Ready."));
    Serial.println(F("Bring a card close to the reader..."));
}

void loop() {
    if (rfid.isCardPresent()) {
        Serial.println(F("-------------------------"));
        
        // Read 4 bytes UID
        uint32_t uid = rfid.getUID();
        
        Serial.print(F("Scanned UID (HEX): "));
        Serial.println(uid, HEX);
        
        // Compare UID
        if (uid == AUTHORIZED_UID) {
            Serial.println(F("ACCESS GRANTED! Welcome back."));
            // Add your logic here (e.g., open a door, turn on a green LED)
        } else {
            Serial.println(F("ACCESS DENIED! Unknown card."));
            // Add your logic here (e.g., trigger an alarm, turn on a red LED)
        }
        
        // Halt card (put into sleep state to prevent continuous reading)
        rfid.haltCard();
        
        delay(1000); // Wait 1 second before allowing a new card to be scanned
    }
    
    delay(50); // Polling delay
}
