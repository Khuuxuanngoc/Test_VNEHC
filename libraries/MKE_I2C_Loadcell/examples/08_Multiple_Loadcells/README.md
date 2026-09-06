# Example 08: Multiple Loadcells

> **⚠️ IMPORTANT:** You MUST call `Wire.begin();` inside your `setup()` function before initializing the Loadcell. Mạch yêu cầu khởi tạo I2C (`Wire.begin()`) trước khi sử dụng thư viện.


🇬🇧 **English**
This example demonstrates how to connect and read from two or more **MKE-S18 I2C HX710 Loadcell Sensor** modules simultaneously on the same I2C bus.

### Important Note
By default, all modules have the same I2C address (`0x0A`). To use multiple modules on the same I2C bus, you **must change the I2C address** of the additional modules so that each module has a unique address.
1. Connect only one module to the Arduino.
2. Run **Example 07 (Change I2C Address)** to change its address (e.g., to `0x0B`).
3. Connect all modules in parallel to the I2C bus and run this example.

---

🇻🇳 **Tiếng Việt**
Ví dụ này hướng dẫn cách kết nối và đọc dữ liệu từ hai hoặc nhiều cảm biến **MKE-S18 I2C HX710 Loadcell Sensor** cùng lúc trên cùng một bus I2C.

### Lưu ý quan trọng
Mặc định, tất cả các module đều có chung địa chỉ I2C (`0x0A`). Để sử dụng nhiều module trên cùng một bus I2C, bạn **bắt buộc phải đổi địa chỉ I2C** của các module lắp thêm sao cho mỗi mạch có một địa chỉ duy nhất.
1. Chỉ kết nối một mạch duy nhất vào Arduino.
2. Chạy **Example 07 (Change I2C Address)** để đổi địa chỉ của mạch đó (ví dụ đổi thành `0x0B`).
3. Kết nối song song tất cả các mạch vào bus I2C và chạy ví dụ này.
