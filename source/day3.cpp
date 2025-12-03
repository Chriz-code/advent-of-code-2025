#include "utils/filereader.cpp"
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

class Day3
{
private:
    stringstream TEST_VALUE = stringstream("987654321111111\n811111111111119\n234234234234278\n818181911112111");

    int charToInt(char c)
    {
        return c - '0';
    }

    long long sum(string numbers)
    {
        return stoll(numbers);
    }

    long long sum(vector<int> numbers)
    {
        string result;
        for (int number : numbers)
        {
            result += to_string(number);
        }
        cout << "line: " << result << endl;
        return sum(result);
    }

    int combine(int a, int b)
    {
        return stoi(to_string(a) + to_string(b));
    }

    int findIndexThatFits(vector<int> arr, int value, int startStep) {
        for (int i = startStep; i < arr.size(); i++) {
            if (value > arr[i]) {
                return i;
            }
        }

        return -1;
    }

    long long calcJoltage(int noBatteries, string line)
    {
        if (noBatteries >= line.length())
        {
            return sum(line);
        }

        vector<int> batteries({charToInt(line[0])});
        for (int ci = 1; ci < line.length(); ci++)
        {
            int charge = charToInt(line[ci]);

            int socketsLeft = noBatteries - batteries.size();
            int batteriesLeft = line.length() - ci;

            if (socketsLeft >= batteriesLeft)
            {
                batteries.push_back(charge);
                continue;
            }

            int index = findIndexThatFits(batteries, charge, max(0, noBatteries - batteriesLeft));

            if (index != -1)
            {
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
    Day3 *part1Test()
    {
        string line;
        long long sum = 0;
        while (getline(TEST_VALUE, line))
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
            sum += combine(numbers[0], numbers[1]);
        }
        cout << "Love " << sum << endl;
        return this;
    }

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
            sum += combine(numbers[0], numbers[1]);
        }
        cout << "Love " << sum << endl;
        return this;
    }

    Day3 *part2Test()
    {
        string line;
        long long sum = 0;
        while (getline(TEST_VALUE, line))
        {
            sum += calcJoltage(12, line);
        }
        cout << "Love " << sum << endl;
        return this;
    }

    Day3* part2() {
        FileReader reader("inputs/day3.txt");
        
        string line;
        long long sum = 0;

        while (getline(*reader.stream, line))
        {
            sum += calcJoltage(12, line);
        }
        
        cout << "Love " << sum << endl;
        return this;
    }
};