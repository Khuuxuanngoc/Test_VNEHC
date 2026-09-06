<details>
  <summary><b>PDF Export Style (Hidden on web)</b></summary>
  <style>
    @media print {
      @page {
        size: A4;
        margin: 16mm 15mm 16mm 15mm;
      }
      body {
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
        font-size: 13.5px;
        line-height: 1.55;
      }
      h1, h2, h3, h4 {
        page-break-after: avoid !important;
        break-after: avoid !important;
      }
      pre, code, table, blockquote {
        page-break-inside: avoid !important;
        break-inside: avoid !important;
      }
      tr {
        page-break-inside: avoid !important;
        page-break-after: auto;
      }
    }
    .page-break {
      page-break-after: always;
      break-after: page;
    }
  </style>
</details>

# Hướng Dẫn Sử Dụng Module VNEHC I2C Loadcell (HX710) - Dành Cho Nhà Sản Xuất

Tài liệu này cung cấp hướng dẫn chuyên sâu về việc thiết lập, tinh chỉnh và lập trình Module I2C Loadcell thông qua giao thức I2C và nút nhấn vật lý.

---

## Phần 1: Hướng Dẫn Sử Dụng Nút Nhấn (Setup Mode)

Module Loadcell được trang bị một nút nhấn (`S1`) để thao tác nhanh tại chỗ mà không cần thông qua I2C Master.

1. **Thao tác Trừ Bì (Tare / Zeroing):**
   - **Thao tác:** Bấm 1 lần (Click).
   - **Phản hồi:** Hệ thống sẽ chờ khoảng 1 giây (để chống rung cơ học do lực nhấn tay), sau đó sẽ lưu mốc 0 mới (Tare).

2. **Khôi phục Cài Đặt Gốc (Factory Reset):**
   - **Thao tác:** Nhấn và giữ nút `S1` trong khoảng thời gian lớn hơn 3 giây.
   - **Phản hồi:** Module sẽ trực tiếp xóa trắng các cấu hình EEPROM (bao gồm hệ số Scale, màng lọc Kalman) và ép địa chỉ I2C trở về mặc định là `0x0A`. Hệ thống thực hiện nạp lại cấu hình màng lọc (Soft Reload) một cách an toàn mà không bị treo MCU.

---

## Phần 2: Hướng Dẫn Giao Thức I2C (Dành Cho Lập Trình Viên)

Module giao tiếp với Vi điều khiển chính (Master) qua I2C. Địa chỉ mặc định là **`0x0A`**.

### 2.1. Cấu Trúc Gói Tin (Packet)
Giao thức I2C sử dụng cấu trúc Header chung: `[AddressId(1 byte)] [ModeId(1 byte)] [Value32(4 bytes)]`
- **Master Ghi lệnh:** Gửi qua I2C các lệnh theo `ModeId` và truyền kèm `Value` 32-bit (Big Endian).
- **Master Đọc dữ liệu:** Gửi `ModeId` cần đọc, trễ 1 khoảng nhỏ (VD: 10ms), sau đó dùng lệnh `Wire.requestFrom` để nhận về 4 bytes giá trị.

> [!WARNING]
> Các cấu hình thay đổi hệ thống (như thay đổi địa chỉ I2C, cập nhật tham số EEPROM) đòi hỏi Master phải mở khóa quyền Admin (gửi Password `0x12345678` vào `ModeId` `0xC8`) trước khi thực hiện.

### 2.2. Nhóm Lệnh Hệ Thống (Core Commands)
Các lệnh dùng chung cho việc quản lý thông tin hệ thống (Mode ID dạng HEX).

| Mode ID | Tên Lệnh | Chức Năng | Value 32-bit (Hex) |
| :---: | :--- | :--- | :--- |
| **`0x01`** | `SET_ADDRESS` | Cài đặt địa chỉ I2C mới (Cần Admin Mode) | Địa chỉ mới (VD: `0x0B`) |
| **`0x02`** | `GET_ID_MODULE` | Đọc mã định danh của Module | Trả về ID của Loadcell |
| **`0x04`** | `GET_FW_VERSION`| Đọc phiên bản Firmware | Trả về Version |
| **`0x06`** | `GET_PRODUCT_CODE`| Đọc mã sản phẩm | Trả về Product Code |
| **`0x0A`** | `GET_ADDRESS` | Đọc địa chỉ I2C hiện tại | Trả về địa chỉ đang dùng |
| **`0xC8`** | `UNLOCK_ADMIN` | Mở/Khóa quyền Admin | Gửi `0x12345678` để mở khóa |
| **`0xC9`** | `GET_ADMIN_MODE`| Kiểm tra trạng thái Admin | `0x01` (Đã mở), `0x00` (Khóa) |

### 2.3. Nhóm Lệnh Điều Khiển Loadcell (Loadcell Commands)
Dùng để hiệu chuẩn, trừ bì, điều chỉnh bộ lọc Kalman và cấu hình EEPROM.

