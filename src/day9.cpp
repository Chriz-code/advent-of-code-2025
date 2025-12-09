#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include "utils/matrix.cpp"
#include <sstream>
#include <vector>
#include <cmath>

typedef long long llong;
typedef std::pair<int, int> Point2D;

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

    std::vector<Point2D> getPoints(std::stringstream& stream) {
        std::string line;
        std::vector<Point2D> points;
        while (getline(stream, line)) {
            std::vector<std::string> numbers = StringUtils::split(line, ',');
            llong x = stoll(numbers[0]);
            llong y = stoll(numbers[1]);
            points.push_back({ x, y });
        }
        return points;
    }

    void sortPoints(std::vector<Point2D>& points) {
        std::sort(points.begin(), points.end(), [](const Point2D& a, const Point2D& b) {
            if (a.first > b.first)
                return true;
            return a.second > b.second;
        });
    }

    static bool isPoint(std::vector<Point2D>& points, int row, int col) {
        Point2D p2({row, col});
        for (auto& p1 : points) {
            if (p1 == p2) {
                return true;
            }
        }
        return false;
    }

public:
    Day9* part1Test() {
        std::stringstream stream(TEST_INPUT);
        std::vector<Point2D> points = getPoints(stream);
        sortPoints(points);
        int size = std::max(points[0].first, points[0].second);
        Matrix2D<char> matrix = Matrix2D<char>(size, size, '.');

        matrix.navigateLTR([&points, &matrix](const int& row, const int& col, const char& c){
            if (Day9::isPoint(points, row, col)) {
                matrix[row][col] = '#';
            }
        });

        matrix.draw(' ');
        return this;
    }
};
