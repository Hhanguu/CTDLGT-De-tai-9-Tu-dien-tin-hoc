# Phần 2 — Thiết kế cấu trúc dữ liệu và giải thuật

## 2.1 Cấu trúc một phần tử — `Entry`

Mỗi từ là một node của danh sách liên kết đơn (`include/Entry.h`):

```cpp
struct Entry {
    std::string english;    // từ tiếng Anh (khoá)
    std::string vietnamese; // nghĩa tiếng Việt
    std::string pos;        // loại từ: noun, verb, adj, adv, ...
    Entry* next;            // node kế tiếp trong bucket

    Entry(const std::string& en, const std::string& vi, const std::string& pos);
};
```

## 2.2 Cấu trúc bảng băm — `HashTable`

Bảng băm cố định **26 bucket** ứng với 26 chữ cái `a–z`; mỗi bucket là đầu một danh sách liên kết đơn (chaining).

| Thành phần | Ý nghĩa |
|---|---|
| `static const int BUCKET_COUNT = 26` | Số bucket cố định |
| `Entry* buckets_[26]` | Con trỏ đầu danh sách của từng bucket |
| `int size_` | Tổng số từ hiện có |
| `clearBucket(int)` | Giải phóng toàn bộ node của một bucket (dùng trong destructor) |
| `findEntry(key, prevOut)` | Tìm node theo khoá; trả kèm node liền trước |

```cpp
class HashTable {
public:
    HashTable();
    ~HashTable();

    // Chặn copy: buckets_ là con trỏ sở hữu, copy nông sẽ gây double-free
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    int hash(const std::string& key) const;
    bool add(const std::string& english, const std::string& vietnamese,
             const std::string& pos);
    Entry* search(const std::string& english) const;
    bool remove(const std::string& english);
    bool edit(const std::string& english, const std::string& newVi,
              const std::string& newPos);
    void displayGroup(char letter) const;
    void displayAll() const;
    int getSize() const;

private:
    Entry* buckets_[BUCKET_COUNT];
    int size_;
    void clearBucket(int index);
    Entry* findEntry(const std::string& english, Entry** prevOut = nullptr) const;
};
```

## 2.3 Hàm băm

```
h(key):
    nếu key rỗng              -> -1 (không hợp lệ)
    c = tolower(key[0])
    nếu c không thuộc 'a'..'z' -> -1
    trả về c - 'a'             (0..25)
```

Ví dụ: `algorithm` → `0`; `Cache` → `2`; `123abc` → `-1` (từ chối).

## 2.4 Giải thuật các thao tác

### 2.4.1 Thêm từ — `add`

1. `idx = hash(english)`; nếu `idx < 0` → từ chối.
2. Duyệt bucket `idx`, nếu có node `equalsIgnoreCase(node->english, english)` → từ đã tồn tại, trả `false`.
3. Cấp phát node mới.
4. Tìm vị trí chèn: duyệt `prev`/`cur` trong khi `cur != nullptr` và `lessIgnoreCase(cur->english, english)`.
5. Nối node vào đúng vị trí (đầu bucket hoặc sau `prev`), tăng `size_`.

```cpp
bool HashTable::add(const std::string& english, const std::string& vietnamese,
                    const std::string& pos) {
    int idx = hash(english);
    if (idx < 0) return false;

    for (Entry* cur = buckets_[idx]; cur; cur = cur->next) {
        if (equalsIgnoreCase(cur->english, english)) return false;
    }

    Entry* node = new Entry(english, vietnamese, pos);

    Entry* prev = nullptr;
    Entry* cur = buckets_[idx];
    while (cur && lessIgnoreCase(cur->english, english)) {
        prev = cur;
        cur = cur->next;
    }
    node->next = cur;
    if (prev) prev->next = node;
    else buckets_[idx] = node;

    ++size_;
    return true;
}
```

**Độ phức tạp:** O(k) với k là số node trong bucket (trung bình O(n/26), xấu nhất O(n)).

### 2.4.2 Tra từ — `search`

Dùng chung `findEntry`: băm khoá, duyệt bucket và so sánh `equalsIgnoreCase`.

```cpp
Entry* HashTable::search(const std::string& english) const {
    return findEntry(english);
}
```

**Độ phức tạp:** O(k), bộ nhớ O(1).

### 2.4.3 Tìm node (dùng chung) — `findEntry`

```cpp
Entry* HashTable::findEntry(const std::string& english, Entry** prevOut) const {
    if (prevOut) *prevOut = nullptr;
    int idx = hash(english);
    if (idx < 0) return nullptr;

    Entry* prev = nullptr;
    for (Entry* cur = buckets_[idx]; cur; cur = cur->next) {
        if (equalsIgnoreCase(cur->english, english)) {
            if (prevOut) *prevOut = prev;
            return cur;
        }
        prev = cur;
    }
    return nullptr;
}
```

