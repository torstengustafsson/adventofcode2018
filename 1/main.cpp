#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void clear(std::ifstream& ifs) {
    ifs.clear();                 // clear fail and eof bits
    ifs.seekg(0, std::ios::beg); // back to the start!
}

int calculatePart1(std::ifstream& ifs) {
    int res = 0;

    char sign;
    int val;
    while (ifs >> sign >> val) {
        res += sign == '+' ? val : -val;
    }

    return res;
}

int calculatePart2(std::ifstream& ifs) {
    int res;
    std::vector<int> vals;

    // read values
    char sign;
    int val;
    while (ifs >> sign >> val) {
        vals.push_back(sign == '+' ? val : -val);
    }

    // find first repeating frequency
    bool found = false;
    int currFreq = 0;
    std::map<int, int> valmap;
    while (!found) {
        for (int val : vals) {
            currFreq += val;
            if (++valmap[currFreq] > 1) {
                found = true;
                res = currFreq;
                break;
            }
        }
    }

    return res;
}

int main() {
    std::ifstream ifs(std::string(AOC1DIR) + "/input.txt");
    std::cout << "part 1 result is = " << calculatePart1(ifs) << std::endl;
    clear(ifs);
    std::cout << "part 2 result is = " << calculatePart2(ifs) << std::endl;
}
