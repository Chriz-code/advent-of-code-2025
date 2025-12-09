#ifndef GRIDIFY_H
#define GRIDIFY_H

#include <vector>
#include <sstream>
#include <functional>
#include <string>

namespace Utils {
    class Gridify {
    public:
        template <class T>
        static std::vector<std::vector<T>> createGridFromString(
            std::stringstream& ss,
            char delim,
            std::function<T(char&)> converter) {
            std::vector<std::vector<T>> result;
            std::string line;
            while (std::getline(ss, line, delim)) {
                std::vector<T> row;
                for (char c : line) {
                    row.push_back(converter(c));
                }
                result.push_back(row);
            }
            return result;
        }
    };
}

#endif