# MKE I2C Loadcell Library

*Read this document in: [🇬🇧 English](#english) | [🇻🇳 Tiếng Việt](#tiếng-việt)*

---

<a id="english"></a>
## 🇬🇧 English

The **MKE_I2C_Loadcell** is a robust and highly optimized Arduino library for interfacing with the MKE I2C Loadcell module (powered by PY32F030 and HX710B). 
This library offloads all complex signal processing (Kalman filtering, Zero tracking, Calibration) to the I2C module, saving immense amounts of processing power and memory on your Arduino/ESP32.

### 🌟 Key Features
- **High-Speed I2C Interface:** Does not block your MCU like traditional HX710B libraries.
- **Built-in Kalman Filter:** Choose between Fast, Medium, and Slow/Stable modes for flawless readings.
- **EEPROM Storage:** Tare offsets and Calibration Scale Factors are saved directly onto the module's non-volatile memory.
- **Piece Counting (PCS):** Built-in logic for counting identical items.
- **Multi-Unit Output:** Instantly get weights in Grams, Kilograms, Ounces, Pounds, or Carats.
- **Configurable I2C Address:** Allows connecting up to 127 load cells on a single I2C bus!

### 🔌 Wiring (Pinout)
| MKE Module Pin | Arduino / ESP32 Pin | Description |
| :---: | :---: | :--- |
| **GND** | GND | Ground |
| **VCC** | 5V or 3.3V | Power Supply (Matches your MCU's logic level) |
| **SDA** | SDA (e.g., A4 on Uno) | I2C Data |
| **SCL** | SCL (e.g., A5 on Uno) | I2C Clock |

### 🚀 Getting Started
Please refer to the `examples/` folder for step-by-step guides. We recommend exploring them in the following order:
1. **01_Read_Weight:** The absolute basics. Read weight in various units.
2. **02_Tare_and_Calibrate:** How to zero the scale and calibrate it with a known weight.
3. **03_Piece_Counting:** How to count identical items (screws, pills, components).
4. **04_Raw_Data:** Read pure ADC data for debugging and custom DSP.
5. **05_Advanced_Filter_Config:** Learn to configure the Kalman Filter level.
6. **06_Module_Information:** Read hardware info (Firmware version, I2C address).
7. **07_Change_I2C_Address:** Tool to change the module's I2C address dynamically.

### 📚 Quick API Reference
```cpp
MKE_I2C_Loadcell scale;

scale.begin();                  // Initialize the scale
scale.tare();                   // Tare (Zero) the scale (Saves to EEPROM)
scale.calibrate(500.0);         // Calibrate using a 500g weight (Saves to EEPROM)

float g  = scale.getGram();     // Get weight in Grams
float kg = scale.getKilogram(); // Get weight in Kilograms

scale.setFilterLevel(3);        // Set filter to Slow & Stable (1=Fast, 2=Medium, 3=Slow)
```

---

<a id="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

**MKE_I2C_Loadcell** là thư viện Arduino mạnh mẽ và được tối ưu hóa cao để giao tiếp với mạch cân điện tử MKE I2C Loadcell (sử dụng chip PY32F030 và HX710B).
Thư viện này chuyển toàn bộ các tác vụ xử lý tín hiệu phức tạp (Lọc Kalman, Chống trôi Zero, Hiệu chuẩn) xuống mạch I2C, giúp tiết kiệm cực kỳ nhiều tài nguyên tính toán và bộ nhớ cho Arduino/ESP32 của bạn.

### 🌟 Tính năng nổi bật
- **Giao tiếp I2C tốc độ cao:** Không gây block (treo) vi điều khiển như các thư viện HX710B truyền thống.
- **Tích hợp bộ lọc Kalman:** Chuyển đổi linh hoạt giữa các chế độ Nhanh, Cân bằng và Chậm/Ổn định.
- **Lưu trữ EEPROM:** Mốc Trừ bì và Hệ số Hiệu chuẩn được lưu trực tiếp vào bộ nhớ trong của mạch.
- **Đếm số lượng (PCS):** Tích hợp sẵn thuật toán đếm số lượng vật thể giống nhau.
- **Đa đơn vị:** Lấy tức thời khối lượng theo Gram, Kilogram, Ounce, Pound hoặc Carat.
- **Đổi địa chỉ I2C:** Cho phép thay đổi địa chỉ phần cứng để kết nối lên tới 127 mạch Loadcell trên cùng một bus I2C!

### 🔌 Sơ đồ kết nối (Pinout)
| Chân Module MKE | Chân Arduino / ESP32 | Mô tả |
| :---: | :---: | :--- |
| **GND** | GND | Nối Đất |
| **VCC** | 5V hoặc 3.3V | Nguồn cấp (Phù hợp với điện áp giao tiếp của Vi điều khiển) |
| **SDA** | SDA (vd: A4 trên Uno) | Dữ liệu I2C |
| **SCL** | SCL (vd: A5 trên Uno) | Xung nhịp I2C |

### 🚀 Bắt đầu sử dụng
Vui lòng tham khảo các đoạn code mẫu trong thư mục `examples/`. Bạn nên chạy thử theo thứ tự sau:
1. **01_Read_Weight:** Đọc khối lượng cơ bản ra nhiều đơn vị khác nhau.
2. **02_Tare_and_Calibrate:** Trừ bì và hiệu chuẩn cân bằng một tạ chuẩn đã biết trước khối lượng.
3. **03_Piece_Counting:** Ứng dụng đếm số lượng hàng hoá (ốc vít, linh kiện).
4. **04_Raw_Data:** Đọc dữ liệu thô (ADC) để tự viết thuật toán vẽ biểu đồ, sửa lỗi.
5. **05_Advanced_Filter_Config:** Cấu hình bộ lọc Kalman.
6. **06_Module_Information:** Đọc thông tin phần cứng (Phiên bản Firmware, Địa chỉ I2C).
7. **07_Change_I2C_Address:** Công cụ quét và đổi địa chỉ I2C tự động.

### 📚 Tổng hợp các hàm cơ bản (API)
```cpp
MKE_I2C_Loadcell scale;

scale.begin();                  // Khởi tạo cân
scale.tare();                   // Trừ bì (Tự động lưu EEPROM)
scale.calibrate(500.0);         // Hiệu chuẩn với tạ 500g (Tự động lưu EEPROM)

float g  = scale.getGram();     // Lấy khối lượng (Gram)
float kg = scale.getKilogram(); // Lấy khối lượng (Kilogram)

scale.setFilterLevel(3);        // Chỉnh bộ lọc thành Chậm & Đầm (1=Nhanh, 2=Vừa, 3=Chậm)
```