#include "HashTable.h"

#include <cctype>
#include <iostream>
#include <string>

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

bool HashTable::add(const std::string& english, const std::string& vietnamese, const std::string& pos) {
    int idx = hash(english);
    if (idx < 0) return false;

    // Kiểm tra trùng khóa trong bucket
    Entry* cur = buckets_[idx];
    while (cur) {
        if (cur->english == english) return false;
        cur = cur->next;
    }

    // Tạo node mới
    Entry* node = new Entry(english, vietnamese, pos);

    // Chèn theo thứ tự alphabet trong bucket (tăng dần theo english)
    Entry* prev = nullptr;
    cur = buckets_[idx];
    while (cur && cur->english < english) {
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
    int idx = hash(english);
    if (idx < 0) return nullptr;

    Entry* cur = buckets_[idx];
    while (cur) {
        if (cur->english == english) return cur;
        cur = cur->next;
    }
    return nullptr;
}

bool HashTable::remove(const std::string& english) {
    int idx = hash(english);
    if (idx < 0) return false;

    Entry* prev = nullptr;
    Entry* cur = buckets_[idx];
    while (cur) {
        if (cur->english == english) {
            if (prev) prev->next = cur->next;
            else buckets_[idx] = cur->next;
            delete cur;
            --size_;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

bool HashTable::edit(const std::string& english, const std::string& newVi, const std::string& newPos) {
    Entry* e = search(english);
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
    for (int i = 0; i < BUCKET_COUNT; ++i) {
        Entry* cur = buckets_[i];
        while (cur) {
            std::cout << cur->english << " | " << cur->vietnamese << " | " << cur->pos << "\n";
            cur = cur->next;
        }
    }
}
