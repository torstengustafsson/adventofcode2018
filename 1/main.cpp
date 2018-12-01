#include <iostream>
#include <fstream>

int main() {
    std::ifstream ifs(std::string(AOC1DIR) + "/input.txt");
    int res = 0;

    char sign;
    int val;
    while (ifs >> sign >> val) {
        res += sign == '+' ? val : -val;
    }

    std::cout << "result is = " << res << std::endl;
}
