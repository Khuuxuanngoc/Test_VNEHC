# 08 - Compare UID

## 🇻🇳 Tiếng Việt
Ví dụ này hướng dẫn cách đọc mã UID (Unique Identifier) của thẻ RFID và so sánh nó với một mã UID cho trước để cấp quyền truy cập (Access Granted) hoặc từ chối (Access Denied). 

Đây là logic cơ bản nhất để làm các ứng dụng như cửa từ thông minh, điểm danh học sinh, hoặc khóa xe máy.

**Lưu ý:**
- Thay đổi biến `AUTHORIZED_UID` trong code thành mã Hex tương ứng với thẻ của bạn.
- Mở Serial Monitor ở tốc độ `115200` baud để xem kết quả.

## 🇬🇧 English
This example demonstrates how to read the UID (Unique Identifier) of an RFID card and compare it against a predefined UID to grant or deny access.

This is the foundational logic for applications like smart door locks, student attendance systems, or motorcycle anti-theft systems.

**Note:**
- Change the `AUTHORIZED_UID` variable in the code to match the Hex code of your specific card.
- Open the Serial Monitor at `115200` baud to see the results.
