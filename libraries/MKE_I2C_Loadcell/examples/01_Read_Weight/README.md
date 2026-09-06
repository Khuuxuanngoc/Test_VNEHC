# 01 Read Weight / Đọc Khối Lượng

> **⚠️ IMPORTANT:** You MUST call `Wire.begin();` inside your `setup()` function before initializing the Loadcell. Mạch yêu cầu khởi tạo I2C (`Wire.begin()`) trước khi sử dụng thư viện.


## 🇻🇳 Tiếng Việt
Ví dụ này là đoạn code cơ bản nhất để kết nối với mạch **MKE I2C Loadcell** và đọc giá trị khối lượng.

**Các tính năng nổi bật trong ví dụ:**
*   Kết nối với Loadcell thông qua chuẩn giao tiếp I2C.
*   Đọc khối lượng theo đơn vị Gram (`getGram()`).
*   Tự động chuyển đổi khối lượng sang các đơn vị quốc tế khác: Kilogram (Kg), Ounce (Oz), Pound (Lb), và Carat (ct).
*   **Tối ưu bộ nhớ RAM:** Mã nguồn mẫu sử dụng macro `F()` (ví dụ: `Serial.print(F("Text"))`) để đẩy các chuỗi văn bản tĩnh vào bộ nhớ Flash thay vì SRAM. Việc này giúp tiết kiệm tối đa RAM, đặc biệt quan trọng khi chạy trên các vi điều khiển tài nguyên thấp như Arduino Uno/Nano.

**Cách sử dụng:**
1. Cắm module MKE I2C Loadcell vào bo mạch Arduino qua cổng I2C (SDA, SCL).
2. Nạp code vào Arduino.
3. Mở Serial Monitor (Baudrate: `115200`).
4. Theo dõi khối lượng hiển thị.

---

## 🇬🇧 English
This example provides the most basic code to connect to the **MKE I2C Loadcell** module and read weight values.

**Key Features in this Example:**
*   Connects to the Loadcell via the I2C protocol.
*   Reads weight in Grams (`getGram()`).
*   Automatically converts weight to other international units: Kilograms (Kg), Ounces (Oz), Pounds (Lb), and Carats (ct).
*   **RAM Optimization:** The example code uses the `F()` macro (e.g., `Serial.print(F("Text"))`) to store static string literals in Flash memory instead of SRAM. This significantly saves RAM, which is crucial for resource-constrained microcontrollers like the Arduino Uno/Nano.

**Usage Instructions:**
1. Connect the MKE I2C Loadcell module to your Arduino board via the I2C port (SDA, SCL).
2. Upload the code to your Arduino.
3. Open the Serial Monitor (Baudrate: `115200`).
4. Monitor the displayed weights.
