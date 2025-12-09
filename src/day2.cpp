#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "utils/range.cpp"

namespace Day2 {
    using namespace std;

    class Solution {
    private:
        const string inputFile = "inputs/day2.txt";
        ifstream* stream() {
            ifstream* inputStream = new ifstream(inputFile);

            if (!(*inputStream).is_open()) {
                cout << "Unable to open file" << endl;
                return nullptr;
            }
            return inputStream;
        }

        string readToString(ifstream* stream) {
            string line;
            string result;
            while (getline(*stream, line)) {
                result += line;
            }
            return result;
        }

        Utils::Range parseRange(string line) {
            int splitIdx = line.find('-');
            string start = line.substr(0, splitIdx);
            string end = line.substr(splitIdx + 1);
            long long startNum = stoll(start);
            long long endNum = stoll(end);
            cout << startNum << ":" << splitIdx << ":" << endNum << endl;
            return { startNum, endNum };
        }

        bool isPalindrome(string value) {
            return value.length() % 2 == 0 && value.substr(0, value.length() / 2) == value.substr(value.length() / 2);
        }

        bool isRepeating(string value) {
            if (isPalindrome(value)) {
                return true;
            }
            //e.g., 1188511885 + 1188511885
            string doubled = value + value;
            // find before half point 1188511885 in 1885"1188511885"11885
            if (doubled.find(value, 1) < value.length()) {
                return true;
            }
            return false;
        }

    public:
        Solution* part1() {
            stringstream input(readToString(stream()));
            string line;
            long long sumOfPalindromes = 0L;
            while (getline(input, line, ',')) {
                Utils::Range range = parseRange(line);

                for (long long value = range.start; value <= range.end; value++) {
                    if (isPalindrome(to_string(value))) {
                        sumOfPalindromes += value;
                    }
                }
            }
            cout << "Here lies " << to_string(sumOfPalindromes) << endl;
            return this;
        }

        //28858486244
        Solution* part2() {
            stringstream input(readToString(stream()));
            string line;
            long long sumOfPalindromes = 0L;
            while (getline(input, line, ',')) {
                Utils::Range range = parseRange(line);

                for (long long value = range.start; value <= range.end; value++) {
                    if (isRepeating(to_string(value))) {
                        sumOfPalindromes += value;
                    }
                }
            }
            cout << "Here lies " << to_string(sumOfPalindromes) << endl;
            return this;
        }
    };
}
