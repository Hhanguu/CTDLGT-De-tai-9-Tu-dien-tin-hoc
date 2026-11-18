#!/bin/bash
# Test script cho tu dien voi 1000 tu

cd "$(dirname "$0")"

echo "===== TEST TU DIEN 1000 TU ====="
echo ""

# Test 1: Load file 1000 tu
echo "Test 1: Load file tudien_1000.txt"
time_start=$(date +%s%N)
./tudien <<EOF > /dev/null 2>&1
0
EOF
time_end=$(date +%s%N)
time_diff=$(( (time_end - time_start) / 1000000 ))
echo "  -> Thoi gian: ${time_diff}ms"
echo ""

# Test 2: Chay benchmark voi 1000 tu
echo "Test 2: Benchmark 1000 tu"
if [ -f "./benchmark" ]; then
    ./benchmark 1000
else
    echo "  -> Chua build benchmark. Chay: make bench"
fi
echo ""

# Test 3: Dem so tu trong file
echo "Test 3: Dem so tu trong file"
tu_count=$(grep -v "^#" data/tudien_1000.txt | grep -v "^$" | wc -l)
echo "  -> Tong so tu: $tu_count"
echo ""

# Test 4: Thong ke phan bo chu cai
echo "Test 4: Phan bo theo chu cai dau:"
for letter in {a..z}; do
    count=$(grep -i "^$letter" data/tudien_1000.txt | wc -l)
    if [ $count -gt 0 ]; then
        printf "  %s: %3d tu\n" "$letter" "$count"
    fi
done
echo ""

echo "===== HOAN TAT ====="
