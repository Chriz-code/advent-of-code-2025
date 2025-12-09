#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class FileReader
{

private:
    bool isValid;
public:
    std::ifstream* stream;

    FileReader(std::string filePath) {
        stream = new std::ifstream(filePath);
        if (!(*stream).is_open())
        {
            cout << "Unable to open file" << endl;
            isValid = false;
        }
        else {
            isValid = true;
        }
    }

    std::string toString()
    {
        std::string line;
        std::string result;
        while (getline(*stream, line, '\n'))
        {
            result += line;
        }
        return result;
    }

    std::stringstream toStringStream() {
        std::stringstream buffer;
        buffer << (*stream).rdbuf();
        return buffer;
    }

    ~FileReader() {
        (*stream).close();
    }
};
#endif