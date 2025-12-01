#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Day1
{
private:
    const string inputFile = "C:\\GitHub\\advent-of-code-2025\\days\\day1_input.txt";
    ifstream inputStream;

    void solver(string line, int &dial, int &result)
    {
        int turn = stoi(line.substr(1));
        if (line[0] == 'L')
        {
            dial -= turn;
        }
        else
        {
            dial += turn;
        }

        while(dial >= 100) {
            dial -= 100;
        }

        while (dial < 0) {
            dial = 100 + dial;
        }

        cout << "The dial is rotated " << line << " to point at ";
        if (dial == 0)
        {
            result += 1;
            cout << "*" << dial << "*";
        }
        else
        {
            cout << dial;
        }
        cout << "\n";
    }

public:
    int part1Test()
    {
        stringstream ss("L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82");
        string line;
        int result = 0;
        int dial = 50;
        while (getline(ss, line, '\n'))
        {
            solver(line, dial, result);
        }
        return result;
    }

    // The right answer is 1139
    int part1()
    {
        ifstream inputStream(inputFile);

        if (!inputStream.is_open())
        {
            cout << "Unable to open file";
            return 0;
        }

        int result = 0;
        int dial = 50;

        string line;
        while (getline(inputStream, line))
        {
            solver(line, dial, result);
        }
        return result;
    }
};