# VNEHC I2C Loadcell (HX710) Module User Manual - For Manufacturers

This document provides in-depth instructions on configuring, tuning, and programming the I2C Loadcell module via I2C protocol and the physical button.

---

## Part 1: Physical Button Usage (Setup Mode)

The Loadcell module is equipped with a physical button (`S1`) for quick on-site actions without requiring commands from the I2C Master.

1. **Tare (Zeroing):**
   - **Action:** Single click.
   - **Feedback:** The system will wait for about 1 second (to avoid mechanical vibration noise caused by the finger press), and then store the new zero point (Tare).

2. **Factory Reset:**
   - **Action:** Press and hold the `S1` button for more than 3 seconds.
   - **Feedback:** The module will directly wipe the EEPROM configurations (including Scale factor and Kalman filter parameters) and force the I2C address back to the default `0x0A`. The system then performs a Soft Reload to re-initialize the filter configuration safely without triggering an MCU freeze.

---

## Part 2: I2C Protocol Guide (For Developers)

The module communicates with the Main Microcontroller (Master) via I2C. The default address is **`0x0A`**.

### 2.1. Packet Structure
The I2C protocol uses a standard Header structure: `[AddressId(1 byte)] [ModeId(1 byte)] [Value32(4 bytes)]`
- **Master Write:** Sends commands via I2C using the `ModeId` and a 32-bit `Value` (Big Endian).
- **Master Read:** Sends the `ModeId` to read, waits for a short delay (e.g., 10ms), and then uses `Wire.requestFrom` to receive the 4-byte value.

> [!WARNING]
> System-altering configurations (like changing the I2C address or updating EEPROM parameters) require the Master to unlock Admin Mode by sending the Password `0x12345678` into `ModeId` `0xC8` before proceeding.

### 2.2. System Commands (Core Commands)
General commands for system information management (Mode IDs are in HEX).

| Mode ID | Command Name | Function | 32-bit Value (Hex) |
| :---: | :--- | :--- | :--- |
| **`0x01`** | `SET_ADDRESS` | Set new I2C Address (Requires Admin) | New address (e.g. `0x0B`) |
| **`0x02`** | `GET_ID_MODULE` | Read Module's unique ID | Returns Loadcell ID |
| **`0x04`** | `GET_FW_VERSION`| Read Firmware Version | Returns Version |
| **`0x06`** | `GET_PRODUCT_CODE`| Read Product Code | Returns Product Code |
| **`0x0A`** | `GET_ADDRESS` | Read current I2C Address | Returns active address |
| **`0xC8`** | `UNLOCK_ADMIN` | Unlock/Lock Admin Mode | Send `0x12345678` to unlock |
| **`0xC9`** | `GET_ADMIN_MODE`| Check Admin status | `0x01` (Unlocked), `0x00` (Locked) |

### 2.3. Loadcell Specific Commands (Loadcell Commands)
Used for calibration, taring, Kalman filter tuning, and EEPROM configuration.

| Mode ID | Command Name | Description | Value (Payload) |
| :---: | :--- | :--- | :--- |
| **`0x32`** | `GET_RAW_VALUE` | Read raw ADC value from HX710 | `0x00` |
| **`0x33`** | `TARE` | Software Tare command | `0x00` |
| **`0x34`** | `GET_GRAM` | Read weight (grams) as Float (32-bit) | `0x00` |
| **`0x35`** | `CALIBRATE` | Calibrate scale (Requires Admin) | Known weight (Float -> uint32_t) |
| **`0x36`** | `GET_SCALE` | Read current Scale divider | Returns Float (32-bit) |
| **`0x37`** | `SET_SCALE` | Set Scale divider manually | Scale value (Float -> uint32_t) |
| **`0x3A`** | `GET_FILTER_LEVEL`| Read Filter Level | Returns `0x00` to `0x03` |
| **`0x3B`** | `SET_FILTER_LEVEL`| Set Filter Level (0: Raw, 1: Fast, 2: Medium, 3: Slow) | `0x00`, `0x01`, `0x02`, `0x03` |
| **`0x3C`** | `GET_KALMAN_MEA` | Read measurement noise (Mea_e) | Float 32-bit |
| **`0x3D`** | `SET_KALMAN_MEA` | Set measurement noise (Mea_e) | Float 32-bit (casted) |
| **`0x3E`** | `GET_KALMAN_EST` | Read estimation error (Est_e) | Float 32-bit |
| **`0x3F`** | `SET_KALMAN_EST` | Set estimation error (Est_e) | Float 32-bit (casted) |
| **`0x40`** | `GET_KALMAN_Q` | Read process noise (Q) | Float 32-bit |
| **`0x41`** | `SET_KALMAN_Q` | Set process noise (Q) | Float 32-bit (casted) |
| **`0x44`** | `GET_LOADCELL_TYPE`| Read Loadcell Type (1Kg, 5Kg...) | Returns Enum Type |
| **`0x45`** | `SET_LOADCELL_TYPE`| Set Loadcell Type | Write Enum Type (0 to 5) |

> [!TIP]
> **Floating Point Handling (Float 32-bit):** Since I2C transmits integers, parameters like Gram, Scale, or Kalman configurations (Mea, Est, Q) must be cast from the memory representation of a `Float` into a `uint32_t` before sending, and cast back upon reception (using Unions or Pointer Casting).
> 
> **Using the Arduino Library:** If you are testing modules at the factory using Arduino, you don't need to use Raw I2C. Simply include `#include "MKE_I2C_Loadcell_Advanced.h"` and use the `MKE_I2C_Loadcell_Advanced` class to call advanced configuration functions directly.

### 2.4. Arduino Master Sample Code (Raw I2C)

```cpp
#include <Wire.h>

#define LOADCELL_I2C_ADDR 0x0A

// Write Function: Send I2C Command
void sendI2CCommand(uint8_t address, uint8_t modeId, uint32_t value) {
  Wire.beginTransmission(address);
  Wire.write(address);
  Wire.write(modeId);
  Wire.write((uint8_t)(value >> 24));
  Wire.write((uint8_t)(value >> 16));
  Wire.write((uint8_t)(value >> 8));
  Wire.write((uint8_t)(value & 0xFF));
  Wire.endTransmission();
}

// Read Function: Retrieve 32-bit Data
uint32_t readI2CValue(uint8_t address, uint8_t modeId) {
  sendI2CCommand(address, modeId, 0x00);
  delay(10); 
  Wire.requestFrom(address, (uint8_t)4);
  uint32_t result = 0;
  if (Wire.available() >= 4) {
    result |= ((uint32_t)Wire.read() << 24);
    result |= ((uint32_t)Wire.read() << 16);
    result |= ((uint32_t)Wire.read() << 8);
    result |= ((uint32_t)Wire.read());
  }
  return result;
}

// Float Data Conversion
float uint32ToFloat(uint32_t val) {
  float f;
  memcpy(&f, &val, 4);
  return f;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  
  // Execute Tare
  Serial.println("Performing Tare...");
  sendI2CCommand(LOADCELL_I2C_ADDR, 0x33, 0x00);
  delay(100);
}

void loop() {
  // Read weight
  uint32_t rawGram = readI2CValue(LOADCELL_I2C_ADDR, 0x34);
  float gram = uint32ToFloat(rawGram);
  
  Serial.print("Weight (g): ");
  Serial.println(gram);
  delay(500);
}
```
