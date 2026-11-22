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
              << "3. Sua tu (edit)\n"
              << "4. Xoa tu (remove)\n"
              << "5. Hien thi nhom chu cai (displayGroup)\n"
              << "6. Hien thi toan bo tu dien (displayAll)\n"
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
            // --- Thêm từ ---
            std::string en, vi, pos;
            std::cout << "Tu tieng Anh: ";
            std::getline(std::cin, en);
            std::cout << "Nghia tieng Viet: ";
            std::getline(std::cin, vi);
            std::cout << "Loai tu (noun/verb/adj/...): ";
            std::getline(std::cin, pos);

            if (ht.add(en, vi, pos)) {
                std::cout << "Da them: " << en << "\n";
                saveToFile(ht, dataFile);
            } else {
                std::cout << "Khong them duoc (trung hoac key khong hop le a-z).\n";
            }

        } else if (choice == 2) {
            // --- Tra từ ---
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
            // --- Sửa từ ---
            std::string en, vi, pos;
            std::cout << "Tu can sua: ";
            std::getline(std::cin, en);

            if (!ht.search(en)) {
                std::cout << "Khong tim thay: " << en << "\n";
            } else {
                std::cout << "Nghia moi (Enter de giu nguyen): ";
                std::getline(std::cin, vi);
                std::cout << "Loai tu moi (Enter de giu nguyen): ";
                std::getline(std::cin, pos);

                if (ht.edit(en, vi, pos)) {
                    std::cout << "Da cap nhat: " << en << "\n";
                    saveToFile(ht, dataFile);
                } else {
                    std::cout << "Sua that bai.\n";
                }
            }

        } else if (choice == 4) {
            // --- Xóa từ ---
            std::string en;
            std::cout << "Tu can xoa: ";
            std::getline(std::cin, en);

            if (ht.remove(en)) {
                std::cout << "Da xoa: " << en << "\n";
                saveToFile(ht, dataFile);
            } else {
                std::cout << "Khong tim thay: " << en << "\n";
            }

        } else if (choice == 5) {
            // --- Hiển thị nhóm chữ cái ---
            char letter;
            std::cout << "Nhap chu cai (a-z): ";
            std::cin >> letter;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ht.displayGroup(letter);

        } else if (choice == 6) {
            // --- Hiển thị toàn bộ ---
            std::cout << "Toan bo tu dien (" << ht.getSize() << " tu):\n";
            ht.displayAll();

        } else if (choice == 0) {
            std::cout << "Tam biet!\n";
        } else {
            std::cout << "Lua chon khong hop le.\n";
        }
    }
}
