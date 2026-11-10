# Đề tài 9 — Từ điển Tin học (English–Vietnamese)

**Môn:** Cấu trúc dữ liệu và Giải thuật  
**Đề tài:** Từ điển tin học (Hash Table + Linked List)  
**Nhóm:** 2 người

## Build và chạy

```bash
cd phan3_cai_dat
make
./tudien
```

## Cấu trúc source code

```
phan3_cai_dat/
├── Makefile
├── include/
│   ├── Entry.h       // Cấu trúc node (từ + nghĩa + loại từ + con trỏ next)
│   ├── HashTable.h   // Bảng băm 26 bucket + linked list chaining
│   ├── FileIO.h      // Đọc/ghi file TXT
│   └── Menu.h        // Menu tương tác
├── src/
│   ├── main.cpp      // TODO: implement
│   ├── HashTable.cpp // TODO: implement
│   ├── FileIO.cpp    // TODO: implement
│   └── Menu.cpp      // TODO: implement
└── data/
    └── tudien.txt    // Dữ liệu mẫu (29 từ)
```

## Chức năng yêu cầu

1. Thêm từ mới
2. Tra từ (tìm kiếm theo từ tiếng Anh)
3. Hiển thị theo nhóm chữ cái
4. Hiển thị tất cả từ
5. Xóa từ
6. Sửa nghĩa từ
