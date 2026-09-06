# 04 Raw Data Reading / Đọc Dữ Liệu Thô

> **⚠️ IMPORTANT:** You MUST call `Wire.begin();` inside your `setup()` function before initializing the Loadcell. Mạch yêu cầu khởi tạo I2C (`Wire.begin()`) trước khi sử dụng thư viện.


## 🇻🇳 Tiếng Việt
Dành cho người dùng nâng cao (Advanced Users) muốn xem trực tiếp các con số nhảy ra từ IC ADC 24-bit HX710B trước khi được chia cho hệ số Calibration.

**Ứng dụng thực tế của ví dụ này:**
*   **Kiểm tra phần cứng / Gỡ lỗi (Debug):** Phát hiện cảm biến bị nhiễu điện từ, nhiễu nguồn hoặc dây dẫn hỏng bằng cách xem giá trị thô có dao động quá mạnh hay không.
*   **Vẽ biểu đồ tín hiệu:** Kết hợp với Serial Plotter (Ctrl + Shift + L) trên Arduino IDE để phân tích phổ rung động cơ học của thiết bị.
*   **Viết thuật toán riêng:** Nếu bạn không muốn dùng bộ lọc Kalman có sẵn, bạn có thể tự thu thập Raw Data để thiết kế thuật toán lọc tín hiệu số (DSP) của riêng bạn.

**Cách sử dụng:**
1. Nạp code vào Arduino.
2. Mở Serial Plotter (`Tools` -> `Serial Plotter`).
3. Gõ nhẹ vào khung nhôm của Loadcell và quan sát sóng tín hiệu trên màn hình.

---

## 🇬🇧 English
Designed for Advanced Users who want to observe the direct output numbers from the 24-bit ADC HX710B IC before they are divided by the Calibration Factor.

**Practical Applications of this Example:**
*   **Hardware Check / Debugging:** Detect electromagnetic interference, power noise, or broken wires by observing if the raw values fluctuate wildly.
*   **Signal Plotting:** Combine with the Serial Plotter (Ctrl + Shift + L) in the Arduino IDE to analyze the mechanical vibration spectrum of your device.
*   **Custom Algorithms:** If you prefer not to use the built-in Kalman filter, you can gather Raw Data to design your own Digital Signal Processing (DSP) algorithms.

**Usage Instructions:**
1. Upload the code to your Arduino.
2. Open the Serial Plotter (`Tools` -> `Serial Plotter`).
3. Tap lightly on the Loadcell's aluminum frame and observe the signal waveforms on the screen.
