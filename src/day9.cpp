#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include <sstream>
#include <vector>
#include <cmath>
#include "utils/grid.cpp"

typedef long long llong;


class Day9 {
private:
    const char* TEST_INPUT =
        "7,1\n"
        "11,1\n"
        "11,7\n"
        "9,7\n"
        "9,5\n"
        "2,5\n"
        "2,3\n"
        "7,3";

    long long calcArea(Point2D& topLeft, Point2D& bottomRight) {
        llong w = abs(bottomRight.first - topLeft.first) + 1;
        llong l = abs(bottomRight.second - topLeft.second) + 1;
        return w * l;
    }

public:
    Day9* part1Test() {
        std::stringstream stream(TEST_INPUT);

        return this;
    }
};
