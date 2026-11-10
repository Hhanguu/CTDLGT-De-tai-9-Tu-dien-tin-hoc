# Phần 1 — Phân tích bài toán

## 1.1 Mô tả bài toán

Xây dựng chương trình từ điển Anh–Việt chuyên ngành tin học sử dụng:
- **Bảng băm (Hash Table)** với 26 bucket, khoá là chữ cái đầu của từ tiếng Anh
- **Danh sách liên kết đơn (Singly Linked List)** để xử lý đụng độ (chaining)

## 1.2 Yêu cầu chức năng

| STT | Chức năng | Mô tả |
|---|---|---|
| 1 | Thêm từ | Nhập từ tiếng Anh, nghĩa tiếng Việt, loại từ |
| 2 | Tra từ | Tìm kiếm theo từ tiếng Anh, hiển thị nghĩa |
| 3 | Hiển thị theo nhóm | Liệt kê tất cả từ bắt đầu bằng một chữ cái |
| 4 | Hiển thị tất cả | Liệt kê toàn bộ từ điển theo thứ tự alphabet |
| 5 | Xóa từ | Xóa một từ khỏi từ điển |
| 6 | Sửa nghĩa | Cập nhật nghĩa tiếng Việt và/hoặc loại từ |

## 1.3 Yêu cầu phi chức năng

- Lưu trữ từ điển ra file TXT, tải lại khi khởi động
- Định dạng file: `tieng_anh|tieng_viet|loai_tu` mỗi dòng
- Mã hóa UTF-8, hỗ trợ tiếng Việt có dấu
- Không dùng `std::unordered_map` hay thư viện băm có sẵn

## 1.4 Ràng buộc

- Ngôn ngữ: C++17
- Không dùng STL container (vector, map, list) cho cấu trúc chính
- 26 bucket cố định ứng với 26 chữ cái a–z
