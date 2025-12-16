#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include <vector>
#include <string>
#include <sstream>
#include <map>

namespace Day11 {
    struct test {
        const char* INPUT =
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
    };

    class Solution {
        using device = std::map<std::string, std::vector<std::string>>;

    private:
        test t;

        device toMap(std::stringstream& stream) {
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

        int dfs(device& devices, std::string next) {
            if (next == "out") return 1;

            int ret = 0;
            for (auto& ng : devices[next]) {
                ret += dfs(devices, ng);
            }
            return ret;
        };

    public:
        Solution* part1Test() {
            std::stringstream stream(t.INPUT);
            auto map = toMap(stream);
            std::cout << "Dedotaded wam: " << dfs(map, "you") << std::endl;
            return this;
        }

        Solution* part1() {
            Utils::FileReader reader("inputs/day11.txt");
            std::stringstream stream = reader.toStringStream();
            auto map = toMap(stream);
            std::cout << "Dedotaded wam: " << dfs(map, "you") << std::endl;
            return this;
        }
    };
}