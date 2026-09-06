# 02 Tare and Calibrate / Trừ bì và Hiệu chuẩn

> **⚠️ IMPORTANT:** You MUST call `Wire.begin();` inside your `setup()` function before initializing the Loadcell. Mạch yêu cầu khởi tạo I2C (`Wire.begin()`) trước khi sử dụng thư viện.


## 🇻🇳 Tiếng Việt
Hướng dẫn cách thiết lập mốc 0 (Trừ bì - Tare) và tinh chỉnh độ chính xác (Hiệu chuẩn - Calibrate) cho cảm biến Loadcell của bạn.

**Các tính năng nổi bật trong ví dụ:**
*   **Tare (Trừ bì):** Đưa giá trị đo hiện tại về `0g`, loại bỏ khối lượng của đĩa cân hoặc khay chứa.
*   **Calibrate (Hiệu chuẩn):** Tính toán hệ số tỷ lệ (Scale Factor) bằng một tạ chuẩn đã biết trước khối lượng. Hệ số mới sẽ được tự động lưu vào bộ nhớ EEPROM bên trong mạch I2C (không bị mất khi tắt điện).

**Cách sử dụng:**
1. Khai báo biến `REFERENCE_WEIGHT_GRAM` trong code khớp với khối lượng quả tạ thực tế bạn đang có (Nên dùng tạ nặng từ 10% đến 50% tải trọng tối đa của cảm biến).
2. Nạp code và mở Serial Monitor (Baudrate: `115200`).
3. Gõ phím `t` hoặc `T` vào khung nhập liệu rồi nhấn Enter để **Trừ bì**.
4. Đặt quả tạ chuẩn lên bàn cân. Gõ phím `c` hoặc `C` rồi nhấn Enter để **Hiệu chuẩn**. 

---

## 🇬🇧 English
A guide on how to set the zero point (Tare) and adjust accuracy (Calibrate) for your Loadcell sensor.

**Key Features in this Example:**
*   **Tare:** Resets the current measured value to `0g`, removing the weight of the weighing pan or container.
*   **Calibrate:** Calculates the Scale Factor using a standard weight of known mass. The new scale factor is automatically saved to the EEPROM inside the I2C module (retained after power off).

**Usage Instructions:**
1. Declare the `REFERENCE_WEIGHT_GRAM` variable in the code to match the actual weight of your standard calibration weight (Recommended: 10% to 50% of the sensor's max capacity).
2. Upload the code and open the Serial Monitor (Baudrate: `115200`).
3. Type `t` or `T` in the input field and press Enter to **Tare**.
4. Place the standard calibration weight on the scale. Type `c` or `C` and press Enter to **Calibrate**.
