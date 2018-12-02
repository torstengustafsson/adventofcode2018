#include <iostream>
#include <fstream>
#include <vector>
#include <map>

std::vector<int> readInput() {
    std::vector<int> res;

    std::ifstream ifs(std::string(ROOT_DIR) + "/day1/input.txt");
    char sign;
    int val;
    while (ifs >> sign >> val) {
        res.push_back(sign == '+' ? val : -val);
    }
    return res;
}

int calculatePart1(std::vector<int> vals) {
    int res = 0;

    for(auto val : vals) {
        res += val;
    }

    return res;
}

int calculatePart2(std::vector<int> vals) {
    int res;

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
    auto vals = readInput();
    std::cout << "part 1 result is = " << calculatePart1(vals) << std::endl;
    std::cout << "part 2 result is = " << calculatePart2(vals) << std::endl;
}
