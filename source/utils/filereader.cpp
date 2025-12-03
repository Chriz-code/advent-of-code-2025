#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileReader
{

private:
    bool isValid;
public:
    ifstream* stream;

    FileReader(string filePath) {
        stream = new ifstream(filePath);
        if (!(*stream).is_open())
        {
            cout << "Unable to open file" << endl;
            isValid = false;
        }
        else {
            isValid = true;
        }
    }

    string toString()
    {
        string line;
        string result;
        while (getline(*stream, line))
        {
            result += line;
        }
        return result;
    }

    ~FileReader() {
        (*stream).close();
    }
};