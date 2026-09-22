# MKE I2C RFID Library

*Read this document in: [🇻🇳 Tiếng Việt](#tiếng-việt) | [🇬🇧 English](#english)*

---

<a id="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

**MKE_I2C_RFID** là thư viện Arduino mạnh mẽ và tối ưu hóa chuyên dùng để giao tiếp với mạch đọc thẻ MKE-M26-RC522-I2C-RFID-MODULE.
Thư viện này chuyển toàn bộ các thao tác xử lý sóng RF 13.56MHz và mã hóa MIFARE phức tạp xuống vi điều khiển trên mạch I2C, giúp tiết kiệm cực kỳ nhiều tài nguyên cho vi điều khiển Arduino/ESP32 chính của bạn.

### 🌟 Tính năng nổi bật
- **Giao tiếp I2C tốc độ cao:** Sử dụng giao tiếp I2C phần cứng, không gây block chương trình như các thư viện SPI truyền thống.
- **Giảm tải xử lý MIFARE:** Việc phát hiện thẻ, đọc UID, xác thực mật khẩu khóa (Key Auth), đọc/ghi khối dữ liệu (Block) được xử lý hoàn toàn bởi mạch MKE_I2C_RFID.
- **Hỗ trợ Value Block:** Có sẵn API trực tiếp cho các ứng dụng ví điện tử, nạp rút điểm (Increment, Decrement, Set Value).
- **Hỗ trợ đa module:** Có thể thay đổi địa chỉ I2C nội bộ của mạch để kết nối cùng lúc nhiều đầu đọc RFID trên cùng một đường dây I2C.

### 🔌 Sơ đồ kết nối (Pinout)
| Chân Module MKE | Chân Arduino / ESP32 | Mô tả |
| :---: | :---: | :--- |
| **GND** | GND | Nối Đất |
| **VCC** | 5V hoặc 3.3V | Nguồn cấp (Phù hợp với điện áp giao tiếp của Vi điều khiển) |
| **SDA** | SDA (vd: A4 trên Uno) | Dữ liệu I2C |
| **SCL** | SCL (vd: A5 trên Uno) | Xung nhịp I2C |

### 🚀 Bắt đầu sử dụng

**Cài đặt thông qua MKE_ONE:**
Thay vì cài đặt thư viện này một cách độc lập, bạn nên cài đặt gói **`MKE_ONE`** thông qua Arduino Library Manager. `MKE_ONE` là hệ sinh thái tổng hợp sẽ tự động cài đặt thư viện này cùng tất cả các thư viện phụ thuộc khác của MakerEdu cho bạn.

Vui lòng tham khảo các đoạn code mẫu trong thư mục `examples/`. Bạn nên chạy thử theo thứ tự sau:
1. **01_Read_UID**: Hướng dẫn phát hiện thẻ và đọc mã định danh UID.
2. **02_DumpInfo**: Đọc và hiển thị toàn bộ thông tin nội dung các Sector/Block trên thẻ.
3. **03_Read_Write_Personal_Data**: Đọc và ghi dữ liệu cá nhân vào một Block cụ thể.
4. **04_Digital_Wallet**: Ví dụ nâng cao mô phỏng một ví điện tử (Nạp/Rút tiền).
5. **05_Change_I2C_Address**: Đổi địa chỉ I2C bằng phần mềm.
6. **06_Reset_Factory**: Khôi phục cài đặt gốc của module.
7. **07_I2C_Multiple_Device**: Giao tiếp với nhiều module RFID cùng lúc.
8. **09_Compare_UID**: Đọc và so sánh UID thẻ với UID cho trước để cấp quyền truy cập.

### 📚 Tổng hợp các hàm cơ bản (API)
```cpp
#include "MKE_I2C_RFID.h"
MKE_I2C_RFID rfid;

void setup() {
    Wire.begin();
    rfid.begin();                       // Khởi tạo module RFID
}

void loop() {
    if (rfid.isCardPresent()) {
        uint32_t uid = rfid.getUID();   // Đọc 4 byte đầu tiên của UID
        
        // Cài đặt key xác thực
        uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        rfid.setAuthKey(key);
        
        // Xác thực Sector 1 (Block 4)
        if (rfid.authenticateKeyA(4) == 0) {
            uint8_t buffer[16];
            rfid.readBlock(4, buffer);  // Đọc nội dung block 4 vào buffer
        }
        
        rfid.haltCard();                // Cho thẻ vào trạng thái ngủ
        rfid.stopCrypto();              // Dừng bộ mã hóa phần cứng
    }
    delay(50);
}
```

---

<a id="english"></a>
## 🇬🇧 English

The **MKE_I2C_RFID** is a robust and highly optimized Arduino library for interfacing with the MKE-M26-RC522-I2C-RFID-MODULE.
This library offloads all the complex 13.56MHz RF signal processing and MIFARE crypto operations directly to the I2C module, drastically saving processing power and memory on your main Arduino/ESP32 controller.

### 🌟 Key Features
- **High-Speed I2C Interface:** Non-blocking hardware I2C communication instead of traditional bit-banged SPI.
- **Offloaded MIFARE Operations:** Card detection, UID scanning, Key Authentication, and Block Read/Write are entirely handled by the module's internal MCU.
- **Value Block Support:** Direct API support for e-wallet operations (Increment, Decrement, Set Value).
- **Multiple Modules:** Change the module's internal I2C Address dynamically to allow chaining multiple RFID readers on a single I2C bus.

### 🔌 Wiring (Pinout)
| MKE Module Pin | Arduino / ESP32 Pin | Description |
| :---: | :---: | :--- |
| **GND** | GND | Ground |
| **VCC** | 5V or 3.3V | Power Supply (Matches your MCU's logic level) |
| **SDA** | SDA (e.g., A4 on Uno) | I2C Data |
| **SCL** | SCL (e.g., A5 on Uno) | I2C Clock |

### 🚀 Getting Started

**Installation via MKE_ONE:**
Instead of installing this library directly, we strongly recommend installing the **`MKE_ONE`** package via the Arduino Library Manager. `MKE_ONE` is the central ecosystem that will automatically install this library and all other MakerEdu dependencies for you.

Please refer to the `examples/` folder for step-by-step guides. We recommend exploring them in the following order:
1. **01_Read_UID**: Detecting a card and reading its unique identifier.
2. **02_DumpInfo**: Reading and displaying the entire memory content (Sectors/Blocks) of the card.
3. **03_Read_Write_Personal_Data**: Reading and writing custom data to a specific block.
4. **04_Digital_Wallet**: Advanced example simulating a digital wallet (Deposit, Withdraw).
5. **05_Change_I2C_Address**: Changing the module's I2C address via software.
6. **06_Reset_Factory**: Restoring the module to factory defaults.
7. **07_I2C_Multiple_Device**: Communicating with multiple RFID modules simultaneously.
8. **09_Compare_UID**: Comparing a card's UID with a predefined UID to grant or deny access.

### 📚 Quick API Reference
```cpp
#include "MKE_I2C_RFID.h"
MKE_I2C_RFID rfid;

void setup() {
    Wire.begin();
    rfid.begin();                       // Initialize the RFID module
}

void loop() {
    if (rfid.isCardPresent()) {
        uint32_t uid = rfid.getUID();   // Get the first 4-byte UID
        
        // Setup authentication key
        uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        rfid.setAuthKey(key);
        
        // Authenticate Sector 1 (Block 4)
        if (rfid.authenticateKeyA(4) == 0) {
            uint8_t buffer[16];
            rfid.readBlock(4, buffer);  // Read block 4 into buffer
        }
        
        rfid.haltCard();                // Put card to sleep
        rfid.stopCrypto();              // Stop encryption on PCD
    }
    delay(50);
}
```


