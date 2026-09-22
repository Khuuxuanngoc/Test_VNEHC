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
    Serial.println(F("   MKE I2C RFID - Digital Wallet"));
    Serial.println(F("========================================"));
    Serial.println(F("Example: How to use MIFARE Value Blocks"));
    Serial.println(F("to create a wallet (Bus ticket, Parking...)."));
    Serial.println(F("Please place a card on the reader..."));
}

void loop() {
    if (rfid.isCardPresent()) {
        Serial.println(F("\n--- Card Detected ---"));
        
        uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        rfid.setAuthKey(key);
        
        // Select Block 5 (inside Sector 1) as Wallet
        uint8_t walletBlock = 5; 
        Serial.println(F("Authenticating Wallet Block 5..."));
        
        if (rfid.authenticateKeyA(walletBlock) == 0) {
            Serial.println(F("Auth Success!"));
            
            int32_t currentBalance = 0;
            
            // 1. Read current balance (this also checks if block is a valid Value Block)
            Serial.println(F("\n1. Reading balance BEFORE transaction..."));
            uint8_t status = rfid.getValue(walletBlock, &currentBalance);
            
            // If this block has never been formatted as a Value Block, getValue will fail.
            // In that case, we will "Initialize" the card with 100,000 VND.
            if (status != 0) {
                Serial.println(F("   Block 5 is not a Value Block. Initializing to 100,000 VND..."));
                if (rfid.setValue(walletBlock, 100000) == 0) {
                    Serial.println(F("   Initialization Success!"));
                    currentBalance = 100000;
                } else {
                    Serial.println(F("   Initialization Failed!"));
                }
            } else {
                Serial.print(F("   Current Balance: "));
                Serial.print(currentBalance);
                Serial.println(F(" VND"));
            }
            
            // 2. Simulate swiping for a Bus Ticket: Deduct 5,000 VND
            Serial.println(F("\n2. Processing Transaction..."));
            if (currentBalance >= 5000) {
                Serial.println(F("   Swiping card for Bus Ticket (Cost: 5,000 VND)..."));
                
                // Use hardware Decrement feature (very safe, immune to power loss during tx)
                if (rfid.decrementValue(walletBlock, 5000) == 0) {
                    Serial.println(F("   Transaction Success!"));
                    
                    // 3. Read back to confirm new balance
                    Serial.println(F("\n3. Reading balance AFTER transaction..."));
                    if (rfid.getValue(walletBlock, &currentBalance) == 0) {
                        Serial.print(F("   New Balance: "));
                        Serial.print(currentBalance);
                        Serial.println(F(" VND"));
                    }
                } else {
                    Serial.println(F("   Transaction Failed!"));
                }
            } else {
                Serial.println(F("   Insufficient funds! Please recharge."));
                
                // Auto-recharge 100,000 VND if out of money (Using Increment)
                Serial.println(F("   Auto-recharging 100,000 VND..."));
                if (rfid.incrementValue(walletBlock, 100000) == 0) {
                    Serial.println(F("   Recharge Success!"));
                }
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
