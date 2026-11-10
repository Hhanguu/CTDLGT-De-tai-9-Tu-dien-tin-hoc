# Ý tưởng giải thuật cho 3 chức năng (add / search / displayGroup)

## Giả thiết bài toán
- **Bảng băm cố định 26 bucket** tương ứng chữ cái đầu **a–z** của từ tiếng Anh.
- Mỗi bucket là **danh sách liên kết đơn (chaining)**.
- Trong cùng 1 bucket, các node được **chèn theo thứ tự alphabet** theo `english`.

---

## 1) Thêm từ mới — `add(english, vietnamese, pos)`

### Bước 1: Băm khoá
- Lấy `c = tolower(english[0])`.
- Nếu `c` không thuộc `a..z` ⇒ từ khoá không hợp lệ.
- `index = c - 'a'` ⇒ chọn bucket.

### Bước 2: Kiểm tra trùng trong bucket
- Duyệt linked list tại `buckets[index]`.
- Nếu gặp node có `node->english == english` ⇒ không thêm.

### Bước 3: Chèn theo thứ tự alphabet
- Duyệt với biến `prev` và `cur`:
  - Trong khi `cur != nullptr` và `cur->english < english` thì dịch con trỏ.
- Chèn node mới vào đúng vị trí:
  - Nếu chèn đầu: `node->next = buckets[index]`, rồi `buckets[index] = node`.
  - Nếu chèn giữa/cuối: `prev->next = node`, `node->next = cur`.

### Độ phức tạp
- Gọi `k` là số node trong bucket tương ứng.
- Thời gian: **O(k)** (tối đa O(n) trong trường hợp xấu), trung bình phụ thuộc độ phân tán của bucket.
- Bộ nhớ: **O(1)** cho mỗi lần thêm (chỉ thêm 1 node).

---

## 2) Tra từ — `search(english)`

### Bước 1: Băm khoá để chọn bucket
- Tính `index = hash(english)` giống như `add`.
- Nếu `english` không hợp lệ (không có chữ cái a-z ở đầu) ⇒ trả về `nullptr`.

### Bước 2: Duyệt linked list trong bucket
- Duyệt `cur` từ `buckets[index]`:
  - Nếu `cur->english == english` ⇒ trả về con trỏ `cur`.
  - Nếu hết danh sách ⇒ không tìm thấy.

### Độ phức tạp
- Gọi `k` là số node trong bucket.
- Thời gian: **O(k)** (trung bình quanh O(n/26)).
- Bộ nhớ: **O(1)**.

---

## 3) Hiển thị theo nhóm chữ cái — `displayGroup(letter)`

### Bước 1: Chuẩn hoá ký tự nhóm
- Lấy `c = tolower(letter)`.
- Nếu `c` không thuộc `a..z` ⇒ báo lỗi.

### Bước 2: Tính bucket index
- `index = c - 'a'`.

### Bước 3: Duyệt toàn bộ bucket
- Duyệt linked list tại `buckets[index]`.
- In ra từng node theo định dạng:
  - `english | vietnamese | pos`

### Độ phức tạp
- Gọi `k` là số node trong bucket đó.
- Thời gian: **O(k)**.
- Bộ nhớ: **O(1)**.
