# Phần 5 — Đánh giá kết quả

## 5.1 Độ phức tạp thời gian

| Thao tác | Trường hợp tốt nhất | Trung bình | Xấu nhất |
|---|---|---|---|
| Thêm | O(1) | O(n/26) | O(n) |
| Tra từ | O(1) | O(n/26) | O(n) |
| Xóa | O(1) | O(n/26) | O(n) |
| Hiển thị nhóm | O(n_bucket) | O(n_bucket) | O(n) |
| Hiển thị tất cả | O(N) | O(N) | O(N) |

*n = số từ trong bucket, N = tổng số từ*

## 5.2 Độ phức tạp không gian

- O(N) cho N từ lưu trong bảng băm
- O(1) overhead cho mảng 26 con trỏ

## 5.3 Nhận xét

*(Điền sau khi chạy thử và đo đạc)*
