#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <assert.h>

const int LETTERS = 26;

std::vector<std::string> readInput() {
    std::vector<std::string> res;

    std::ifstream ifs(std::string(ROOT_DIR) + "/day2/input.txt");
    std::string line;
    while (std::getline(ifs, line)) {
        res.push_back(line);
    }
    return res;
}

int calculatePart1(std::vector<std::string> lines) {
    int twices = 0;
    int thrices = 0;

    for (auto line : lines) {
        int charmap[LETTERS] = { 0 }; // storage for lower case ascii letters
        bool twice = false;
        bool thrice = false;

        for (auto ch : line) {
            charmap[ch - 97]++; // we know input only contains lower case charactes (ascii 97-122)
        }

        for (int i = 0; i < LETTERS; i++) {
            if (charmap[i] == 2) { twice = true; }
            if (charmap[i] == 3) { thrice = true; }
        }

        twices += twice;   // 0 or 1
        thrices += thrice;
    }

    return twices * thrices;
}

std::string calculatePart2(std::vector<std::string> lines) {
    for (int line1 = 0; line1 < lines.size(); line1++) {
        for (int line2 = line1; line2 < lines.size(); line2++) {
            if (line1 == line2) { continue; } // don't compare line with itself

            int lineLength = lines[line1].length();
            assert(lineLength == lines[line2].length()); // all lines must be same length

            std::string sameChars("");

            for (int i = 0; i < lineLength; i++) {
                if (lines[line1][i] == lines[line2][i]) {
                    sameChars += lines[line1][i];
                }
            }

            // should only exist one pair which differs by exactly 1 char
            if (sameChars.length() == lineLength - 1) {
                return sameChars;
            }
        }
    }
    return ""; // not found
}

int main() {
    auto lines = readInput();
    std::cout << "part 1 result is = " << calculatePart1(lines) << std::endl;
    std::cout << "part 2 result is = " << calculatePart2(lines) << std::endl;

    return 0;
}
