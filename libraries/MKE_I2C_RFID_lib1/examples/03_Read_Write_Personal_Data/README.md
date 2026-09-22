# 03 - Read Write Personal Data

🇻🇳 **Tiếng Việt**

## Giới thiệu
Example này hướng dẫn người mới bắt đầu cách lưu trữ dữ liệu dạng văn bản (String) vào thẻ MIFARE Classic. Bằng cách chuyển đổi chuỗi ký tự thành mảng Byte, bạn có thể lưu tên, mã số sinh viên, hoặc biển số xe trực tiếp vào thẻ.

## Hướng dẫn sử dụng
1. Cắm MKE I2C RFID Module vào board Arduino/ESP32.
2. Mở Serial Monitor với baudrate **115200**.
3. Đặt một thẻ MIFARE Classic lên đầu đọc.
4. Hệ thống sẽ:
   - Đọc và in ra dữ liệu hiện tại của Block 4.
   - Ghi đè dòng chữ `"Hello MakerEdu!"` vào Block 4.
   - Đọc lại dữ liệu để xác nhận đã ghi thành công.

## Lưu ý quan trọng
- MIFARE Classic chỉ cho phép lưu tối đa **16 ký tự (16 bytes)** trên mỗi Block. Nếu chuỗi dài hơn, bạn phải chia nhỏ và ghi vào các Block tiếp theo.
- Hãy cẩn thận không ghi nhầm vào các Block chứa Mật khẩu (Trailer Block: 3, 7, 11...), nếu không thẻ sẽ bị khoá (Bricked) vĩnh viễn.

---

🇬🇧 **English**

## Introduction
This example demonstrates how beginners can store text data (Strings) into a MIFARE Classic card. By converting a String into a Byte array, you can save names, student IDs, or license plates directly onto the card.

## Usage
1. Connect the MKE I2C RFID Module to your Arduino/ESP32 board.
2. Open the Serial Monitor with a baudrate of **115200**.
3. Place a MIFARE Classic card on the reader.
4. The system will:
   - Read and print the current data in Block 4.
   - Overwrite Block 4 with the text `"Hello MakerEdu!"`.
   - Read the data back to confirm a successful write.

## Important Notes
- MIFARE Classic allows a maximum of **16 characters (16 bytes)** per block. If your string is longer, you must split it and write it across multiple blocks.
- Be careful not to accidentally write into the Password Blocks (Trailer Blocks: 3, 7, 11...), otherwise, the card may become Bricked.
