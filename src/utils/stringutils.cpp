#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include<string>
#include<vector>
#include<sstream>
class StringUtils {
    public:
    static std::vector<std::string> split(std::string value, char delimiter) {
        std::vector<std::string> result;
        std::stringstream stream(value);
        std::string line;
        while (getline(stream, line, delimiter)) {
            result.push_back(line);
        }
        return result;
    }
};
#endif