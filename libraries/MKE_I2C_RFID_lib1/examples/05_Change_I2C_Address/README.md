# 05_Change_I2C_Address

*Read this document in: [🇻🇳 Tiếng Việt](#tiếng-việt) | [🇬🇧 English](#english)*

---

<a id="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Mô tả
Ví dụ này hướng dẫn cách thay đổi địa chỉ I2C của mạch MKE_I2C_RFID.

**⚠️ LƯU Ý QUAN TRỌNG:** Chỉ kết nối DUY NHẤT 1 module MKE_I2C_RFID vào mạch Arduino trong quá trình đổi địa chỉ I2C để tránh việc đổi nhầm địa chỉ của các thiết bị khác trên cùng đường truyền I2C.
Do mạch không có nút nhấn hoặc công tắc gạt (DIP switch) để thay đổi địa chỉ phần cứng, việc thay đổi địa chỉ được thực hiện thông qua phần mềm. Chương trình sẽ tự động quét địa chỉ hiện tại của mạch và cho phép bạn nhập địa chỉ mới (dạng HEX) thông qua Serial Monitor.

### Đấu nối
| Chân Module MKE | Chân Arduino / ESP32 | Mô tả |
| :---: | :---: | :--- |
| **GND** | GND | Nối Đất |
| **VCC** | 5V hoặc 3.3V | Nguồn cấp |
| **SDA** | SDA | Dữ liệu I2C |
| **SCL** | SCL | Xung nhịp I2C |

### Hướng dẫn
1. Nạp code `05_Change_I2C_Address.ino`.
2. Mở cửa sổ Serial Monitor ở tốc độ **115200 baud**. Cài đặt kết thúc dòng là **"Newline"** hoặc **"Both NL & CR"**.
3. Arduino sẽ tự động quét và in ra địa chỉ hiện tại của mạch.
4. Gõ địa chỉ I2C mới mà bạn muốn đổi (ví dụ: `3A` hoặc `50`) vào thanh nhập liệu và nhấn Enter.
5. Sau khi thay đổi thành công, bạn cần ngắt nguồn và cấp lại để module lưu và khởi động lại với địa chỉ mới. (Tùy chọn)

---

<a id="english"></a>
## 🇬🇧 English

### Description
This example demonstrates how to change the I2C address of the MKE_I2C_RFID module.

**⚠️ IMPORTANT NOTE:** Please connect ONLY ONE MKE_I2C_RFID module to the Arduino during the I2C address change process to avoid accidentally modifying other devices on the same I2C bus.
Since the module does not have a physical button or DIP switch to change the hardware address, changing the address is done via software. The program will automatically scan for the current address of the module and allow you to input a new address (in HEX) via the Serial Monitor.

### Wiring
| MKE Module Pin | Arduino / ESP32 Pin | Description |
| :---: | :---: | :--- |
| **GND** | GND | Ground |
| **VCC** | 5V or 3.3V | Power Supply |
| **SDA** | SDA | I2C Data |
| **SCL** | SCL | I2C Clock |

### Instructions
1. Upload the `05_Change_I2C_Address.ino` sketch.
2. Open the Serial Monitor at **115200 baud**. Set the line ending to **"Newline"** or **"Both NL & CR"**.
3. Arduino will automatically scan and print the current address of the module.
4. Type the new I2C address you want to change to (e.g., `3A` or `50`) in the input bar and press Enter.
5. After a successful change, power cycle the module to ensure it boots up with the new address. (Optional)
