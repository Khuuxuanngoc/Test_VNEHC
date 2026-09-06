# 05 Advanced Filter Config / Cấu Hình Bộ Lọc

> **⚠️ IMPORTANT:** You MUST call `Wire.begin();` inside your `setup()` function before initializing the Loadcell. Mạch yêu cầu khởi tạo I2C (`Wire.begin()`) trước khi sử dụng thư viện.


## 🇻🇳 Tiếng Việt
Ví dụ này dành cho những dự án yêu cầu khả năng chống nhiễu chuyên sâu, giúp ổn định số đo trên các mâm cân tải trọng lớn.

**Các tính năng nổi bật trong ví dụ:**
*   **Filter Level (Cấp độ lọc Kalman):** Chuyển đổi giữa các chế độ: `1` (Nhanh/Nhạy), `2` (Cân bằng), `3` (Chậm/Siêu Ổn Định). Cấu hình này sẽ tự động thay đổi các thuật toán lọc số bên trong mạch để phù hợp với tốc độ cập nhật của bạn.

**Cách sử dụng:**
1. Nạp code vào mạch Arduino.
2. Mở Serial Monitor. Mạch sẽ tự động lưu Filter Level vào EEPROM bên trong mạch I2C.
3. Nếu dùng tay ấn mạnh, số sẽ lên rất đầm và êm (do dùng Level 3 - Chậm). Bạn có thể thử sửa số `3` thành số `1` trong code rồi nạp lại để thấy sự khác biệt về độ phản hồi.

---

## 🇬🇧 English
This example is for projects that require advanced noise suppression, helping to stabilize readings on high-capacity loadcells.

**Key Features in this Example:**
*   **Filter Level (Kalman Filter Level):** Switch between modes: `1` (Fast/Sensitive), `2` (Balanced), `3` (Slow/Super Stable). This configuration automatically changes the internal digital filtering algorithms to suit your update rate.

**How to Use:**
1. Upload the code to your Arduino.
2. Open the Serial Monitor. The module will automatically save the Filter Level to its internal EEPROM.
3. Press firmly on the scale. The weight will increase smoothly and stably (because of Level 3 - Slow). You can try changing the `3` to `1` in the code and re-uploading to see the difference in responsiveness.
