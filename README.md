# Trie-Based Prefix Search Engine

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Status: Production Ready](https://img.shields.io/badge/Status-Production%20Ready-success.svg)]()

## 🎯 Project Overview

The **Trie-Based Prefix Search Engine** is a high-performance C++ application that implements an intelligent prefix-based word suggestion engine using the **Trie (Prefix Tree)** data structure. 

**Real-world relevance**: This same concept powers:
- 🔍 Search engine autocomplete (Google, Bing)
- ⌨️ Mobile keyboard suggestions (iOS, Android)
- 📝 Text editor autocomplete (VS Code, IntelliJ)
- 📚 Dictionary and spell-check systems

---

## ✨ Features

### Core Functionality
- ⚡ **Lightning-fast prefix search** - O(L) time complexity for any prefix length
- 🔤 **Alphabetically sorted suggestions** - Results always in perfect order
- 💚 **Dynamic dictionary** - Add words at runtime without restart
- 🔠 **Case-insensitive search** - "AP" and "ap" work identically
- 🎯 **Smart input handling** - Automatic whitespace trimming and validation

### Premium CLI Experience
- 🎨 **Color-coded interface** - Green success, blue info, cyan suggestions
- 📊 **Real-time statistics** - Dictionary size, search performance metrics
- ⚡ **Performance tracking** - Microsecond-precision search timing
- ✨ **Beautiful formatting** - Professional banner, numbered lists, visual separators
- 🛡️ **Error handling** - Helpful messages with visual indicators (✓/✗)
- ❓ **Built-in help system** - Comprehensive usage guide

### Technical Excellence
- 🧠 **Memory safe** - Proper destructor implementation prevents leaks
- 📝 **Well-documented** - Detailed complexity analysis for every function
- 🧪 **Fully tested** - Automated test suite with 10+ comprehensive tests
- 🏗️ **Production-ready** - Robust error handling and edge case coverage

---

## 📁 Folder Structure

```
Trie-Based-Prefix-Search-Engine/
├── src/
│   └── trie_autosuggest.cpp      # Main C++ implementation (400+ lines)
├── test/
│   ├── test_cases.txt            # Manual test scenarios
│   └── automated_test.sh         # Automated test suite script
├── COMPLEXITY_ANALYSIS.md        # Detailed algorithmic analysis
├── README.md                     # This file
└── LICENSE                       # MIT License
```

---

## 🚀 Getting Started

### Prerequisites
- C++ compiler with C++17 support (GCC 7+, Clang 5+, MSVC 2017+)
- Make (optional, for build automation)
- Bash (for running automated tests)

### Compilation

Navigate to the project root and compile:

```bash
g++ -std=c++17 -Wall -Wextra src/trie_autosuggest.cpp -o trie_autosuggest
```

### Running the Application

```bash
./trie_autosuggest
```

### Usage Guide

The interactive menu offers 5 options:

1. **🔍 Search Suggestions** - Enter a prefix to see matching words
   - Type `ap` → See: apartment, app, appetite, apple, apply, apricot
   - Press Enter (empty) → See all 49 dictionary words
   - Case doesn't matter: `AP` = `ap` = `Ap`

2. **➕ Add Word** - Dynamically expand the dictionary
   - New words persist during the session
   - Automatic validation and confirmation

3. **📊 Show Statistics** - View dictionary metrics
   - Total word count
   - Data structure details
   - Algorithm information

4. **❓ Help** - Comprehensive usage guide
   - Feature explanations
   - Example queries
   - Complexity overview

5. **🚪 Exit** - Clean program termination

---

## 🧪 Testing

### Automated Test Suite

Run the comprehensive automated tests:

```bash
bash test/automated_test.sh
```

**Test coverage includes:**
- ✅ Basic prefix search ("ap", "ba", "c")
- ✅ Edge cases (no matches, empty prefix)
- ✅ Case insensitivity
- ✅ Alphabetical sorting verification
- ✅ Dynamic word insertion
- ✅ Statistics display
- ✅ Input validation and whitespace handling

### Manual Testing

Refer to `test/test_cases.txt` for manual test scenarios and expected outputs.

---

## 📊 Complexity Analysis

### Quick Reference

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| **Insert** | O(L) | O(L) worst case |
| **Search Prefix** | O(L) | O(1) |
| **Get Suggestions** | O(L + K×M + K log K) | O(K×M) |
| **Memory Cleanup** | O(N) | O(H) |

**Legend:**
- **L**: Length of word/prefix
- **K**: Number of matching suggestions
- **M**: Average suggestion length
- **N**: Total Trie nodes
- **H**: Height of Trie (longest word)

### Detailed Analysis

For comprehensive complexity analysis including comparisons with alternative data structures, worst-case scenarios, and real-world performance metrics, see **[COMPLEXITY_ANALYSIS.md](COMPLEXITY_ANALYSIS.md)**.

---

## 🎨 Sample Output

```
╔════════════════════════════════════════════╗
║    TRIE-BASED PREFIX SEARCH ENGINE v2.0    ║
║    Intelligent Prefix-Based Search        ║
╚════════════════════════════════════════════╝

⏳ Loading dictionary...
✓ Dictionary loaded with 49 words in 0.296ms

------------------------------------------------
MENU:
  1. 🔍 Search Suggestions
  2. ➕ Add Word to Dictionary
  3. 📊 Show Statistics
  4. ❓ Help
  5. 🚪 Exit
------------------------------------------------
Enter choice: 1

Enter prefix (or press Enter for all): ap

Found 6 matches in 15μs:

   1. apartment
   2. app
   3. appetite
   4. apple
   5. apply
   6. apricot
```

---

## 🏗️ How It Works

### Trie Data Structure

The Trie (prefix tree) stores words character-by-character:

```
       (root)
      /  |  \
     a   b   c
    /    |    \
   p     a     a
  / \    |     |
 p   r   l     t
 |   |   |     |
...
```

**Key advantages:**
- Shared prefixes stored once (space-efficient)
- Search time independent of dictionary size
- Perfect for autocomplete and spell-check

### Algorithm Steps

1. **Insert**: Traverse/create nodes for each character → O(L)
2. **Search**: 
   - Find prefix node → O(L)
   - Collect all words in subtree → O(K×M)
   - Sort alphabetically → O(K log K)
3. **Memory**: Recursive post-order cleanup → O(N)

---

## 🎓 Educational Value

This project demonstrates understanding of:
- ✅ Tree-based data structures
- ✅ Recursive algorithms (DFS traversal)
- ✅ Dynamic memory management
- ✅ Time/space complexity analysis
- ✅ Algorithm optimization (sorting, caching)
- ✅ Software engineering best practices
- ✅ User experience design (CLI)

---

## 🔬 Performance Metrics

Real-world measurements from testing:

| Operation | Dictionary Size | Measured Time |
|-----------|----------------|---------------|
| Load dictionary | 49 words | ~0.3 ms |
| Search "ap" | 6 results | 15 μs |
| Search "" (all) | 49 results | ~100-200 μs |
| Insert word | 1 word | <1 μs |

**Conclusion**: Sub-millisecond performance suitable for real-time applications.

---

## 🛠️ Advanced Features

### Color Support

The CLI uses ANSI escape codes for color output. If colors don't display:
- **Windows**: Use Windows Terminal or enable VT100 support
- **Mac/Linux**: Should work out-of-the-box
- **Disable colors**: Remove Color namespace from source code

### Customization

**Expand dictionary**: Edit lines 260-270 in `src/trie_autosuggest.cpp` to add preloaded words

**Change colors**: Modify Color namespace (lines 14-22) with custom ANSI codes

**Adjust performance**: Comment out `std::sort()` call (line 182) for unsorted but faster results

---

## 🐛 Troubleshooting

**Compilation errors**:
- Ensure C++17 support: `g++ --version` (check >= 7.0)
- Use explicit flag: `-std=c++17`

**No color output**:
- Terminal may not support ANSI codes
- Try modern terminal: iTerm2, Windows Terminal, GNOME Terminal

**Memory issues**:
- Check with: `valgrind --leak-check=full ./trie_autosuggest`
- Should show 0 bytes definitely lost

---

## 📚 Further Reading

- [Trie Data Structure - Wikipedia](https://en.wikipedia.org/wiki/Trie)
- [C++ Standard Library - std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map)
- [Big O Notation Guide](https://www.bigocheatsheet.com/)

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

**Educational Project** - Demonstrating advanced data structures and algorithms

For questions, improvements, or bug reports, feel free to open an issue or submit a pull request!

---

## 🌟 Acknowledgments

- **Data Structure**: Donald Knuth (The Art of Computer Programming)
- **Inspiration**: Modern autocomplete systems in production applications
- **Testing**: Community feedback and real-world usage patterns

---

<div align="center">

**Made with ❤️ and C++17**

⭐ Star this repo if you found it helpful!

</div>
