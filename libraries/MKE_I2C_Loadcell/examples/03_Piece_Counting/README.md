# 03 Piece Counting / Đếm Số Lượng Sản Phẩm

> **⚠️ IMPORTANT:** You MUST call `Wire.begin();` inside your `setup()` function before initializing the Loadcell. Mạch yêu cầu khởi tạo I2C (`Wire.begin()`) trước khi sử dụng thư viện.


## 🇻🇳 Tiếng Việt
Ví dụ minh họa ứng dụng PCS (Piece Counting System). Thay vì chỉ hiển thị khối lượng, tính năng này giúp bạn đếm nhanh số lượng các vật thể có khối lượng bằng nhau (ví dụ: đếm linh kiện điện tử, ốc vít, hạt cà phê, viên thuốc...).

**Các tính năng nổi bật trong ví dụ:**
*   Thiết lập khối lượng tham chiếu cho 1 đơn vị sản phẩm (`setPieceWeight()`).
*   Tự động tính toán tổng số lượng vật thể đang nằm trên bàn cân (`getPCS()`).
*   **Auto Refine (Tự động tinh chỉnh):** Cập nhật lại khối lượng mẫu chính xác hơn khi có nhiều vật thể trên bàn cân.

**Cách sử dụng:**
1. Lấy một số lượng mẫu thực tế (ví dụ: đếm tay 10 con ốc) rồi đặt lên cân để xác định tổng khối lượng của mẫu này (bạn có thể đo qua ví dụ `01_Read_Weight`).
2. Sửa lại biến `SAMPLE_TOTAL_WEIGHT_GRAM` thành tổng khối lượng bạn vừa đo.
3. Sửa lại biến `SAMPLE_QUANTITY` thành số lượng vật mẫu (ở ví dụ này là 10).
4. Nạp code và mở Serial Monitor (Baudrate `115200`). Chương trình sẽ tự tính khối lượng 1 vật dựa trên mẫu của bạn.
5. Đổ ốc vít / linh kiện vào, màn hình sẽ hiển thị chính xác số lượng.
6. **Mẹo tăng độ chính xác:** Để đếm số lượng lớn, bạn không nên đổ ngay hàng trăm con vào. Hãy dùng kỹ thuật **tăng dần (gấp đôi)**:
    - Từ mẫu 10 con ban đầu, hãy đổ thêm khoảng 10 con (tổng ~20 con). Lúc này sai số rất nhỏ nên màn hình chắc chắn hiển thị đúng 20 con.
    - **Chờ 1-2 giây** cho số trên màn hình thật sự ổn định, rồi nhấn `u` hoặc `U`. Cân sẽ tự động chia lại trọng lượng trung bình chuẩn xác hơn.
    - Tiếp tục đổ thêm khoảng 20 con (tổng ~40 con), chờ ổn định rồi nhấn `u`.
    - Lặp lại quá trình này (80, 160...), bạn có thể đếm hàng ngàn linh kiện với độ chính xác tuyệt đối mà không bao giờ sợ màn hình bị nhảy sai số!

---

## 🇬🇧 English
An example illustrating the PCS (Piece Counting System) application. Instead of just displaying weight, this feature helps you quickly count items of identical weight (e.g., counting electronic components, screws, coffee beans, pills...).

**Key Features in this Example:**
*   Sets the reference weight for a single unit (`setPieceWeight()`).
*   Automatically calculates the total number of items currently on the scale (`getPCS()`).
*   **Auto Refine:** Dynamically updates the unit weight for higher accuracy when more items are placed on the scale.

**Usage Instructions:**
1. Take an actual sample quantity (e.g., manually count out 10 screws) and weigh them to find the total sample weight (you can measure this via the `01_Read_Weight` example).
2. Modify the `SAMPLE_TOTAL_WEIGHT_GRAM` variable to the total weight you just measured.
3. Modify the `SAMPLE_QUANTITY` variable to match the number of items in your sample (e.g., 10).
4. Upload the code and open the Serial Monitor (Baudrate `115200`). The program will automatically calculate the unit weight based on your sample.
5. Pour the screws/components into the tray, and the monitor will display the exact quantity.
6. **Pro Tip for High Accuracy:** When counting large quantities, do not pour hundreds of items at once. Use the **doubling method**:
    - Starting from your initial 10-piece sample, add about 10 more (total ~20 pieces). Because the quantity only doubled, the scale will perfectly round and display exactly 20 pieces.
    - **Wait 1-2 seconds** for the reading to fully stabilize, then type `u` or `U`. The scale will recalculate a much more accurate average unit weight.
    - Add about 20 more (total ~40 pieces), wait for stability, and press `u`.
    - Repeat this process (80, 160...). You will be able to count thousands of components with perfect accuracy without the reading ever drifting into errors!
