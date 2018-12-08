#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

std::string readInput() {
    std::ifstream ifs(std::string(ROOT_DIR) + "/day5/input.txt");
    std::string line;
    ifs >> line;
    return line;
}

// Capitalized letters have a distance of 32 characters in the Ascii table. We 
// consider chars outside Ascii letters as accepted undefined behaviour since 
// we don't allow other chars than a-z and A-Z.
inline bool reacts(const char& a, const char& b) {
    return (a - 32 == b) || (a + 32 == b);
}

int calculatePart1(std::string polymer) {
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
    return stored.size();
}

int main() {
    auto entries = readInput();
    std::cout << "part 1 result is = " << calculatePart1(entries) << std::endl;

    return 0;
}
