# Đề tài 9 — Từ điển Tin học (English–Vietnamese)

**Môn:** Cấu trúc dữ liệu và Giải thuật  
**Đề tài:** Từ điển tin học (Hash Table + Linked List)  
**Nhóm:** 2 người

---

## 🚀 Quick Start

### Build và chạy phiên bản cơ bản (29 từ)
```bash
cd phan3_cai_dat
make
./tudien
```

### Build và chạy phiên bản test 1000 từ
```bash
cd phan3_cai_dat
make
./tudien_1000
```

### Đo hiệu năng
```bash
cd phan3_cai_dat
make bench
./benchmark 1000    # Test với 1000 từ ngẫu nhiên
./benchmark 100000  # Test với 100000 từ ngẫu nhiên
```

---

## 📋 Chức năng đầy đủ (6/6)

| # | Chức năng | Case-insensitive | Auto-save |
|---|-----------|------------------|-----------|
| 1 | **Thêm từ mới** (add) | ✅ | ✅ |
| 2 | **Tra từ** (search) | ✅ | - |
| 3 | **Hiển thị theo nhóm** (displayGroup) | - | - |
| 4 | **Hiển thị tất cả** (displayAll) | - | - |
| 5 | **Xóa từ** (remove) | ✅ | ✅ |
| 6 | **Sửa nghĩa/loại từ** (edit) | ✅ | ✅ |

### Menu terminal
```
===== TU DIEN TIN HOC (26 bucket + linked list) =====
1. Them tu (add)
2. Tra tu (search)
3. Hien thi nhom chu cai (displayGroup)
4. Hien thi tat ca (displayAll)
5. Xoa tu (remove)
6. Sua nghia/loai tu (edit)
0. Thoat
```

---

## 📊 Kết quả benchmark

### Test với 1000 từ

| Thao tác | Tổng | TB/từ | Ghi chú |
|----------|------|-------|---------|
| Add | 0.375 ms | 375 ns | 1000 từ → bảng rỗng |
| Search (hit) | 0.26 ms | 258 ns | Tìm 1000 từ có sẵn |
| Search (miss) | 0.04 ms | 352 ns | Tìm 100 từ không tồn tại |
| Remove | 0.17 ms | 172 ns | Xóa 1000 từ |

**Phân bố bucket:**
- Bucket có dữ liệu: 26/26 (100%)
- Chuỗi ngắn nhất: 25 từ
- Chuỗi dài nhất: 53 từ  
- Chuỗi trung bình: **38.46 từ** (≈ N/26)

---

## 🏗️ Cấu trúc source code

```
CTDLGT-De-tai-9-Tu-dien-tin-hoc/
├── README.md
├── HUONG_DAN_SU_DUNG.md         ← Hướng dẫn chi tiết
├── phan2_thiet_ke/
│   └── thiet_ke.md              ← Phần 2: Thiết kế (244 dòng)
├── phan3_cai_dat/
│   ├── Makefile
│   ├── tudien                   ← Binary 29 từ
│   ├── tudien_1000              ← Binary 1000 từ
│   ├── benchmark                ← Binary benchmark
│   ├── include/
│   │   ├── Entry.h              # Node: từ + nghĩa + loại từ + next
│   │   ├── HashTable.h          # 26 bucket + chaining
│   │   ├── FileIO.h             # Đọc/ghi file + CRLF support
│   │   └── Menu.h               # Menu 6 chức năng
│   ├── src/
│   │   ├── main.cpp             # Main 29 từ
│   │   ├── main_1000.cpp        # Main 1000 từ
│   │   ├── HashTable.cpp        # Logic hash table + case-insensitive
│   │   ├── FileIO.cpp           # Logic file I/O + trim
│   │   └── Menu.cpp             # 6 chức năng + auto-save
│   ├── bench/
│   │   └── benchmark.cpp        # Đo hiệu năng add/search/remove
│   └── data/
│       ├── tudien.txt           # 29 từ mẫu
│       └── tudien_1000.txt      # 922 từ test (A-Z)
└── phan5_ket_qua/
    └── ket_qua.md               ← Phần 5: Kết quả (70 dòng)
```

---

## ✨ Tính năng nổi bật

### ✅ Case-insensitive comparison
```cpp
"algorithm" == "Algorithm" == "ALGORITHM" == "AlGoRiThM"
```

### ✅ Tự động sắp xếp alphabet
Trong mỗi bucket, từ được chèn theo thứ tự alphabet:
```
Bucket 'C': cache → callback → class → compiler → cpu
```

### ✅ Hỗ trợ CRLF (Windows/Linux)
- Tự động trim `\r\n` và khoảng trắng
- Đọc file từ Windows hoặc Linux đều OK

### ✅ Không trùng lặp
- Kiểm tra trùng với case-insensitive
- Từ `Algorithm` và `algorithm` coi là trùng

### ✅ Auto-save
- Sau mỗi lần add/remove/edit, file tự động lưu

---

## 📐 Độ phức tạp

| Thao tác | Tốt nhất | Trung bình | Xấu nhất |
|----------|----------|------------|----------|
| add | O(1) | O(N/26) | O(N) |
| search | O(1) | O(N/26) | O(N) |
| remove | O(1) | O(N/26) | O(N) |
| edit | O(1) | O(N/26) | O(N) |
| displayGroup | O(k) | O(k) | O(N) |
| displayAll | O(N) | O(N) | O(N) |

**Ghi chú:** 
- N = tổng số từ
- k = số từ trong bucket
- Với N = 1000, độ dài chuỗi ≈ 38 → rất nhanh

---

## 📚 Tài liệu

- **[HUONG_DAN_SU_DUNG.md](HUONG_DAN_SU_DUNG.md)** - Hướng dẫn chi tiết từng chức năng
- **[phan2_thiet_ke/thiet_ke.md](phan2_thiet_ke/thiet_ke.md)** - Phần 2: Thiết kế
- **[phan5_ket_qua/ket_qua.md](phan5_ket_qua/ket_qua.md)** - Phần 5: Kết quả benchmark

---

## 🧪 Test

### Test tự động
```bash
cd phan3_cai_dat
./test_1000.sh
```

### Test thủ công
```bash
# Test case-insensitive
echo -e "2\nalgorithm\n2\nALGORITHM\n0" | ./tudien_1000

# Test hiển thị nhóm
echo -e "3\nc\n0" | ./tudien_1000

# Test thêm và xóa
echo -e "1\ntestword\ntest nghia\nnoun\n2\ntestword\n5\ntestword\n0" | ./tudien_1000
```

---

## ⚡ Performance

Với **922 từ** trong file `tudien_1000.txt`:
- Load từ file: < 1ms
- Tra 1 từ: ~258 nanoseconds
- Thêm 1 từ: ~375 nanoseconds
- Xóa 1 từ: ~172 nanoseconds

**Kết luận:** Hiệu năng tuyệt vời cho ứng dụng terminal!

---

## 🎯 Trạng thái hoàn thành

- ✅ Phần 2: Thiết kế (244 dòng)
- ✅ Phần 3: Cài đặt (6/6 chức năng)
- ✅ Phần 5: Kết quả (70 dòng)
- ✅ Menu terminal đầy đủ
- ✅ Test với 1000 từ
- ✅ Benchmark tool
- ✅ Case-insensitive
- ✅ CRLF support
- ✅ Auto-save
- ✅ Tài liệu đầy đủ

**🎓 Sẵn sàng nộp bài!**
