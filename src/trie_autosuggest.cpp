#include <algorithm>
#include <cctype>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace chrono;

// ==================== ANSI COLOR CODES ====================
namespace Color {
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string DIM = "\033[2m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string RED = "\033[31m";
} // namespace Color

// ==================== TRIE NODE STRUCTURE ====================
/**
 * TrieNode represents a single node in the Trie data structure.
 * Space Complexity: O(ALPHABET_SIZE) per node in worst case
 */
struct TrieNode {
  unordered_map<char, TrieNode *> children;
  bool isEndOfWord;
  TrieNode() : isEndOfWord(false) {}
};

// ==================== TRIE CLASS ====================
/**
 * Trie implements a prefix tree for efficient word storage and retrieval.
 */
class Trie {
private:
  TrieNode *root;
  int wordCount;

  /**
   * Recursively destroy all Trie nodes
   * Time Complexity: O(N) where N = total nodes
   */
  void destroyTrie(TrieNode *node) {
    if (!node)
      return;
    for (auto &pair : node->children) {
      destroyTrie(pair.second);
    }
    delete node;
  }

  /**
   * Recursively collect all words from a given node
   * Time Complexity: O(K * M) where K = words, M = avg length
   */
  void collectSuggestions(TrieNode *node, string currentPrefix,
                          vector<string> &results) const {
    if (node->isEndOfWord) {
      results.push_back(currentPrefix);
    }
    for (const auto &[key, child] : node->children) {
      collectSuggestions(child, currentPrefix + key, results);
    }
  }

  /**
   * Find TrieNode for a given prefix
   * Time Complexity: O(L) where L = prefix length
   */
  TrieNode *searchPrefix(const string &prefix) const {
    TrieNode *current = root;
    for (char ch : prefix) {
      if (current->children.find(ch) == current->children.end()) {
        return nullptr;
      }
      current = current->children[ch];
    }
    return current;
  }

  string toLower(const string &str) const {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
  }

  string trim(const string &str) const {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
      return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
  }

public:
  Trie() : wordCount(0) { root = new TrieNode(); }
  ~Trie() { destroyTrie(root); }

  /**
   * Insert word into Trie - Time: O(L), Space: O(L) worst case
   */
  void insert(const string &word) {
    string cleanWord = toLower(trim(word));
    if (cleanWord.empty())
      return;

    TrieNode *current = root;
    for (char ch : cleanWord) {
      if (!isalpha(ch))
        continue;
      if (current->children.find(ch) == current->children.end()) {
        current->children[ch] = new TrieNode();
      }
      current = current->children[ch];
    }
    if (!current->isEndOfWord) {
      current->isEndOfWord = true;
      wordCount++;
    }
  }

  /**
   * Get sorted suggestions for prefix
   * Time: O(L + K*M + K*log(K)) where K = results, M = avg length
   */
  vector<string> getSuggestions(const string &prefix) const {
    vector<string> results;
    string cleanPrefix = toLower(trim(prefix));
    TrieNode *prefixNode =
        cleanPrefix.empty() ? root : searchPrefix(cleanPrefix);

    if (!prefixNode)
      return results;
    collectSuggestions(prefixNode, cleanPrefix, results);
    sort(results.begin(), results.end());
    return results;
  }

