# Phần 4 — Thử nghiệm

## 4.1 Test case thêm từ

| Input | Kết quả mong đợi |
|---|---|
| `add("algorithm", "thuật toán", "noun")` | Thêm thành công |
| `add("algorithm", "...", "...")` | Từ đã tồn tại |
| `add("123abc", "...", "...")` | Khoá không hợp lệ |

## 4.2 Test case tra từ

| Input | Kết quả mong đợi |
|---|---|
| `search("cache")` | Trả về Entry: cache \| bộ nhớ đệm \| noun |
| `search("xyz123")` | nullptr |

## 4.3 Test case xóa từ

| Input | Kết quả mong đợi |
|---|---|
| `remove("bit")` | Xóa thành công, size giảm 1 |
| `remove("notexist")` | false |

## 4.4 Kết quả chạy thử

*(Chụp màn hình chạy chương trình điền vào đây)*
