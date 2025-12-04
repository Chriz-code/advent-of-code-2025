#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef GRANDPARENT_H
#define GRANDPARENT_H

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
        while (getline(*stream, line, '\n'))
        {
            result += line;
        }
        return result;
    }

    stringstream toStringStream() {
        stringstream buffer;
        buffer << (*stream).rdbuf();
        return buffer;
    }

    ~FileReader() {
        (*stream).close();
    }
};
#endif