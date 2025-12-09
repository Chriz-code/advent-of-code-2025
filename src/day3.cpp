#include "utils/filereader.cpp"
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

namespace Day3 {
    class Solution {
    private:
        std::stringstream TEST_VALUE = std::stringstream("987654321111111\n811111111111119\n234234234234278\n818181911112111");

        int charToInt(char c) {
            return c - '0';
        }

        long long sum(std::string numbers) {
            return stoll(numbers);
        }

        long long sum(std::vector<int> numbers) {
            std::string result;
            for (int number : numbers) {
                result += std::to_string(number);
            }
            std::cout << "line: " << result << std::endl;
            return sum(result);
        }

        int combine(int a, int b) {
            return std::stoi(std::to_string(a) + std::to_string(b));
        }

        int findIndexThatFits(std::vector<int> arr, int value, int startStep) {
            for (int i = startStep; i < arr.size(); i++) {
                if (value > arr[i]) {
                    return i;
                }
            }

            return -1;
        }

        long long calcJoltage(int noBatteries, std::string line) {
            if (noBatteries >= line.length()) {
                return sum(line);
            }

            std::vector<int> batteries({ charToInt(line[0]) });
            for (int ci = 1; ci < line.length(); ci++) {
                int charge = charToInt(line[ci]);

                int socketsLeft = noBatteries - batteries.size();
                int batteriesLeft = line.length() - ci;

                if (socketsLeft >= batteriesLeft) {
                    batteries.push_back(charge);
                    continue;
                }

                int index = findIndexThatFits(batteries, charge, std::max(0, noBatteries - batteriesLeft));

                if (index != -1) {
                    batteries.resize(index);
                    batteries.push_back(charge);
                }
                else if (socketsLeft > 0) {
                    batteries.push_back(charge);
                }
            }
            return sum(batteries);
        }

    public:
        Solution* part1Test() {
            std::string line;
            long long sum = 0;
            while (getline(TEST_VALUE, line)) {
                int numbers[2] = { charToInt(line[0]), charToInt(line[1]) };
                for (int i = 2; i < line.length(); i++) {
                    int num = charToInt(line[i]);
                    if (i + 1 < line.length() && num > numbers[0]) {
                        numbers[0] = num;
                        numbers[1] = 0;
                    }
                    else if (num > numbers[1]) {
                        numbers[1] = num;
                    }
                }
                sum += combine(numbers[0], numbers[1]);
            }
            std::cout << "Love " << sum << std::endl;
            return this;
        }

        // 17922 too high
        // 17766
        Solution* part1() {
            Utils::FileReader reader("inputs/day3.txt");

            std::string line;
            long long sum = 0;

            while (getline(*reader.stream, line)) {
                int numbers[2] = { charToInt(line[0]), charToInt(line[1]) };
                for (int i = 2; i < line.length(); i++) {
                    int num = charToInt(line[i]);
                    if (i + 1 < line.length() && num > numbers[0]) {
                        numbers[0] = num;
                        numbers[1] = 0;
                    }
                    else if (num > numbers[1]) {
                        numbers[1] = num;
                    }
                }
                sum += combine(numbers[0], numbers[1]);
            }
            std::cout << "Love " << sum << std::endl;
            return this;
        }

        Solution* part2Test() {
            std::string line;
            long long sum = 0;
            while (getline(TEST_VALUE, line)) {
                sum += calcJoltage(12, line);
            }
            std::cout << "Love " << sum << std::endl;
            return this;
        }

        Solution* part2() {
            Utils::FileReader reader("inputs/day3.txt");

            std::string line;
            long long sum = 0;

            while (getline(*reader.stream, line)) {
                sum += calcJoltage(12, line);
            }

            std::cout << "Love " << sum << std::endl;
            return this;
        }
    };
}
