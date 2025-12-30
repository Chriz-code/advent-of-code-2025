#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include<string>
#include<vector>
#include<sstream>

namespace Utils {
    class StringUtils {
    public:
        static std::vector<std::string> split(std::string value, char delimiter) {
            std::vector<std::string> result;
            if (value.find(delimiter) >= value.size()) {
                result.push_back(value);
                return result;
            }
            std::stringstream stream(value);
            std::string line;
            while (getline(stream, line, delimiter)) {
                result.push_back(line);
            }
            return result;
        }
    };
}

#endif