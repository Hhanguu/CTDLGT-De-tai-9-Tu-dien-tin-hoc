#include "HashTable.h"
#include "FileIO.h"
#include "Menu.h"
#include <iostream>

int main() {
    const std::string DATA_FILE = "data/tudien_1000.txt";

    std::cout << "===== TU DIEN TIN HOC - TEST 1000 TU =====\n";
    std::cout << "Dang tai du lieu tu " << DATA_FILE << "...\n";

    HashTable ht;
    if (!loadFromFile(ht, DATA_FILE)) {
        std::cout << "LOI: Khong the doc file du lieu: " << DATA_FILE << "\n";
        std::cout << "Hay chay tu thu muc phan3_cai_dat/\n";
        return 1;
    }

    std::cout << "THANH CONG! Da tai " << ht.getSize() << " tu vao bo nho.\n";
    runMenu(ht, DATA_FILE);
    return 0;
}
