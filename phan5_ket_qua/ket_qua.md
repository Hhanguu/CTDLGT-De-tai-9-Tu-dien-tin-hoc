# Phần 5 — Kết quả và đánh giá

## 5.1 Môi trường đo

| Thành phần | Giá trị |
|---|---|
| Hệ điều hành | Windows (win32) |
| Trình biên dịch | g++ 16.2.0 (MSYS2), chuẩn C++17 |
| Cờ tối ưu | `-O2` |
| Đồng hồ đo | `std::chrono::steady_clock` |
| Chương trình đo | `bench/benchmark.cpp` |
| Dữ liệu | N từ sinh ngẫu nhiên, seed cố định 42, chữ cái đầu phân bố đều a–z |

Lệnh chạy:

```bash
cd phan3_cai_dat
make bench
./benchmark 100000
```

Mỗi lần đo: thêm toàn bộ N từ, tra toàn bộ N từ (hit), tra N/10 từ không tồn tại (miss), xóa toàn bộ N từ, cuối cùng nạp lại file dữ liệu mẫu 29 từ.

## 5.2 Độ phức tạp

Gọi `k` là số node trong bucket đích, `N` là tổng số từ.

| Thao tác | Tốt nhất | Trung bình | Xấu nhất |
|---|---|---|---|
| Thêm | O(1) | O(k) ≈ O(N/26) | O(N) |
| Tra từ | O(1) | O(N/26) | O(N) |
| Xóa từ | O(1) | O(N/26) | O(N) |
| Sửa nghĩa/loại từ | O(1) | O(N/26) | O(N) |
| Hiển thị theo nhóm | O(k) | O(k) | O(N) |
| Hiển thị tất cả | O(N) | O(N) | O(N) |

Không gian: **O(N)** cho N node, cộng **O(1)** cho mảng 26 con trỏ bucket.

Do chữ cái đầu phân bố đều nên độ dài chuỗi trung bình xấp xỉ `N/26`:

| N | 1 000 | 10 000 | 100 000 |
|---|---|---|---|
| Chuỗi ngắn nhất | 25 | 337 | 3 700 |
| Chuỗi dài nhất | 53 | 413 | 3 922 |
| Chuỗi trung bình | 38,46 | 384,62 | 3 846,15 |

## 5.3 Kết quả benchmark

| N | Thêm (ms) | Thêm (ns/từ) | Tra hit (ms) | Tra hit (ns/từ) | Tra miss (ns/từ) | Xóa (ms) | Xóa (ns/từ) |
|---:|---:|---:|---:|---:|---:|---:|---:|
| 1 000 | 1,306 | 1 306,20 | 0,920 | 921,40 | 2 833,00 | 0,640 | 644,70 |
| 10 000 | 89,670 | 8 966,97 | 132,700 | 13 270,16 | 13 046,50 | 37,820 | 3 782,00 |
| 100 000 | 22 774,210 | 227 742,10 | 21 949,120 | 219 491,19 | 150 871,95 | 9 298,790 | 92 987,86 |

- Ở N = 100 000, phần tra miss đo trên 10 000 truy vấn; các mức N khác đo trên N/10 truy vấn.
- Không có truy vấn miss nào trả về nhầm kết quả (`Tim thay nham: 0`).
- Nạp file dữ liệu mẫu 29 từ: **0,21–0,36 ms** — không đáng kể.

## 5.4 Nhận xét

1. **Đúng lý thuyết O(k):** thời gian mỗi thao tác tăng theo độ dài chuỗi trong bucket; chuỗi trung bình đo được khớp với `N/26` (38,46 → 384,62 → 3 846,15).
2. **Tổng thời gian thêm N từ là O(N²/26):** mỗi lần thêm phải duyệt chuỗi dài dần, nên khi N tăng 10 lần thì tổng thời gian tăng hơn 10 lần (1,306 → 89,670 → 22 774,210 ms). Ở mức 100 000 từ còn chịu thêm chi phí cache/memory do danh sách kéo dài.
3. **Xóa nhanh hơn thêm/tra:** mỗi lần xóa làm chuỗi ngắn lại, nên độ dài trung bình trong suốt quá trình xóa chỉ còn khoảng một nửa so với ban đầu.
4. **Nút thắt là số bucket:** chỉ 26 bucket nên khi N lớn, mỗi bucket chứa hàng nghìn node. Đây là đánh đổi của thiết kế đề bài (26 bucket cố định), không phải lỗi cài đặt. Nếu mở rộng lên 676 bucket (2 chữ cái đầu), độ dài chuỗi giảm khoảng 26 lần.
5. **Tính đúng đắn:** đã kiểm tra thủ công các trường hợp thêm mới/trùng/khoá không hợp lệ, tra có–không/chuỗi rỗng, xóa đầu–giữa–cuối, sửa nghĩa/sửa loại từ/không có gì để sửa, hiển thị nhóm/hiển thị tất cả/bảng rỗng, đọc file CRLF và ghi–đọc lại (roundtrip). Tất cả đạt yêu cầu.

## 5.5 Hạn chế và hướng phát triển

- **Hạn chế:** 26 bucket cố định → chuỗi dài khi dữ liệu lớn; chưa hỗ trợ thay đổi khoá (đổi từ tiếng Anh) vì sẽ phải băm lại; dữ liệu lưu dạng text nên không phù hợp từ điển rất lớn.
- **Hướng phát triển:** mở rộng lên 676 bucket (2 chữ cái đầu) hoặc băm toàn chuỗi; thêm cơ chế rehash khi hệ số tải vượt ngưỡng; thêm tìm kiếm gần đúng (fuzzy); xây dựng giao diện đồ họa.
