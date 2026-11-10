# Đề tài 9 — Từ điển Tin học (English–Vietnamese)

**Môn:** Cấu trúc dữ liệu và Giải thuật  
**Đề tài:** Từ điển tin học (Hash Table + Linked List)  
**Nhóm:** 2 người

## Cấu trúc thư mục

| Thư mục | Nội dung |
|---|---|
| `phan1_phan_tich/` | Phân tích bài toán, yêu cầu chức năng |
| `phan2_thiet_ke/` | Thiết kế cấu trúc dữ liệu, giải thuật, sơ đồ |
| `phan3_cai_dat/` | Source code C++ (src/, include/, data/) |
| `phan4_thu_nghiem/` | Kết quả chạy thử, test case |
| `phan5_ket_qua/` | Đánh giá kết quả, độ phức tạp |
| `phan6_phan_cong/` | Bảng phân công nhiệm vụ từng thành viên |
| `phan7_tai_lieu/` | Tài liệu tham khảo |
| `phan8_ket_luan/` | Kết luận, hướng phát triển |
| `bao_cao/` | File báo cáo Word/PDF hoàn chỉnh |

## Build và chạy

```bash
cd phan3_cai_dat
g++ -std=c++17 -Wall src/*.cpp -o tudien
./tudien
```

## Chức năng yêu cầu

1. Thêm từ mới
2. Tra từ (tìm kiếm theo từ tiếng Anh)
3. Hiển thị theo nhóm chữ cái
4. Hiển thị tất cả từ
5. Xóa từ
6. Sửa nghĩa từ
