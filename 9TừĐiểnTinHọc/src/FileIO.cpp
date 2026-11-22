#include "FileIO.h"

#include <fstream>
#include <sstream>
#include <string>

// Cắt khoảng trắng và ký tự xuống dòng (CR/LF) ở hai đầu chuỗi.
// Cần thiết vì file dữ liệu trên Windows dùng CRLF: getline chỉ bỏ '\n',
// nên trường cuối (pos) sẽ còn dính '\r' nếu không trim.
static std::string trim(const std::string& s) {
    const char* ws = " \t\r\n";
    std::string::size_type first = s.find_first_not_of(ws);
    if (first == std::string::npos) return "";
    std::string::size_type last = s.find_last_not_of(ws);
    return s.substr(first, last - first + 1);
}

static bool parseLine(const std::string& line, std::string& en, std::string& vi, std::string& pos) {
    std::string trimmed = trim(line);
    if (trimmed.empty() || trimmed[0] == '#') return false;

    std::istringstream ss(trimmed);
    if (!std::getline(ss, en, '|')) return false;
    if (!std::getline(ss, vi, '|')) return false;
    if (!std::getline(ss, pos)) pos.clear();

    en = trim(en);
    vi = trim(vi);
    pos = trim(pos);
    return !en.empty();
}

bool saveToFile(const HashTable& ht, const std::string& filename) {
    std::ofstream f(filename);
    if (!f.is_open()) return false;

    for (int i = 0; i < 26; ++i) {
        const Entry* cur = ht.getBucket(i);
        while (cur) {
            f << cur->english << '|' << cur->vietnamese << '|' << cur->pos << '\n';
            cur = cur->next;
        }
    }
    return true;
}

bool loadFromFile(HashTable& ht, const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;

    std::string line;
    while (std::getline(f, line)) {
        std::string en, vi, pos;
        if (!parseLine(line, en, vi, pos)) continue;
        ht.add(en, vi, pos);
    }
    return true;
}
