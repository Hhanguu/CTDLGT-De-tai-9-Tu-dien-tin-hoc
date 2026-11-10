#include "Menu.h"

#include "FileIO.h"

#include <cctype>
#include <iostream>
#include <limits>
#include <string>

static void printMenu() {
    std::cout << "\n===== TU DIEN TIN HOC (26 bucket + linked list) =====\n"
              << "1. Them tu (add)\n"
              << "2. Tra tu (search)\n"
              << "3. Hien thi nhom chu cai (displayGroup)\n"
              << "0. Thoat\n"
              << "Chon: ";
}

void runMenu(HashTable& ht, const std::string& dataFile) {
    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!(std::cin >> choice)) return;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::string en, vi, pos;
            std::cout << "Tu tieng Anh: ";
            std::getline(std::cin, en);
            std::cout << "Nghia tieng Viet: ";
            std::getline(std::cin, vi);
            std::cout << "Loai tu (noun/verb/adj/...): ";
            std::getline(std::cin, pos);

            if (ht.add(en, vi, pos)) {
                std::cout << "Da them: " << en << "\n";
                // Lưu lại để lần chạy sau không mất
                saveToFile(ht, dataFile);
            } else {
                std::cout << "Khong them duoc (trung hoac key khong hop le a-z).\n";
            }

        } else if (choice == 2) {
            std::string en;
            std::cout << "Nhap tu can tra: ";
            std::getline(std::cin, en);
            Entry* e = ht.search(en);
            if (!e) {
                std::cout << "Khong tim thay: " << en << "\n";
            } else {
                std::cout << e->english << " | " << e->vietnamese << " | " << e->pos << "\n";
            }

        } else if (choice == 3) {
            char letter;
            std::cout << "Nhap chu cai (a-z): ";
            std::cin >> letter;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            ht.displayGroup(letter);

        } else if (choice == 0) {
            std::cout << "Tam biet!\n";
        } else {
            std::cout << "Lua chon khong hop le.\n";
        }
    }
}
