#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include <vector>
#include <string>
#include <sstream>
#include <map>

namespace Day11 {
    class Solution {
    private:
        const char* TEST_INPUT =
            "aaa: you hhh\n"
            "you: bbb ccc\n"
            "bbb: ddd eee\n"
            "ccc: ddd eee fff\n"
            "ddd: ggg\n"
            "eee: out\n"
            "fff: out\n"
            "ggg: out\n"
            "hhh: ccc fff iii\n"
            "iii: out";

        std::map<std::string, std::vector<std::string>> toMap(std::stringstream& stream) {
            using namespace std;
            string line;
            map<string, vector<string>> result;
            while (getline(stream, line)) {
                vector<string> split = Utils::StringUtils::split(line, ':');
                string key = split[0];

                vector<string> values = Utils::StringUtils::split(split[1], ' ');
                auto ne = remove_if(values.begin(), values.end(), [](string value) {
                    return value.empty();
                });
                values.erase(ne);
                result[key] = values;
            }
            return result;
        }

    public:
        Solution* part1Test() {
            std::stringstream stream(TEST_INPUT);
            auto map = toMap(stream);
            return this;
        }
    };
}