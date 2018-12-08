#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <array>

enum class Activity {
    BEGINS,
    FALLS_ASLEEP,
    WAKES_UP
};

struct Date {
    int year, month, day;
    int hour, minute;

    static Date toDate(std::string s) {
        Date res;
        res.year = atoi(s.substr(0, 4).c_str());
        res.month = atoi(s.substr(5, 2).c_str());
        res.day = atoi(s.substr(8, 2).c_str());
        res.minute = atoi(s.substr(11, 2).c_str());
        res.minute = atoi(s.substr(14, 2).c_str());
        return res;
    }
};

struct Entry {
    Date date;
    int id;
    Activity activity;
};

std::vector<Entry> readInput() {
    std::vector<Entry> res;

    std::ifstream ifs(std::string(ROOT_DIR) + "/day4/input.txt");
    std::string line;
    int currId;
    while (getline(ifs, line)) {
        auto extract = [line](size_t from, size_t to = ~0) { return line.substr(from + 1, to - from - 1); };

        size_t dateStart = line.find('[');
        size_t dateEnd = line.find(']');

        Entry entry;
        entry.date = Date::toDate(extract(dateStart, dateEnd));
        
        std::string text = extract(dateEnd + 1); // skip ws
        if (text.substr(0, 5) == "Guard") {
            size_t start = text.find('#');
            size_t end = text.find(' ', start);
            auto s = text.substr(text.find('#') + 1, text.find(' ', start) - text.find('#'));
           currId = atoi(text.substr(text.find('#') + 1, text.find(' ', start) - text.find('#')).c_str());
           entry.activity = Activity::BEGINS;
        }
        else if (text == "falls asleep") {
            entry.activity = Activity::FALLS_ASLEEP;
        }
        else if (text == "wakes up") {
            entry.activity = Activity::WAKES_UP;
        }

        entry.id = currId;

        res.push_back(entry);
    }
    return res;
}

// struct containing a default-initialized int (why do I use C++ for this?!)
struct DefInt {
    inline operator int() { return val; }
    inline void operator+= (const int& other) { val += other; }
private:
    int val = 0;
};

int calculatePart1(std::vector<Entry> entries) {
    std::map <int, DefInt> guardAmountMins;
    std::map <int, std::array<DefInt, 60>> guardSleepMins;
    
    int startMin, sleepiestGuard;
    int maxMinAsleep = 0;
    for (auto entry : entries) {
        if (entry.activity == Activity::FALLS_ASLEEP) {
            startMin = entry.date.hour == 23 ? 0 : entry.date.minute; // guards may begin a few minutes before 00:00
        }
        else if (entry.activity == Activity::WAKES_UP) {
            int endMin = entry.date.minute;
            guardAmountMins[entry.id] += endMin - startMin;

            for (int i = startMin; i < endMin; i++) {
                guardSleepMins[entry.id][i] += 1;
            }

            if(guardAmountMins[entry.id] > maxMinAsleep) {
                maxMinAsleep = guardAmountMins[entry.id];
                sleepiestGuard = entry.id;
            }
        }
    }

    int favouriteMinute;
    int maxNumMins = 0;
    for (int minute = 0; minute < 60; minute++) {
        int amount = guardSleepMins[sleepiestGuard][minute];
        if (maxNumMins < amount) {
            favouriteMinute = minute;
            maxNumMins = amount;
        }
    }
    return sleepiestGuard * favouriteMinute;
}

int calculatePart2(std::vector<Entry> entries) {
    return 0;
}

int main() {
    auto entries = readInput();
    std::cout << "part 1 result is = " << calculatePart1(entries) << std::endl;

    return 0;
}
