#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include <sstream>
#include <vector>
#include <cmath>

typedef long long llong;

struct Point2D {
    llong x, y;
    long double dist;
};

typedef std::vector<Point2D> Coordinates;

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

    Coordinates getCoords(std::stringstream& stream) {
        Coordinates coords;

        std::string line;
        while (getline(stream, line)) {
            std::vector<std::string> digits = StringUtils::split(line, ',');
            llong x = stoll(digits[0]);
            llong y = stoll(digits[1]);
            coords.push_back({ x, y, sqrt(pow(x, 2) + pow(y, 2))});
        }

        return coords;
    }

    Coordinates findLargestArea(Coordinates& coords) {
        //Sort top left
        std::sort(coords.begin(), coords.end(), [](const auto& coord1, const auto& coord2) {
            return coord1.dist < coord2.dist;
        });
        Point2D topLeft = *coords.begin();
        Point2D bottomRight = coords.back();
        return Coordinates({ topLeft, bottomRight });
    }

    long long calcArea(Point2D& topLeft, Point2D& bottomRight) {
        llong w = abs(bottomRight.x - topLeft.x) + 1;
        llong l = abs(bottomRight.y - topLeft.y) + 1;
        return w * l;
    }

public:
    Day9* part1Test() {
        std::stringstream stream(TEST_INPUT);

        Coordinates coords = getCoords(stream);
        Coordinates areaCoords = findLargestArea(coords);

        Point2D topLeft = areaCoords[0];
        Point2D bottomRight = areaCoords[1];
        llong area = calcArea(topLeft, bottomRight);

        cout << "The 2 points are: "
            << "(" << topLeft.x << "," << topLeft.y << ")"
            << "(" << bottomRight.x << "," << bottomRight.y << ")" << endl;
        cout << "The largest area is: " << area << endl;

        return this;
    }

    // 3469520181 - too low?
    // 166048784
    // 4737634748 - too low??
    // 4737634748
    Day9* part1() {
        FileReader reader("inputs/day9.txt");
        std::stringstream stream = reader.toStringStream();

        Coordinates coords = getCoords(stream);
        Coordinates areaCoords = findLargestArea(coords);

        Point2D topLeft = areaCoords[0];
        Point2D bottomRight = areaCoords[1];
        llong area = calcArea(topLeft, bottomRight);

        cout << "The 2 points are: "
            << "(" << topLeft.x << "," << topLeft.y << ")"
            << "(" << bottomRight.x << "," << bottomRight.y << ")" << endl;
        cout << "The largest area is: " << area << endl;

        return this;
    }
};
