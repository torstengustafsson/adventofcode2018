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
        auto extract = [line](size_t from, size_t to = ~0) { return atoi(line.substr(from + 1, to - from).c_str()); };

        size_t idTag = line.find('#');
        size_t posTag = line.find('@');
        size_t posSeparator = line.find(',');
        size_t sizeTag = line.find(':');
        size_t sizeSeparator = line.find('x');

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

// quick and dirty solution (duplicate of part 1!)
int calculatePart2(std::vector<Rect> rects) {
    uint8_t fabric[999][999] = { 0 };
    for (auto rect : rects) {
        for (int x = rect.x; x < rect.x + rect.width; x++) {
            for (int y = rect.y; y < rect.y + rect.height; y++) {
                fabric[x][y]++;
            }
        }
    }

    for (auto rect : rects) {
        for (int x = rect.x; x < rect.x + rect.width; x++) {
            for (int y = rect.y; y < rect.y + rect.height; y++) {
                if(fabric[x][y] != 1) { goto next; } // skip to next if any pos overlaps
            }
        }
        return rect.id; // found!
        next: continue; // goto is nice
    }
    return 0;
}

int main() {
    auto rects = readInput();
    std::cout << "part 1 result is = " << calculatePart1(rects) << std::endl;
    std::cout << "part 2 result is = " << calculatePart2(rects) << std::endl;

    return 0;
}
