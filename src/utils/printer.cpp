#ifndef PRINTER_H
#define PRINTER_H

#include <vector>

namespace Utils {
    class Printer {
    public:

        template<class T>
        static void print2DVector(std::vector<std::vector<T>>& arr, bool commaSeperator = true) {
            for (std::vector<T> x : arr) {
                std::cout << "[";
                for (auto y = x.begin(); y != x.end(); ++y) {
                    if (std::next(y) == x.end()) {
                        std::cout << *y;
                    }
                    else {
                        std::cout << *y;
                        if (commaSeperator) {
                            std::cout << ", ";
                        }
                    }
                }
                std::cout << "]" << std::endl;
            }
        }
    };
}
#endif
