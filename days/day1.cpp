#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Day1
{
private:
    const string inputFile = "C:\\GitHub\\advent-of-code-2025\\days\\day1_input.txt";
    ifstream inputStream;

public:
    Day1()
    {
        inputStream = ifstream(inputFile);
    }

    int part1()
    {
        if (!inputStream.is_open())
        {
            cout << "Unable to open file";
            return 0;
        }
        
        string line;
        while (getline(inputStream, line))
        {
            cout << line << '\n';
        }
        inputStream.close();

        return 0;
    }

    ~Day1()
    {
        inputStream.close();
    }
};