# 01_Read_UID

*Read this document in: [🇻🇳 Tiếng Việt](#tiếng-việt) | [🇬🇧 English](#english)*

---

<a id="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Mô tả
Ví dụ cơ bản này hướng dẫn cách sử dụng thư viện MKE_I2C_RFID để phát hiện thẻ MIFARE RFID và đọc Mã định danh duy nhất (UID) của nó. Ví dụ cũng cho thấy cách lấy loại thẻ và byte SAK (Select Acknowledge). 
Mạch MKE_I2C_RFID xử lý toàn bộ các giao tiếp RF 13.56MHz phức tạp, giúp Arduino của bạn chỉ cần yêu cầu dữ liệu thông qua giao tiếp I2C đơn giản.

### Đấu nối
Kết nối mạch MKE-M26-RC522-I2C-RFID-MODULE với Arduino qua I2C:

| Chân Module MKE | Chân Arduino / ESP32 | Mô tả |
| :---: | :---: | :--- |
| **GND** | GND | Nối Đất |
| **VCC** | 5V hoặc 3.3V | Nguồn cấp (Phù hợp với điện áp giao tiếp của Vi điều khiển) |
| **SDA** | SDA (vd: A4 trên Uno) | Dữ liệu I2C |
| **SCL** | SCL (vd: A5 trên Uno) | Xung nhịp I2C |

### Hướng dẫn
1. Nạp code `01_Read_UID.ino` vào mạch Arduino của bạn.
2. Mở cửa sổ Serial Monitor ở tốc độ **115200 baud**.
3. Đưa một thẻ MIFARE RFID lại gần ăng-ten của mạch.
4. Serial Monitor sẽ in ra mã UID của thẻ, SAK và Loại thẻ.

---

<a id="english"></a>
## 🇬🇧 English

### Description
This basic example demonstrates how to use the MKE_I2C_RFID library to detect a MIFARE RFID card/tag and read its Unique Identifier (UID). It also shows how to retrieve the card type and SAK (Select Acknowledge) byte. 
The module handles all the complex 13.56MHz RF communication, allowing your Arduino to simply request data via I2C.

### Wiring
Connect the MKE-M26-RC522-I2C-RFID-MODULE to your Arduino via I2C:

| MKE Module Pin | Arduino / ESP32 Pin | Description |
| :---: | :---: | :--- |
| **GND** | GND | Ground |
| **VCC** | 5V or 3.3V | Power Supply (Matches your MCU's logic level) |
| **SDA** | SDA (e.g., A4 on Uno) | I2C Data |
| **SCL** | SCL (e.g., A5 on Uno) | I2C Clock |

### Instructions
1. Upload the sketch `01_Read_UID.ino` to your Arduino.
2. Open the Serial Monitor at **115200 baud**.
3. Bring a MIFARE RFID card or tag close to the module's antenna.
4. The Serial Monitor will output the card's UID, SAK, and Type.