| Mode ID | Tên Lệnh | Ý Nghĩa | Value (Cần truyền) |
| :---: | :--- | :--- | :--- |
| **`0x32`** | `GET_RAW_VALUE` | Đọc giá trị ADC thô từ HX710 | Không cần truyền (`0x00`) |
| **`0x33`** | `TARE` | Lệnh trừ bì bằng phần mềm | `0x00` |
| **`0x34`** | `GET_GRAM` | Đọc khối lượng (gram) dạng Float (32-bit) | `0x00` |
| **`0x35`** | `CALIBRATE` | Hiệu chuẩn cân (Cần Admin Mode) | Khối lượng vật mẫu (Float -> uint32_t) |
| **`0x36`** | `GET_SCALE` | Đọc hệ số chia Scale hiện hành | Trả về Float (32-bit) |
| **`0x37`** | `SET_SCALE` | Đặt hệ số chia Scale thủ công | Giá trị Scale (Float -> uint32_t) |
| **`0x3A`** | `GET_FILTER_LEVEL`| Đọc mức độ màng lọc (Filter Level) | Trả về `0x00` đến `0x03` |
| **`0x3B`** | `SET_FILTER_LEVEL`| Cài đặt mức độ lọc (0: Raw, 1: Fast, 2: Medium, 3: Slow) | `0x00`, `0x01`, `0x02`, `0x03` |
| **`0x3C`** | `GET_KALMAN_MEA` | Đọc sai số đo lường (Mea_e) | Float 32-bit |
| **`0x3D`** | `SET_KALMAN_MEA` | Ghi sai số đo lường (Mea_e) | Float 32-bit (ép kiểu) |
| **`0x3E`** | `GET_KALMAN_EST` | Đọc sai số ước lượng (Est_e)| Float 32-bit |
| **`0x3F`** | `SET_KALMAN_EST` | Ghi sai số ước lượng (Est_e)| Float 32-bit (ép kiểu) |
| **`0x40`** | `GET_KALMAN_Q` | Đọc nhiễu hệ thống (Q) | Float 32-bit |
| **`0x41`** | `SET_KALMAN_Q` | Ghi nhiễu hệ thống (Q) | Float 32-bit (ép kiểu) |
| **`0x44`** | `GET_LOADCELL_TYPE`| Đọc loại Loadcell (1Kg, 5Kg...) | Trả về Enum Type |
| **`0x45`** | `SET_LOADCELL_TYPE`| Cài đặt loại Loadcell | Ghi Enum Type (0 đến 5) |

> [!TIP]
> **Xử Lý Số Thực (Float 32-bit):** Do I2C truyền nhận số nguyên, các tham số như Gram, Scale, hay thông số Kalman (Mea, Est, Q) cần được ép kiểu từ bộ nhớ `Float` sang `uint32_t` trước khi truyền, và ép kiểu ngược lại sau khi nhận (Sử dụng kỹ thuật Union hoặc Cast Pointer).
> 
> **Sử Dụng Thư Viện Arduino:** Nếu đang nạp test tại nhà máy bằng Arduino, bạn không cần phải dùng Raw I2C. Hãy include file `#include "MKE_I2C_Loadcell_Advanced.h"` và sử dụng class `MKE_I2C_Loadcell_Advanced` để gọi trực tiếp các hàm cấu hình nâng cao.

### 2.4. Code Arduino Master Mẫu (Raw I2C)

```cpp
#include <Wire.h>

#define LOADCELL_I2C_ADDR 0x0A

// Hàm Ghi: Gửi lệnh I2C
void sendI2CCommand(uint8_t address, uint8_t modeId, uint32_t value) {
  Wire.beginTransmission(address);
  Wire.write(address);
  Wire.write(modeId);
  Wire.write((uint8_t)(value >> 24));
  Wire.write((uint8_t)(value >> 16));
  Wire.write((uint8_t)(value >> 8));
  Wire.write((uint8_t)(value & 0xFF));
  Wire.endTransmission();
}

// Hàm Đọc: Lấy dữ liệu 32-bit
uint32_t readI2CValue(uint8_t address, uint8_t modeId) {
  sendI2CCommand(address, modeId, 0x00);
  delay(10); 
  Wire.requestFrom(address, (uint8_t)4);
  uint32_t result = 0;
  if (Wire.available() >= 4) {
    result |= ((uint32_t)Wire.read() << 24);
    result |= ((uint32_t)Wire.read() << 16);
    result |= ((uint32_t)Wire.read() << 8);
    result |= ((uint32_t)Wire.read());
  }
  return result;
}

// Hàm chuyển đổi dữ liệu Float
float uint32ToFloat(uint32_t val) {
  float f;
  memcpy(&f, &val, 4);
  return f;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  
  // Trừ bì (Tare)
  Serial.println("Thuc hien Tare...");
  sendI2CCommand(LOADCELL_I2C_ADDR, 0x33, 0x00);
  delay(100);
}

void loop() {
  // Đọc khối lượng
  uint32_t rawGram = readI2CValue(LOADCELL_I2C_ADDR, 0x34);
  float gram = uint32ToFloat(rawGram);
  
  Serial.print("Weight (g): ");
  Serial.println(gram);
  delay(500);
}
```
