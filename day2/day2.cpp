#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

const int LETTERS = 26;

int calculatePart1(std::ifstream& ifs) {
    int twices = 0;
    int thrices = 0;

    std::string line;
    while (std::getline(ifs, line)) {
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
        twices += twice; // 0 or 1
        thrices += thrice;
    }

    return twices * thrices;
}

int main() {
    std::ifstream ifs(std::string(ROOT_DIR) + "/day2/input.txt");
    std::cout << "part 1 result is = " << calculatePart1(ifs) << std::endl;

    return 0;
}
