#ifndef FILEIO_H
#define FILEIO_H

#include "HashTable.h"
#include <string>

// Lưu toàn bộ từ điển ra file TXT
// Định dạng mỗi dòng: english|vietnamese|pos
bool saveToFile(const HashTable& ht, const std::string& filename);

// Tải từ điển từ file TXT vào bảng băm
bool loadFromFile(HashTable& ht, const std::string& filename);

#endif // FILEIO_H
