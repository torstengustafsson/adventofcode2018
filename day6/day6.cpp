#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

const int INF = 32767; // 2^15-1
const int maxRadius = 100; // bad solution. stops infinite loop

struct Point {
    Point(int16_t x, int16_t y) : x(x), y(y) {}
    bool operator==(const Point& other) { return x == other.x && y == other.y; }
    int16_t x, y;
};

inline uint16_t manhattanDist(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

inline bool distShorterThanOthers(Point p, Point me, std::vector<Point> others) {
    for (auto other : others) {
        if (other == me) { continue; } // don't compare with yourself
        if (manhattanDist(other, p) <= manhattanDist(me, p)) {
            return false; // not shortest distance
        }
    }
    return true;
}

inline std::vector<Point> getPointsAroundPoint(Point center, uint16_t radius) {
    std::vector<Point> res;
    for (int x = center.x - radius; x <= center.x + radius; x++) {
        res.push_back(Point(x, center.y + radius));
        res.push_back(Point(x, center.y - radius));
    }
    for (int y = center.y - radius + 1; y <= center.y + radius - 1; y++) {
        res.push_back(Point(center.x + radius, y));
        res.push_back(Point(center.x - radius, y));
    }
    return res;
}

std::vector<Point> readInput() {
    std::vector<Point> res;
    std::ifstream ifs(std::string(ROOT_DIR) + "/day6/input.txt");

    std::string strX; // need to remove ','
    uint16_t y;
    while (ifs >> strX >> y) {
        uint16_t x = atoi(strX.substr(0, strX.length() - 1).c_str());
        res.push_back(Point(x, y));
    }
    return res;
}

uint16_t calculatePart1(std::vector<Point> points) {
    uint16_t res = 0;

    int16_t minX = INF, maxX = -INF, minY = INF, maxY = -INF;
    for (auto point : points) {
        minX = std::min(point.x, minX);
        maxX = std::max(point.x, maxX);
        minY = std::min(point.y, minY);
        maxY = std::max(point.y, maxY);
    }

    for (auto point : points) {
        if (point.x > minX && point.x < maxX && point.y > minY && point.y < maxY) {
            uint16_t currRadius = 1;
            uint16_t area = 1; // point is always closest to itself
            bool cont = true; // should continue?

            while (cont) { // expand outwards in all directions
                if (currRadius >= maxRadius) {
                    area = 0;
                    break; // since my solution doesn't handle all cases, do a "fuling" and break loop
                }
                cont = false;
                auto pointsAroundCenter = getPointsAroundPoint(point, currRadius);

                for (auto currPoint : pointsAroundCenter) {
                    if (distShorterThanOthers(currPoint, point, points)) {
                        area++;
                        cont = true;
                    }
                }
                currRadius++;
            }
            if (res < area) { res = area; }
        }
    }

    return res;
}

int main() {
    auto points = readInput();
    std::cout << "part 1 result is = " << calculatePart1(points) << std::endl;

    return 0;
}
