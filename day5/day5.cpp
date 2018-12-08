#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <algorithm>

std::string readInput() {
    std::ifstream ifs(std::string(ROOT_DIR) + "/day5/input.txt");
    std::string line;
    ifs >> line;
    return line;
}

// Capitalized letters have a distance of 32 characters in the Ascii table. We
// consider chars outside Ascii letters as undefined behaviour since
// we don't allow other chars than a-z and A-Z.
inline bool reacts(const char& a, const char& b) {
    return (a - 32 == b) || (a + 32 == b);
}

// c must be the capitalized version of the letter
inline std::string removeLetter(std::string s, char c) {
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
    s.erase(std::remove(s.begin(), s.end(), c + 32), s.end());
    return s;
}

uint32_t calculatePart1(std::string polymer) {
    std::stack<int> stored;
    int curr = 0;
    int next = 1;

    while (curr < polymer.length()) {
        if (reacts(polymer[curr], polymer[next])) {
            if (stored.empty()) {
                curr = next + 1;
                next = curr + 1;
            }
            else {
                curr = stored.top();
                stored.pop();
                next++;
            }
        }
        else {
            stored.push(curr);
            curr = next;
            next = curr + 1;
        }
    }
    return static_cast<int>(stored.size());
}

uint32_t calculatePart2(std::string polymer) {
    uint32_t res = ~0; // infinity
    for (char c = 65; c < 90; c++) { // loop through the alphabet (A-Z)
        std::string s = removeLetter(polymer, c);
        auto curr = calculatePart1(s);
        if (curr < res) {
            res = curr;
        }
    }

    return res;
}

int main() {
    auto entries = readInput();
    std::cout << "part 1 result is = " << calculatePart1(entries) << std::endl;
    std::cout << "part 2 result is = " << calculatePart2(entries) << std::endl;

    return 0;
}
