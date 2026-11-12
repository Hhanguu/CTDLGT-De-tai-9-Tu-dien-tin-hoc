#include "HashTable.h"

#include <cctype>
#include <iostream>
#include <string>

// So sánh chuỗi theo từng ký tự; trả về <0, 0, >0 giống strcmp.
static int compareIgnoreCase(const std::string& a, const std::string& b) {
    std::string::size_type n = a.size() < b.size() ? a.size() : b.size();
    for (std::string::size_type i = 0; i < n; ++i) {
        int ca = std::tolower(static_cast<unsigned char>(a[i]));
        int cb = std::tolower(static_cast<unsigned char>(b[i]));
        if (ca != cb) return ca < cb ? -1 : 1;
    }
    if (a.size() == b.size()) return 0;
    return a.size() < b.size() ? -1 : 1;
}

static bool equalsIgnoreCase(const std::string& a, const std::string& b) {
    return compareIgnoreCase(a, b) == 0;
}

static bool lessIgnoreCase(const std::string& a, const std::string& b) {
    return compareIgnoreCase(a, b) < 0;
}

HashTable::HashTable() : size_(0) {
    for (int i = 0; i < BUCKET_COUNT; ++i) buckets_[i] = nullptr;
}

void HashTable::clearBucket(int index) {
    Entry* cur = buckets_[index];
    while (cur) {
        Entry* next = cur->next;
        delete cur;
        cur = next;
    }
    buckets_[index] = nullptr;
}

HashTable::~HashTable() {
    for (int i = 0; i < BUCKET_COUNT; ++i) clearBucket(i);
}

int HashTable::hash(const std::string& key) const {
    if (key.empty()) return -1;
    char c = static_cast<char>(std::tolower(static_cast<unsigned char>(key[0])));
    if (c < 'a' || c > 'z') return -1;
    return c - 'a';
}

Entry* HashTable::findEntry(const std::string& english, Entry** prevOut) const {
    if (prevOut) *prevOut = nullptr;

    int idx = hash(english);
    if (idx < 0) return nullptr;

    Entry* prev = nullptr;
    Entry* cur = buckets_[idx];
    while (cur) {
        if (equalsIgnoreCase(cur->english, english)) {
            if (prevOut) *prevOut = prev;
            return cur;
        }
        prev = cur;
        cur = cur->next;
    }
    return nullptr;
}

bool HashTable::add(const std::string& english, const std::string& vietnamese, const std::string& pos) {
    int idx = hash(english);
    if (idx < 0) return false;

    // Kiểm tra trùng khóa trong bucket
    Entry* cur = buckets_[idx];
    while (cur) {
        if (equalsIgnoreCase(cur->english, english)) return false;
        cur = cur->next;
    }

    // Tạo node mới
    Entry* node = new Entry(english, vietnamese, pos);

    // Chèn theo thứ tự alphabet trong bucket
    Entry* prev = nullptr;
    cur = buckets_[idx];
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

Entry* HashTable::search(const std::string& english) const {
    return findEntry(english);
}

bool HashTable::remove(const std::string& english) {
    Entry* prev = nullptr;
    Entry* cur = findEntry(english, &prev);
    if (!cur) return false;

    if (prev) {
        prev->next = cur->next;
    } else {
        buckets_[hash(english)] = cur->next;
    }

    delete cur;
    --size_;
    return true;
}

bool HashTable::edit(const std::string& english, const std::string& newVi, const std::string& newPos) {
    if (newVi.empty() && newPos.empty()) return false;

    Entry* e = findEntry(english);
    if (!e) return false;

    if (!newVi.empty()) e->vietnamese = newVi;
    if (!newPos.empty()) e->pos = newPos;
    return true;
}

void HashTable::displayGroup(char letter) const {
    char c = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
    if (c < 'a' || c > 'z') {
        std::cout << "Ky tu khong hop le. Chi nhap a-z.\n";
        return;
    }

    int idx = c - 'a';
    Entry* cur = buckets_[idx];
    std::cout << "Nhom '" << static_cast<char>(std::toupper(static_cast<unsigned char>(c))) << "':\n";

    if (!cur) {
        std::cout << "  (rong)\n";
        return;
    }

    while (cur) {
        std::cout << "  " << cur->english << " | " << cur->vietnamese << " | " << cur->pos << "\n";
        cur = cur->next;
    }
}

void HashTable::displayAll() const {
    if (size_ == 0) {
        std::cout << "  (trong)\n";
        return;
    }

    // Duyệt bucket 0..25 theo chữ cái đầu, trong mỗi bucket đã sắp alphabet
    for (int i = 0; i < BUCKET_COUNT; ++i) {
        for (Entry* cur = buckets_[i]; cur; cur = cur->next) {
            std::cout << cur->english << " | " << cur->vietnamese << " | " << cur->pos << "\n";
        }
    }
}
