#ifndef PRINTER_H
#define PRINTER_H

#include <vector>

class Printer {
    public:

    template<class T>
    static void print2DVector(std::vector<std::vector<T>> arr) {
        for (std::vector<T> x : arr) {
            cout << "[";
            for (auto y = x.begin(); y != x.end(); ++y) {
                if (std::next(y) == x.end()) {
                    cout << *y;
                } else {
                    cout << *y << ", ";
                }
            }
            cout << "]";
        }
    }
};
#endif
