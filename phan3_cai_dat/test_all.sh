#!/bin/bash
echo "========================================="
echo "    TEST SUITE - TU DIEN TIN HOC"
echo "========================================="
echo ""

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

pass=0
fail=0

# Test 1: Build
echo "Test 1: Build project"
make clean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ PASS${NC} - Build successful"
    ((pass++))
else
    echo -e "${RED}✗ FAIL${NC} - Build failed"
    ((fail++))
    exit 1
fi
echo ""

# Test 2: Load file 29 từ
echo "Test 2: Load data/tudien.txt (29 từ)"
output=$(echo "0" | ./tudien 2>&1)
if echo "$output" | grep -q "Da tai 29 tu"; then
    echo -e "${GREEN}✓ PASS${NC} - Loaded 29 words"
    ((pass++))
else
    echo -e "${RED}✗ FAIL${NC} - Expected 29 words"
    echo "$output"
    ((fail++))
fi
echo ""

# Test 3: Load file 1000 từ
echo "Test 3: Load data/tudien_1000.txt (922 từ)"
output=$(echo "0" | ./tudien_1000 2>&1)
if echo "$output" | grep -q "Da tai 922 tu"; then
    echo -e "${GREEN}✓ PASS${NC} - Loaded 922 words"
    ((pass++))
else
    echo -e "${RED}✗ FAIL${NC} - Expected 922 words"
    echo "$output"
    ((fail++))
fi
echo ""

# Test 4: Search - case insensitive
echo "Test 4: Case-insensitive search"
result=$(cat << INPUT | ./tudien_1000 2>&1
2
algorithm
2
ALGORITHM
2
AlGoRiThM
0
INPUT
)
count=$(echo "$result" | grep -c "algorithm | thuat toan | noun")
if [ "$count" -eq 3 ]; then
    echo -e "${GREEN}✓ PASS${NC} - Found 'algorithm' 3 times (case-insensitive)"
    ((pass++))
else
    echo -e "${RED}✗ FAIL${NC} - Expected 3 matches, got $count"
    ((fail++))
fi
echo ""

# Test 5: Search - not found
echo "Test 5: Search word that doesn't exist"
result=$(cat << INPUT | ./tudien_1000 2>&1
2
xyznotexist
0
INPUT
)
if echo "$result" | grep -q "Khong tim thay"; then
    echo -e "${GREEN}✓ PASS${NC} - Correctly returned 'not found'"
    ((pass++))
else
    echo -e "${RED}✗ FAIL${NC} - Should return 'not found'"
    ((fail++))
fi
echo ""

# Test 6: Display group
echo "Test 6: Display group 'c'"
result=$(cat << INPUT | ./tudien_1000 2>&1
3
c
0
INPUT
)
if echo "$result" | grep -q "cache | bo nho dem | noun"; then
    echo -e "${GREEN}✓ PASS${NC} - Group 'C' contains 'cache'"
    ((pass++))
else
    echo -e "${RED}✗ FAIL${NC} - 'cache' not found in group C"
    ((fail++))
fi
echo ""

# Test 7: Benchmark
echo "Test 7: Benchmark (1000 words)"
make bench > /dev/null 2>&1
result=$(./benchmark 1000 2>&1)
if echo "$result" | grep -q "\[add\] 1000/1000 tu"; then
    echo -e "${GREEN}✓ PASS${NC} - Benchmark completed"
    echo "   - Add: $(echo "$result" | grep "TB/tu" | head -1 | awk '{print $3}') ns/word"
    echo "   - Search: $(echo "$result" | grep "TB/tu" | sed -n '2p' | awk '{print $3}') ns/word"
    ((pass++))
else
    echo -e "${RED}✗ FAIL${NC} - Benchmark failed"
    ((fail++))
fi
echo ""

# Test 8: Memory leaks (basic check)
echo "Test 8: Memory check"
if command -v valgrind &> /dev/null; then
    valgrind_out=$(valgrind --leak-check=summary --error-exitcode=1 ./tudien_1000 << INPUT 2>&1
0
INPUT
)
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ PASS${NC} - No memory leaks detected"
        ((pass++))
    else
        echo -e "${RED}✗ FAIL${NC} - Memory leaks detected"
        ((fail++))
    fi
else
    echo -e "${YELLOW}⊘ SKIP${NC} - valgrind not installed"
fi
echo ""

# Test 9: Count words in each group
echo "Test 9: Word distribution check"
result=$(cat << INPUT | ./tudien_1000 2>&1
3
s
0
INPUT
)
s_count=$(echo "$result" | grep -E "^\s+[a-z]+ \|" | wc -l)
if [ "$s_count" -gt 50 ]; then
    echo -e "${GREEN}✓ PASS${NC} - Group 'S' has $s_count words (expected ~110)"
    ((pass++))
else
    echo -e "${RED}✗ FAIL${NC} - Group 'S' has only $s_count words"
    ((fail++))
fi
echo ""

# Summary
echo "========================================="
echo "           TEST SUMMARY"
echo "========================================="
echo -e "Total:  $(($pass + $fail))"
echo -e "${GREEN}Passed: $pass${NC}"
if [ $fail -gt 0 ]; then
    echo -e "${RED}Failed: $fail${NC}"
else
    echo -e "Failed: 0"
fi
echo ""

if [ $fail -eq 0 ]; then
    echo -e "${GREEN}✓ ALL TESTS PASSED!${NC}"
    exit 0
else
    echo -e "${RED}✗ SOME TESTS FAILED${NC}"
    exit 1
fi
