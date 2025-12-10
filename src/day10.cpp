#include "utils/stringutils.cpp"
#include <string>
#include <vector>
#include <functional>
#include <sstream>

namespace Day10 {
    class Machine {
        typedef std::vector<int> Button;

    private:
        std::function<std::vector<std::string>(std::string, char)> split = Utils::StringUtils::split;

        std::string src;
        std::string display;
        std::vector<Button> buttons;
        std::vector<int> joltage;

        std::vector<Button> to_buttons(std::vector<std::string> parts) {
            using namespace std;

            vector<Button> result;
            for (auto& p : parts) {
                p.erase(remove(p.begin(), p.end(), '('), p.end());
                p.erase(remove(p.begin(), p.end(), ')'), p.end());
                Button button;
                vector<string> nums = split(p, ',');
                for (auto& n : nums) {
                    button.push_back(stoi(n));
                }
                result.push_back(button);
            }
            return result;
        }

        std::vector<int> toJoltage(std::string joltages) {
            std::vector<int> result;
            joltages.erase(remove(joltages.begin(), joltages.end(), '{'), joltages.end());
            joltages.erase(remove(joltages.begin(), joltages.end(), '}'), joltages.end());
            for (auto& s : split(joltages, ',')) {
                result.push_back(stoi(s));
            }
            return result;
        }

    public:
        Machine(std::string line) {
            std::vector<std::string> parts = split(line, ' ');
            src = line;
            display = *parts.begin();
            buttons = to_buttons(std::vector<std::string>(parts.begin() + 1, parts.end() - 1));
            joltage = toJoltage(parts.back());
        }
    };


    class Solution {
    private:
        const char* TEST_INPUT =
            "[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}\n"
            "[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}\n"
            "[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}";
    public:
        Solution* part1Test() {
            std::stringstream stream(TEST_INPUT);
            std::vector<Machine> machines;
            std::string line;
            while (getline(stream, line)) {
                machines.push_back(Machine(line));
            }
            return this;
        }
    };
}
