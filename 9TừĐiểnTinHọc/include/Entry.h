#ifndef ENTRY_H
#define ENTRY_H

#include <string>

// Một phần tử trong từ điển (node của danh sách liên kết)
struct Entry {
    std::string english;    // từ tiếng Anh (khoá)
    std::string vietnamese; // nghĩa tiếng Việt
    std::string pos;        // loại từ: noun, verb, adj, adv, ...
    Entry* next;            // con trỏ đến phần tử kế tiếp

    Entry(const std::string& en, const std::string& vi, const std::string& pos)
        : english(en), vietnamese(vi), pos(pos), next(nullptr) {}
};

#endif // ENTRY_H