`prevOut` cho phép `remove` biết node liền trước để nối lại danh sách.

### 2.4.4 Xóa từ — `remove`

1. `findEntry(english, &prev)`; không thấy → `false`.
2. Nếu có node trước: `prev->next = cur->next`; nếu xóa đầu bucket: `buckets_[hash(english)] = cur->next`.
3. `delete cur`, giảm `size_`, trả `true`.

```cpp
bool HashTable::remove(const std::string& english) {
    Entry* prev = nullptr;
    Entry* cur = findEntry(english, &prev);
    if (!cur) return false;

    if (prev) prev->next = cur->next;
    else buckets_[hash(english)] = cur->next;

    delete cur;
    --size_;
    return true;
}
```

**Độ phức tạp:** O(k); giải phóng đúng bộ nhớ, không rò rỉ.

### 2.4.5 Sửa nghĩa/loại từ — `edit`

1. Nếu cả `newVi` và `newPos` đều rỗng → không có gì để sửa, trả `false`.
2. `findEntry(english)`; không thấy → `false`.
3. Chỉ cập nhật trường có dữ liệu mới (trường để trống giữ nguyên giá trị cũ).

```cpp
bool HashTable::edit(const std::string& english, const std::string& newVi,
                     const std::string& newPos) {
    if (newVi.empty() && newPos.empty()) return false;

    Entry* e = findEntry(english);
    if (!e) return false;

    if (!newVi.empty()) e->vietnamese = newVi;
    if (!newPos.empty()) e->pos = newPos;
    return true;
}
```

**Độ phức tạp:** O(k).

### 2.4.6 Hiển thị theo nhóm chữ cái — `displayGroup`

1. `c = tolower(letter)`; nếu `c` ngoài `a–z` → báo lỗi.
2. Duyệt `buckets_[c - 'a']` và in từng node theo định dạng `english | vietnamese | pos`.
3. Bucket rỗng → in `(rong)`.

**Độ phức tạp:** O(k).

### 2.4.7 Hiển thị tất cả — `displayAll`

1. Nếu `size_ == 0` → in `(trong)`.
2. Duyệt bucket `0..25`, với mỗi bucket in toàn bộ node.

```cpp
void HashTable::displayAll() const {
    if (size_ == 0) {
        std::cout << "  (trong)\n";
        return;
    }
    for (int i = 0; i < BUCKET_COUNT; ++i) {
        for (Entry* cur = buckets_[i]; cur; cur = cur->next) {
            std::cout << cur->english << " | " << cur->vietnamese
                      << " | " << cur->pos << "\n";
        }
    }
}
```

**Độ phức tạp:** O(N) — mỗi node được in đúng một lần. Do bucket xếp theo chữ cái đầu và trong bucket đã chèn theo alphabet, kết quả ra đúng thứ tự alphabet.

## 2.5 Sơ đồ bộ nhớ (dữ liệu mẫu)

```
buckets[0] → [algorithm|thuật toán|noun] → [api|giao diện lập trình ứng dụng|noun]
           → [array|mảng|noun] → null
buckets[1] → [bit|bit|noun] → [boolean|luận lý|adj] → [buffer|bộ đệm|noun] → null
buckets[2] → [cache|bộ nhớ đệm|noun] → [class|lớp|noun] → [compiler|trình biên dịch|noun]
           → [cpu|bộ xử lý trung tâm|noun] → null
buckets[3] → [database|cơ sở dữ liệu|noun] → [debug|gỡ lỗi|verb] → null
...
buckets[9] → null   (không có từ bắt đầu bằng 'j')
...
buckets[25] → null  (không có từ bắt đầu bằng 'z')
```

## 2.6 Định dạng file và đọc/ghi dữ liệu

- File TXT, mỗi dòng một từ: `english|vietnamese|pos`.
- `saveToFile`: duyệt 26 bucket, ghi lần lượt từng node theo đúng thứ tự trong bảng.
- `loadFromFile`:
  1. Đọc từng dòng, bỏ dòng rỗng và dòng bắt đầu bằng `#`.
  2. Tách 3 trường theo dấu `|` (trường `pos` có thể thiếu).
  3. `trim` cả 3 trường để loại khoảng trắng và ký tự `\r` (file CRLF trên Windows).
  4. Bỏ qua dòng không có từ tiếng Anh; gọi `add` cho các dòng hợp lệ (từ trùng bị bỏ qua).

Nhờ bước `trim`, dữ liệu nạp từ file CRLF không còn dính `\r` ở trường `pos` — lỗi thường gặp khi đọc file TXT trên Windows.
