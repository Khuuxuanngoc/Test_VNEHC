# 07_I2C_Multiple_Device

*Read this document in: [🇻🇳 Tiếng Việt](#tiếng-việt) | [🇬🇧 English](#english)*

---

<a id="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Mô tả
Ví dụ này trình diễn khả năng mạnh mẽ nhất của chuẩn giao tiếp I2C: **Điều khiển nhiều module trên cùng một đường truyền (Bus)**. Bằng cách nối song song nhiều mạch MKE_I2C_RFID, bạn có thể quét thẻ từ nhiều vị trí khác nhau mà không cần tốn thêm chân cắm trên Arduino.

### Lưu ý quan trọng
Để ví dụ này hoạt động, bạn CẦN PHẢI đổi địa chỉ của một module sang địa chỉ khác (ví dụ `0x30`) thông qua đoạn mã mẫu `05_Change_I2C_Address.ino`. Module còn lại giữ nguyên địa chỉ mặc định `0x29`.

### Đấu nối
Tất cả các module đều được cắm song song với nhau:
| Chân Module MKE | Chân Arduino / ESP32 | Mô tả |
| :---: | :---: | :--- |
| **GND** | GND | Nối Đất |
| **VCC** | 5V hoặc 3.3V | Nguồn cấp |
| **SDA** | SDA | Nối chung tất cả các chân SDA |
| **SCL** | SCL | Nối chung tất cả các chân SCL |

---

<a id="english"></a>
## 🇬🇧 English

### Description
This example demonstrates the most powerful capability of the I2C protocol: **Controlling multiple modules on the same bus**. By connecting multiple MKE_I2C_RFID modules in parallel, you can scan cards from different physical locations without wasting additional Arduino GPIO pins.

### Important Note
For this example to work, you MUST change the address of one module to a different address (e.g., `0x30`) using the `05_Change_I2C_Address.ino` example. The other module can remain at the default address `0x29`.

### Wiring
All modules should be wired in parallel:
| MKE Module Pin | Arduino / ESP32 Pin | Description |
| :---: | :---: | :--- |
| **GND** | GND | Ground |
| **VCC** | 5V or 3.3V | Power Supply |
| **SDA** | SDA | Connect all SDA pins together |
| **SCL** | SCL | Connect all SCL pins together |
