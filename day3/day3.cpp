#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Rect {
    int id;
    int x, y;
    int width, height;
};

std::vector<Rect> readInput() {
    std::vector<Rect> res;
    res.reserve(1000 * 1000); // at least 1000 square inches

    std::ifstream ifs(std::string(ROOT_DIR) + "/day3/input.txt");
    std::string line;
    while (getline(ifs, line)) {
        auto extract = [line](int from, int to = ~0) { return atoi(line.substr(from + 1, to - from).c_str()); };

        int idTag = line.find('#');
        int posTag = line.find('@');
        int posSeparator = line.find(',');
        int sizeTag = line.find(':');
        int sizeSeparator = line.find('x');

        Rect rect;
        rect.id = extract(idTag, posTag - idTag);
        rect.x = extract(posTag, posSeparator);
        rect.y = extract(posSeparator, sizeTag);
        rect.width = extract(sizeTag, sizeSeparator);
        rect.height = extract(sizeSeparator);
        
        res.push_back(rect);
    }
    return res;
}

int calculatePart1(std::vector<Rect> rects) {
    int res = 0;

    // max size of the fabric our rects occupy were found to be exactly 999x999
    uint8_t fabric[999][999] = { 0 };
    for (auto rect : rects) {
        for (int x = rect.x; x < rect.x + rect.width; x++) {
            for (int y = rect.y; y < rect.y + rect.height; y++) {
                res += ++fabric[x][y] == 2;
            }
        }
    }
    return res;
}

int main() {
    auto rects = readInput();
    std::cout << "part 1 result is = " << calculatePart1(rects) << std::endl;

    return 0;
}
