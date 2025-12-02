#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Day2 {
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
};