  int getWordCount() const { return wordCount; }
};

// ==================== UI HELPER FUNCTIONS ====================

void printBanner() {
  cout << "\n" << Color::BOLD << Color::CYAN;
  cout << "  ╔══════════════════════════════════════════════════════╗\n";
  cout << "  ║                                                      ║\n";
  cout << "  ║        TRIE AUTO-SUGGEST SYSTEM v2.0                ║\n";
  cout << "  ║        Intelligent Prefix-Based Search              ║\n";
  cout << "  ║                                                      ║\n";
  cout << "  ╚══════════════════════════════════════════════════════╝";
  cout << Color::RESET << "\n\n";
}

void printLine(char c = '-', int len = 54) {
  cout << "  " << Color::DIM << string(len, c) << Color::RESET << "\n";
}

void printThickLine() {
  cout << "  " << Color::BOLD << Color::CYAN << string(54, '=') << Color::RESET
       << "\n";
}

void printSuccess(const string &msg) {
  cout << "  " << Color::GREEN << Color::BOLD << "✓" << Color::RESET
       << Color::GREEN << " " << msg << Color::RESET << "\n";
}

void printError(const string &msg) {
  cout << "  " << Color::RED << Color::BOLD << "✗" << Color::RESET << Color::RED
       << " " << msg << Color::RESET << "\n";
}

void printInfo(const string &msg) {
  cout << "  " << Color::BLUE << "ℹ " << msg << Color::RESET << "\n";
}

void printMenu() {
  cout << "\n";
  printThickLine();
  cout << "\n  " << Color::BOLD << Color::YELLOW
       << "SELECT AN OPTION:" << Color::RESET << "\n\n";
  cout << "    " << Color::BOLD << Color::CYAN << "[1]" << Color::RESET
       << "  Search for Suggestions\n";
  cout << "    " << Color::BOLD << Color::CYAN << "[2]" << Color::RESET
       << "  Add New Word\n";
  cout << "    " << Color::BOLD << Color::CYAN << "[3]" << Color::RESET
       << "  View Statistics\n";
  cout << "    " << Color::BOLD << Color::CYAN << "[4]" << Color::RESET
       << "  Help & Documentation\n";
  cout << "    " << Color::BOLD << Color::CYAN << "[5]" << Color::RESET
       << "  Exit Program\n\n";
  printThickLine();
  cout << "\n  " << Color::YELLOW << "→ Your choice: " << Color::RESET;
}

void printHelp() {
  cout << "\n";
  printThickLine();
  cout << "\n  " << Color::BOLD << Color::MAGENTA << "HELP & DOCUMENTATION"
       << Color::RESET << "\n\n";
  printLine();
  cout << "\n  " << Color::BOLD << Color::CYAN << "How to Use:" << Color::RESET
       << "\n\n";
  cout << "    • Enter any prefix to see matching words\n";
  cout << "    • Press Enter (empty) to display all words\n";
  cout << "    • Search is case-insensitive: \"AP\" = \"ap\"\n";
  cout << "    • Add words dynamically during runtime\n\n";
  printLine();
  cout << "\n  " << Color::BOLD << Color::CYAN << "Examples:" << Color::RESET
       << "\n\n";
  cout << "    Prefix: " << Color::YELLOW << "\"ap\"" << Color::RESET
       << "  →  apple, app, apply, apricot\n";
  cout << "    Prefix: " << Color::YELLOW << "\"ba\"" << Color::RESET
       << "  →  ball, banana, bat, battle\n";
  cout << "    Prefix: " << Color::YELLOW << "\"\"" << Color::RESET
       << "    →  Displays all dictionary words\n\n";
  printLine();
  cout << "\n  " << Color::BOLD << Color::CYAN
       << "Complexity Analysis:" << Color::RESET << "\n\n";
  cout << "    • Insert:  " << Color::GREEN << "O(L)" << Color::RESET
       << " — L = word length\n";
  cout << "    • Search:  " << Color::GREEN << "O(L + K×M)" << Color::RESET
       << " — K = results, M = avg length\n";
  cout << "    • Space:   " << Color::GREEN << "O(N×M)" << Color::RESET
       << " — N = words, M = avg length\n\n";
  printThickLine();
  cout << "\n";
}

// ==================== MAIN FUNCTION ====================
int main() {
  Trie trie;
  printBanner();

  // Preload Dictionary
  vector<string> dictionary = {
      "apple",    "app",         "apply",  "apricot", "apartment", "appetite",
      "banana",   "bat",         "ball",   "battle",  "badge",     "balance",
      "cat",      "caterpillar", "cattle", "camera",  "castle",    "canvas",
      "dog",      "dove",        "doll",   "dragon",  "dance",     "danger",
      "elephant", "egg",         "eagle",  "earth",   "energy",    "fish",
      "frog",     "falcon",      "forest", "fortune", "goat",      "grape",
      "giraffe",  "galaxy",      "garden", "hat",     "home",      "horse",
      "harbor",   "harmony",     "ice",    "igloo",   "island",    "iron",
      "imagine"};

  cout << "  " << Color::BLUE << "Initializing system..." << Color::RESET
       << "\n";
  cout << "  " << Color::DIM
       << "Loading dictionary and building trie structure..." << Color::RESET
       << "\n\n";

  auto startLoad = high_resolution_clock::now();
  for (const string &word : dictionary) {
    trie.insert(word);
  }
  auto endLoad = high_resolution_clock::now();
  auto loadDuration = duration_cast<microseconds>(endLoad - startLoad);

  printSuccess("System ready! Loaded " + to_string(trie.getWordCount()) +
               " words in " + to_string(loadDuration.count() / 1000.0) + "ms");

  // Main Loop
  while (true) {
    printMenu();

    int choice;
    if (!(cin >> choice)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "\n";
      printError("Invalid input. Please enter a number between 1-5.");
      continue;
    }
    cin.ignore();

    if (choice == 1) {
      // SEARCH
      cout << "\n  " << Color::YELLOW << "→ Enter search prefix" << Color::DIM
           << " (or press Enter to show all)" << Color::RESET << ": ";
      string prefix;
      getline(cin, prefix);

      auto start = high_resolution_clock::now();
      vector<string> suggestions = trie.getSuggestions(prefix);
      auto end = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(end - start);

      cout << "\n";
      if (suggestions.empty()) {
        printError("No suggestions found for \"" + prefix + "\"");
        cout << "  " << Color::DIM
             << "Try a different prefix or check spelling." << Color::RESET
             << "\n";
      } else {
        printThickLine();
        cout << "\n  " << Color::BOLD << Color::GREEN << "✓ Found "
             << suggestions.size() << " match"
             << (suggestions.size() > 1 ? "es" : "") << Color::RESET
             << Color::DIM << " (in " << duration.count() << "μs)"
             << Color::RESET << "\n\n";
        printLine();
        cout << "\n";
        int count = 1;
        for (const string &word : suggestions) {
          cout << "    " << Color::DIM << "[" << setw(2) << count++ << "]"
               << Color::RESET << "  " << Color::CYAN << word << Color::RESET
               << "\n";
        }
        cout << "\n";
        printThickLine();
      }
      cout << "\n";

    } else if (choice == 2) {
      // ADD
      cout << "\n  " << Color::YELLOW
           << "→ Enter new word to add: " << Color::RESET;
      string word;
      getline(cin, word);

      cout << "\n";
      if (word.empty() || word.find_first_not_of(" \t\n\r") == string::npos) {
        printError("Cannot add empty word. Please try again.");
      } else {
        int oldCount = trie.getWordCount();
        trie.insert(word);
        int newCount = trie.getWordCount();

        if (newCount > oldCount) {
          printSuccess("Successfully added \"" + Color::BOLD + word +
                       Color::RESET + Color::GREEN + "\" to dictionary!");
          cout << "  " << Color::DIM << "Dictionary now contains " << newCount
               << " words." << Color::RESET << "\n";
        } else {
          printInfo("Word \"" + word + "\" already exists in dictionary.");
        }
      }
      cout << "\n";

    } else if (choice == 3) {
      // STATS
      cout << "\n";
      printThickLine();
      cout << "\n  " << Color::BOLD << Color::MAGENTA << "SYSTEM STATISTICS"
           << Color::RESET << "\n\n";
      printLine();
      cout << "\n  " << Color::CYAN << "Total Words:        " << Color::RESET
           << Color::BOLD << trie.getWordCount() << Color::RESET << "\n";
      cout << "  " << Color::CYAN << "Data Structure:     " << Color::RESET
           << "Trie (Prefix Tree)\n";
      cout << "  " << Color::CYAN << "Search Algorithm:   " << Color::RESET
           << "Prefix Matching + DFS Traversal\n";
      cout << "  " << Color::CYAN << "Result Sorting:     " << Color::RESET
           << "Alphabetical (std::sort)\n";
      cout << "  " << Color::CYAN << "Performance:        " << Color::RESET
           << "Sub-millisecond search times\n\n";
      printLine();
      cout << "\n  " << Color::DIM
           << "Tip: Press Enter at search prompt to view all words"
           << Color::RESET << "\n\n";
      printThickLine();
      cout << "\n";

    } else if (choice == 4) {
      // HELP
      printHelp();

    } else if (choice == 5) {
      // EXIT
      cout << "\n";
      printThickLine();
      cout << "\n  " << Color::GREEN << Color::BOLD << "✓" << Color::RESET
           << Color::GREEN << " Thank you for using Trie Auto-Suggest System!"
           << Color::RESET << "\n";
      cout << "  " << Color::DIM << "Session terminated. Goodbye!"
           << Color::RESET << "\n\n";
      printThickLine();
      cout << "\n";
      break;

    } else {
      cout << "\n";
      printError("Invalid choice. Please select a number between 1-5.");
      cout << "\n";
    }
  }

  return 0;
}
