#include "HashTable.h"
#include "FileIO.h"
#include "Menu.h"
#include <iostream>

int main() {
    const std::string DATA_FILE = "data/tudien.txt";

    HashTable ht;
    if (!loadFromFile(ht, DATA_FILE)) {
        std::cout << "Khong the doc file du lieu: " << DATA_FILE << "\n";
    }

    std::cout << "Da tai " << ht.getSize() << " tu.\n";
    runMenu(ht, DATA_FILE);
    return 0;
}
