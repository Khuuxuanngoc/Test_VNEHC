# 04 - Digital Wallet (Value Block)

🇻🇳 **Tiếng Việt**

## Giới thiệu
Example này mô phỏng một hệ thống "Ví Điện Tử" thu nhỏ (như vé xe bus, thẻ gửi xe trả trước, máy chơi game arcade). Nó sử dụng tính năng **Value Block** được hỗ trợ nguyên bản bằng phần cứng mã hoá của thẻ MIFARE Classic.

## Hướng dẫn sử dụng
1. Cắm MKE I2C RFID Module vào board Arduino/ESP32.
2. Mở Serial Monitor với baudrate **115200**.
3. Đặt một thẻ MIFARE Classic lên đầu đọc.
4. Hệ thống sẽ:
   - Kiểm tra xem Block 5 đã được định dạng làm Value Block chưa. Nếu chưa, nó sẽ khởi tạo số dư là `100,000 VND`.
   - Mô phỏng quẹt thẻ mua vé xe bus: Trừ `5,000 VND` khỏi thẻ bằng hàm `decrementValue()`.
   - Đọc lại số dư mới để xác nhận.
   - Nếu thẻ hết tiền, hệ thống tự động nạp lại `100,000 VND` bằng hàm `incrementValue()`.

## Lưu ý quan trọng
- **Tại sao phải dùng tính năng Increment/Decrement phần cứng thay vì tự cộng trừ trong code?**
  - Tránh mất tiền khi mất điện: Nếu bạn tự đọc giá trị, cộng trừ trong RAM, rồi thẻ bị rút ra đột ngột khi đang ghi lại vào thẻ, số dư sẽ bị hỏng hoàn toàn. 
  - An toàn tuyệt đối: Lệnh Increment/Decrement được xử lý khép kín bằng mạch mã hoá điện tử bên trong lõi chip của thẻ MIFARE, chống được hoàn toàn lỗi gián đoạn do rớt nguồn hoặc thẻ bị rút ra.

---

🇬🇧 **English**

## Introduction
This example simulates a mini "Digital Wallet" system (like a bus ticket, prepaid parking card, or arcade card). It utilizes the **Value Block** feature, which is natively supported by the hardware encryption logic of the MIFARE Classic card.

## Usage
1. Connect the MKE I2C RFID Module to your Arduino/ESP32 board.
2. Open the Serial Monitor with a baudrate of **115200**.
3. Place a MIFARE Classic card on the reader.
4. The system will:
   - Check if Block 5 is formatted as a Value Block. If not, it will initialize the balance to `100,000 VND`.
   - Simulate a bus ticket transaction: Deduct `5,000 VND` from the card using the `decrementValue()` function.
   - Read the new balance to confirm.
   - If the balance is insufficient, the system will auto-recharge `100,000 VND` using the `incrementValue()` function.

## Important Notes
- **Why use hardware Increment/Decrement instead of calculating in software?**
  - Prevents money loss during power failures: If you read the balance, calculate it in RAM, and the card is pulled away while writing it back, the data gets completely corrupted.
  - Absolute Safety: Increment/Decrement commands are processed atomically by the cryptographic logic gate inside the MIFARE card's chip, making it immune to sudden interruptions or drops in power.
