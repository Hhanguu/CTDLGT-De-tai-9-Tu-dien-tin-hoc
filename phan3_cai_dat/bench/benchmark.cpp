// Benchmark cac thao tac chinh cua HashTable (phan cua Thanh vien A).
// Do thoi gian add / search (hit + miss) / remove tren N tu sinh ngau nhien,
// thong ke do dai chuoi trong 26 bucket va thoi gian nap file du lieu mau.
//
// Build: make bench
// Chay : ./benchmark [N]   (mac dinh N = 100000)

#include "FileIO.h"
#include "HashTable.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;

double toMillis(Clock::duration d) {
    return std::chrono::duration<double, std::milli>(d).count();
}

double toNanosPerOp(Clock::duration d, std::size_t ops) {
    if (ops == 0) return 0.0;
    return std::chrono::duration<double, std::nano>(d).count() / static_cast<double>(ops);
}

// Sinh N tu ngau nhien: chu cai dau a-z + duoi ngau nhien, dung seed co dinh
// de moi lan chay cho cung du lieu (ket qua tai lap duoc).
std::vector<std::string> makeWords(int n) {
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> letter(0, 25);
    std::uniform_int_distribution<int> suffix(0, 999999999);

    std::vector<std::string> words;
    words.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        std::string w(1, static_cast<char>('a' + letter(rng)));
        int len = 2 + static_cast<int>(rng() % 6); // tong do dai 3..8 chu cai
        for (int j = 0; j < len; ++j) {
            w.push_back(static_cast<char>('a' + letter(rng)));
        }
        w += std::to_string(suffix(rng));
        words.push_back(std::move(w));
    }
    return words;
}

void reportBuckets(const HashTable& ht) {
    int maxLen = 0;
    int minLen = 0;
    int used = 0;
    long long total = 0;

    for (int i = 0; i < 26; ++i) {
        int len = 0;
        for (const Entry* cur = ht.getBucket(i); cur; cur = cur->next) ++len;
        if (len > 0) {
            ++used;
            if (minLen == 0 || len < minLen) minLen = len;
            if (len > maxLen) maxLen = len;
        }
        total += len;
    }

    double avg = used ? static_cast<double>(total) / used : 0.0;
    std::cout << "  Bucket co du lieu : " << used << "/26\n"
              << "  Chuoi ngan nhat  : " << minLen << "\n"
              << "  Chuoi dai nhat   : " << maxLen << "\n"
              << "  Chuoi trung binh : " << std::fixed << std::setprecision(2) << avg << "\n";
}

} // namespace

int main(int argc, char** argv) {
    int n = 100000;
    if (argc > 1) n = std::max(1, std::atoi(argv[1]));

    std::cout << "===== BENCHMARK HASH TABLE (" << n << " tu) =====\n";

    std::vector<std::string> words = makeWords(n);
    HashTable ht;

    int added = 0;
    auto t0 = Clock::now();
    for (const std::string& w : words) {
        if (ht.add(w, "nghia", "noun")) ++added;
    }
    auto t1 = Clock::now();

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\n[add] " << added << "/" << n << " tu\n"
              << "  Tong  : " << toMillis(t1 - t0) << " ms\n"
              << "  TB/tu : " << toNanosPerOp(t1 - t0, static_cast<std::size_t>(added)) << " ns\n";
    reportBuckets(ht);

    long long found = 0;
    auto t2 = Clock::now();
    for (const std::string& w : words) {
        if (ht.search(w)) ++found;
    }
    auto t3 = Clock::now();

    std::cout << "\n[search - hit] " << found << "/" << n << " tu\n"
              << "  Tong  : " << toMillis(t3 - t2) << " ms\n"
              << "  TB/tu : " << toNanosPerOp(t3 - t2, static_cast<std::size_t>(n)) << " ns\n";

    int misses = std::max(1, n / 10);
    long long hitOnMiss = 0;
    auto t4 = Clock::now();
    for (int i = 0; i < misses; ++i) {
        if (ht.search("zzz_khong_ton_tai_" + std::to_string(i))) ++hitOnMiss;
    }
    auto t5 = Clock::now();

    std::cout << "\n[search - miss] " << misses << " tu\n"
              << "  Tong  : " << toMillis(t5 - t4) << " ms\n"
              << "  TB/tu : " << toNanosPerOp(t5 - t4, static_cast<std::size_t>(misses)) << " ns\n"
              << "  Tim thay nham: " << hitOnMiss << "\n";

    int removed = 0;
    auto t6 = Clock::now();
    for (const std::string& w : words) {
        if (ht.remove(w)) ++removed;
    }
    auto t7 = Clock::now();

    std::cout << "\n[remove] " << removed << "/" << n << " tu\n"
              << "  Tong  : " << toMillis(t7 - t6) << " ms\n"
              << "  TB/tu : " << toNanosPerOp(t7 - t6, static_cast<std::size_t>(removed)) << " ns\n"
              << "  Con lai trong bang: " << ht.getSize() << "\n";

    const std::string dataFile = "data/tudien.txt";
    HashTable loaded;
    auto t8 = Clock::now();
    bool ok = loadFromFile(loaded, dataFile);
    auto t9 = Clock::now();

    std::cout << "\n[load file] " << dataFile << "\n";
    if (ok) {
        std::cout << "  So tu : " << loaded.getSize() << "\n"
                  << "  Tong  : " << toMillis(t9 - t8) << " ms\n";
    } else {
        std::cout << "  Khong mo duoc file (hay chay tu thu muc phan3_cai_dat)\n";
    }

    return 0;
}
