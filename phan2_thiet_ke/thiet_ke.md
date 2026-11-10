# Phần 2 — Thiết kế cấu trúc dữ liệu và giải thuật

## 2.1 Cấu trúc Node (phần tử danh sách liên kết)

```cpp
struct Entry {
    std::string english;   // từ tiếng Anh (khoá)
    std::string vietnamese; // nghĩa tiếng Việt
    std::string pos;       // loại từ: noun, verb, adj, ...
    Entry* next;           // con trỏ đến phần tử kế tiếp
};
```

## 2.2 Cấu trúc bảng băm

```cpp
struct HashTable {
    Entry* buckets[26];    // 26 bucket ứng với a–z
    int size;              // tổng số từ
};
```

## 2.3 Hàm băm

```
h(key) = tolower(key[0]) - 'a'   // index 0–25
```

Ví dụ: `"algorithm"` → `h = 'a' - 'a' = 0` → bucket[0]

## 2.4 Giải thuật các thao tác

### Thêm từ — O(n) trong bucket
1. Tính `h = hash(english)`
2. Duyệt bucket[h], nếu đã tồn tại → thông báo trùng
3. Tạo node mới, chèn vào đúng vị trí (sắp xếp alphabet)

### Tra từ — O(n) trong bucket, trung bình O(1)
1. Tính `h = hash(english)`
2. Duyệt bucket[h], so sánh chuỗi không phân biệt hoa/thường
3. Tìm thấy → trả về Entry; không thấy → null

### Xóa từ — O(n) trong bucket
1. Tính `h = hash(english)`
2. Duyệt bucket[h], tìm node cần xóa
3. Cập nhật con trỏ prev->next, giải phóng bộ nhớ

### Hiển thị theo nhóm — O(n_bucket)
1. Tính `h = hash(chữ_cái)`
2. Duyệt toàn bộ bucket[h], in ra màn hình

### Hiển thị tất cả — O(N)
1. Duyệt bucket[0] đến bucket[25]
2. In từng node trong mỗi bucket

### Sửa nghĩa — O(n) trong bucket
1. Tra từ như thao tác tìm kiếm
2. Cập nhật trường `vietnamese` và/hoặc `pos`

## 2.5 Sơ đồ bộ nhớ

```
buckets[0] → [algorithm|thuật toán|noun] → [api|giao diện lập trình|noun] → null
buckets[1] → [bit|bit|noun] → [boolean|luận lý|adj] → null
buckets[2] → [cache|bộ đệm|noun] → null
...
buckets[25] → null
```

## 2.6 Định dạng file lưu trữ

```
algorithm|thuật toán|noun
api|giao diện lập trình|noun
bit|bit|noun
boolean|luận lý|adj
cache|bộ đệm|noun
```
