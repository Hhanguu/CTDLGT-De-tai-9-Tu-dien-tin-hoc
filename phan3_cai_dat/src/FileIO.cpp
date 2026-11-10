#include "FileIO.h"

#include <fstream>
#include <sstream>
#include <string>

static bool parseLine(const std::string& line, std::string& en, std::string& vi, std::string& pos) {
    if (line.empty() || line[0] == '#') return false;
    std::istringstream ss(line);
    return std::getline(ss, en, '|') &&
           std::getline(ss, vi, '|') &&
           std::getline(ss, pos);
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
