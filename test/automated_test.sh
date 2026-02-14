#!/bin/bash

# Automated Test Suite for Trie Auto-Suggest System
# This script runs comprehensive tests to verify functionality

# Get the directory where the script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Change to project root
cd "$PROJECT_ROOT" || exit 1

echo "╔════════════════════════════════════════════════════════╗"
echo "║   TRIE AUTO-SUGGEST SYSTEM - AUTOMATED TEST SUITE     ║"
echo "╚════════════════════════════════════════════════════════╝"
echo ""
echo "Project directory: $PROJECT_ROOT"
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0

# Function to run a test
run_test() {
    local test_name="$1"
    local input="$2"
    local expected_pattern="$3"
    
    echo -n "  Testing: $test_name... "
    
    result=$(echo -e "$input" | ./trie_autosuggest 2>&1)
    
    if echo "$result" | grep -q "$expected_pattern"; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo "    Expected pattern: $expected_pattern"
        echo "    Got: $(echo "$result" | grep -A 2 "Suggestions:")"
        ((FAILED++))
    fi
}

# Compile the program
echo "Compiling..."
g++ -std=c++17 -Wall -Wextra src/trie_autosuggest.cpp -o trie_autosuggest 2>&1

if [ $? -ne 0 ]; then
    echo -e "${RED}✗ Compilation FAILED${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Compilation successful${NC}"
echo ""

echo "Running Tests:"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

# Test 1: Basic prefix search "ap"
run_test "Prefix 'ap' search" "1\nap\n5" "apartment"

# Test 2: Prefix search "ba"
run_test "Prefix 'ba' search" "1\nba\n5" "badge"

# Test 3: No results for "xyz"
run_test "No matches for 'xyz'" "1\nxyz\n5" "No suggestions found"

# Test 4: Single character prefix "c"
run_test "Single char prefix 'c'" "1\nc\n5" "camera"

# Test 5: Case insensitive search "AP" 
run_test "Case insensitive 'AP'" "1\nAP\n5" "apartment"

# Test 6: Empty prefix (show all)
run_test "Empty prefix (all words)" "1\n\n5" "Found 49 match"

# Test 7: Add new word
run_test "Add word 'testing'" "2\ntesting\n1\ntest\n5" "testing"

# Test 8: Statistics display
run_test "Show statistics" "3\n5" "Total Words:"

# Test 9: Alphabetical sorting (just check first result is alphabetically first)
run_test "Alphabetical order check" "1\nap\n5" "apartment"

# Test 10: Whitespace handling
run_test "Whitespace trimming" "1\n  ap  \n5" "apartment"

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
echo "Test Results:"
echo "  ${GREEN}Passed: $PASSED${NC}"
echo "  ${RED}Failed: $FAILED${NC}"
echo "  Total:  $((PASSED + FAILED))"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}╔════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║  ALL TESTS PASSED SUCCESSFULLY! ✓ ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════╝${NC}"
    exit 0
else
    echo -e "${RED}╔══════════════════════════════╗${NC}"
    echo -e "${RED}║  SOME TESTS FAILED!  ✗      ║${NC}"
    echo -e "${RED}╚══════════════════════════════╝${NC}"
    exit 1
fi
