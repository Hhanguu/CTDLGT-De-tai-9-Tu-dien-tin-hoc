#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Entry.h"
#include <string>

// Bảng băm 26 bucket — mỗi bucket là một danh sách liên kết đơn
class HashTable {
public:
    HashTable();
    ~HashTable();

    // Chặn copy: các bucket là con trỏ sở hữu, copy nông sẽ gây double-free
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    // Hàm băm: lấy chữ cái đầu của từ, trả về index 0–25
    int hash(const std::string& key) const;

    // Thêm từ mới (chèn theo thứ tự alphabet trong bucket)
    bool add(const std::string& english, const std::string& vietnamese, const std::string& pos);

    // Tra từ — trả về con trỏ Entry nếu tìm thấy, nullptr nếu không
    Entry* search(const std::string& english) const;

    // Xóa từ — trả về true nếu xóa thành công
    bool remove(const std::string& english);

    // Sửa nghĩa và/hoặc loại từ
    bool edit(const std::string& english, const std::string& newVi, const std::string& newPos);

    // Hiển thị tất cả từ trong một nhóm chữ cái
    void displayGroup(char letter) const;

    // Hiển thị toàn bộ từ điển
    void displayAll() const;

    // Số từ hiện có
    int getSize() const { return size_; }

    // Truy cập bucket theo index 0–25 (dùng cho FileIO)
    const Entry* getBucket(int index) const {
        if (index < 0 || index >= BUCKET_COUNT) return nullptr;
        return buckets_[index];
    }

private:
    static const int BUCKET_COUNT = 26;
    Entry* buckets_[BUCKET_COUNT];
    int size_;

    // Xóa toàn bộ một bucket (dùng trong destructor)
    void clearBucket(int index);

    // Tìm node theo khoá, so sánh không phân biệt hoa/thường.
    // prevOut (nếu khác nullptr) nhận node liền trước node tìm thấy.
    Entry* findEntry(const std::string& english, Entry** prevOut = nullptr) const;
};

#endif // HASHTABLE_H
