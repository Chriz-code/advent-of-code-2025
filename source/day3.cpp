#include "utils/filereader.cpp"
#include <string>

class Day3
{
private:
    int findIndexOfLargestNumberIn(string line) {
        int max = -1;
        int result = 0;
        for (int i = 0; i < line.length(); i++) {
            int value = line[i] - '0';
            if (value > max) {
                max = value;
                result = i;
            }
        }
        return result;
    }

public:
// 17922 too high
    Day3 *part1()
    {
        FileReader reader("inputs/day3.txt");

        string line;
        long long sum = 0;
        while (getline(*reader.stream, line)) {
            int index = findIndexOfLargestNumberIn(line);
            char first = line[index];
            line[index] = '0';
            index = findIndexOfLargestNumberIn(line);
            char second = line[index];

            sum += stoll(string({first, second}));
        }
        cout << "Love " << sum << endl;
        return this;
    }
};