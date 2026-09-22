# 02_DumpInfo

*Read this document in: [🇻🇳 Tiếng Việt](#tiếng-việt) | [🇬🇧 English](#english)*

---

<a id="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Mô tả
Ví dụ này hướng dẫn cách sử dụng thư viện MKE_I2C_RFID để đọc và in ra (dump) toàn bộ nội dung bộ nhớ của một thẻ MIFARE Classic 1K.
Chương trình sẽ thực hiện xác thực bằng Key A mặc định (`FF FF FF FF FF FF`) cho toàn bộ 16 sector và đọc 4 block bên trong mỗi sector.

### Đấu nối
Kết nối mạch MKE-M26-RC522-I2C-RFID-MODULE với Arduino qua I2C:

| Chân Module MKE | Chân Arduino / ESP32 | Mô tả |
| :---: | :---: | :--- |
| **GND** | GND | Nối Đất |
| **VCC** | 5V hoặc 3.3V | Nguồn cấp (Phù hợp với điện áp giao tiếp của Vi điều khiển) |
| **SDA** | SDA (vd: A4 trên Uno) | Dữ liệu I2C |
| **SCL** | SCL (vd: A5 trên Uno) | Xung nhịp I2C |

### Hướng dẫn
1. Nạp code `02_DumpInfo.ino` vào mạch Arduino của bạn.
2. Mở cửa sổ Serial Monitor ở tốc độ **115200 baud**.
3. Đưa một thẻ MIFARE Classic 1K lại gần ăng-ten của mạch.
4. Serial Monitor sẽ in ra UID, SAK, và toàn bộ dữ liệu thô (hex data) của cả 64 block nằm trong 16 sector.

---

<a id="english"></a>
## 🇬🇧 English

### Description
This example demonstrates how to use the MKE_I2C_RFID library to read and dump the entire memory contents of a MIFARE Classic 1K RFID card. 
It performs authentication using the default Key A (`FF FF FF FF FF FF`) for all 16 sectors and reads the 4 blocks within each sector.

### Wiring
Connect the MKE-M26-RC522-I2C-RFID-MODULE to your Arduino via I2C:

| MKE Module Pin | Arduino / ESP32 Pin | Description |
| :---: | :---: | :--- |
| **GND** | GND | Ground |
| **VCC** | 5V or 3.3V | Power Supply (Matches your MCU's logic level) |
| **SDA** | SDA (e.g., A4 on Uno) | I2C Data |
| **SCL** | SCL (e.g., A5 on Uno) | I2C Clock |

### Instructions
1. Upload the sketch `02_DumpInfo.ino` to your Arduino.
2. Open the Serial Monitor at **115200 baud**.
3. Bring a MIFARE Classic 1K card close to the module's antenna.
4. The Serial Monitor will print the UID, SAK, and the raw hex data of all 64 blocks across the 16 sectors.
