#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Range
{
    long start;
    long end;
};

class Day2
{
private:
    const string inputFile = "inputs/day2.txt";
    ifstream *stream()
    {
        ifstream *inputStream = new ifstream(inputFile);

        if (!(*inputStream).is_open())
        {
            cout << "Unable to open file" << endl;
            return nullptr;
        }
        return inputStream;
    }

    string readToString(ifstream *stream)
    {
        string line;
        string result;
        while (getline(*stream, line))
        {
            result += line;
        }
        return result;
    }

    bool isPalindrome(string value)
    {
        return value.length() % 2 == 0 && value.substr(0, value.length() / 2) == value.substr(value.length() / 2);
    }

    Range parseRange(string line)
    {
        int splitIdx = line.find('-');
        string start = line.substr(0, splitIdx);
        string end = line.substr(splitIdx + 1);
        long startNum = stol(start);
        long endNum = stol(end);
        cout << startNum << ":" << splitIdx << ":" << endNum << endl;
        return { startNum, endNum };
    }

public:
    Day2 *part1()
    {
        stringstream input(readToString(stream()));
        string line;
        long sumOfPalindromes = 0L;
        while (getline(input, line, ','))
        {
            Range range = parseRange(line);

            for (long value = range.start; value <= range.end; value++)
            {
                if (isPalindrome(to_string(value)))
                {
                    sumOfPalindromes += value;
                }
            }
        }
        cout << "Here lies " << to_string(sumOfPalindromes) << endl;
        return this;
    }
};