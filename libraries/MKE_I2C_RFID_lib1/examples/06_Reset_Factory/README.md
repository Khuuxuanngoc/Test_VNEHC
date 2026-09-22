# 06_Reset_Factory

*Read this document in: [🇻🇳 Tiếng Việt](#tiếng-việt) | [🇬🇧 English](#english)*

---

<a id="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Mô tả
Ví dụ này được sử dụng để Khôi phục cài đặt gốc (Factory Reset) cho mạch MKE_I2C_RFID.

**⚠️ LƯU Ý QUAN TRỌNG:** Chỉ kết nối DUY NHẤT 1 module MKE_I2C_RFID vào mạch Arduino trong quá trình khôi phục cài đặt gốc để tránh việc reset nhầm các thiết bị khác trên cùng đường truyền I2C.
Do mạch không có nút nhấn vật lý, việc khôi phục cài đặt sẽ được thực hiện qua cổng Serial Monitor. Chương trình sẽ tự động dò tìm địa chỉ I2C hiện tại của mạch và sử dụng lớp `MKE_I2C_RFID_Advanced` để mở khóa quyền Quản trị viên (Admin Mode), sau đó gửi lệnh Factory Reset.
Mạch sẽ tự động chạy hàm `ResetEeprom()` nội bộ để:
- Đặt lại địa chỉ I2C về mặc định là **0x29**.
- Đặt lại các thông số và cấu hình về mặc định.

### Đấu nối
| Chân Module MKE | Chân Arduino / ESP32 | Mô tả |
| :---: | :---: | :--- |
| **GND** | GND | Nối Đất |
| **VCC** | 5V hoặc 3.3V | Nguồn cấp |
| **SDA** | SDA | Dữ liệu I2C |
| **SCL** | SCL | Xung nhịp I2C |

### Hướng dẫn
1. Nạp code `06_Reset_Factory.ino`.
2. Mở cửa sổ Serial Monitor ở tốc độ **115200 baud**. Cài đặt kết thúc dòng là **"Newline"** hoặc **"Both NL & CR"**.
3. Mạch Arduino sẽ quét và nhận diện địa chỉ hiện tại của cảm biến.
4. Gõ `YES` (viết hoa) và nhấn Enter trên thanh nhập liệu để xác nhận quá trình khôi phục.
5. Sau khi thành công, ngắt và cấp lại nguồn cho mạch để hệ thống tải lại cấu hình gốc.

---

<a id="english"></a>
## 🇬🇧 English

### Description
This example is used to perform a Factory Reset on the MKE_I2C_RFID module.

**⚠️ IMPORTANT NOTE:** Please connect ONLY ONE MKE_I2C_RFID module to the Arduino during the factory reset process to avoid accidentally resetting other devices on the same I2C bus.
Because the module does not have a physical button, the factory reset is executed via the Serial Monitor. The sketch will automatically detect the current I2C address of the module and use the `MKE_I2C_RFID_Advanced` class to unlock Admin Mode, then send the Factory Reset command.
The module will automatically run its internal `ResetEeprom()` function to:
- Reset the I2C address to the default **0x29**.
- Reset all parameters and configurations to default.

### Wiring
| MKE Module Pin | Arduino / ESP32 Pin | Description |
| :---: | :---: | :--- |
| **GND** | GND | Ground |
| **VCC** | 5V or 3.3V | Power Supply |
| **SDA** | SDA | I2C Data |
| **SCL** | SCL | I2C Clock |

### Instructions
1. Upload the `06_Reset_Factory.ino` sketch.
2. Open the Serial Monitor at **115200 baud**. Set the line ending to **"Newline"** or **"Both NL & CR"**.
3. Arduino will scan and detect the current I2C address of the sensor.
4. Type `YES` (all caps) and press Enter in the input bar to confirm the reset process.
5. After success, power cycle the module so the system can reload the default configuration.
