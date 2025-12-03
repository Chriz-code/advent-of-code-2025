#include "utils/filereader.cpp"
#include <string>
#include <sstream>
#include <vector>

class Day3
{
private:
    int charToInt(char c)
    {
        return c - '0';
    }

    int combine(int a, int b) {
        return stoi(to_string(a) + to_string(b));
    }

    int findIndexOfLargestNumberIn(string line)
    {
        int max = -1;
        int result = 0;
        for (int i = 0; i < line.length(); i++)
        {
            int value = line[i] - '0';
            if (value > max)
            {
                max = value;
                result = i;
            }
        }
        return result;
    }

public:
    // 17922 too high
    // 17766
    Day3 *part1()
    {
        FileReader reader("inputs/day3.txt");

        string line;
        long long sum = 0;
        while (getline(*reader.stream, line))
        {
            int numbers[2] = {charToInt(line[0]), charToInt(line[1])};
            for (int i = 2; i < line.length(); i++)
            {
                int num = charToInt(line[i]);
                if (i + 1 < line.length() && num > numbers[0])
                {
                    numbers[0] = num;
                    numbers[1] = 0;
                }
                else if (num > numbers[1])
                {
                    numbers[1] = num;
                }
            }
            cout << numbers[0] << numbers[1] << endl;
            sum += combine(numbers[0], numbers[1]);
        }
        cout << "Love " << sum << endl;
        return this;
    }

    Day3 *part1Test()
    {
        stringstream ss(
            "987654321111111\n811111111111119\n234234234234278\n818181911112111");
        string line;
        long long sum = 0;
        while (getline(ss, line))
        {
            int numbers[2] = {charToInt(line[0]), charToInt(line[1])};
            for (int i = 2; i < line.length(); i++)
            {
                int num = charToInt(line[i]);
                if (i + 1 < line.length() && num > numbers[0])
                {
                    numbers[0] = num;
                    numbers[1] = 0;
                }
                else if (num > numbers[1])
                {
                    numbers[1] = num;
                }
            }
            cout << numbers[0] << numbers[1] << endl;
            sum += combine(numbers[0], numbers[1]);
        }
        cout << "Love " << sum << endl;
        return this;
    }
};