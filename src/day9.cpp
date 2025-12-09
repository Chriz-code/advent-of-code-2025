#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include "utils/matrix.cpp"
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

namespace Day9 {
    typedef long long llong;

    struct Point2D {
        int id;
        llong x, y;

        bool operator < (const Point2D& other) const {
            return id < other.id;
        }

        static bool sortBySize(const Point2D& p1, const Point2D& p2) {
            if (p1.x > p2.x)
                return true;
            return p1.y > p2.y;
        }
    };

    typedef std::pair<Point2D, Point2D> Edge2D;

    class Solution {
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
            int id = 0;
            while (getline(stream, line)) {
                std::vector<std::string> numbers = Utils::StringUtils::split(line, ',');
                llong x = stoll(numbers[0]);
                llong y = stoll(numbers[1]);
                points.push_back({ id, x, y });
                id++;
            }
            return points;
        }

        std::vector<Edge2D> getUniquePointSets(std::vector<Point2D>& points) {
            auto compare = [](Edge2D lhs, Edge2D rhs) {
                if (lhs.first.id > lhs.second.id)
                    lhs = { lhs.second, lhs.first };
                if (rhs.first.id > rhs.second.id)
                    rhs = { rhs.second, rhs.first };
                return lhs < rhs;
            };

            std::set<Edge2D, decltype(compare)> uniques(compare);
            for (auto& p1 : points) {
                for (auto& p2 : points) {
                    if (p1.id == p2.id) {
                        continue;
                    }
                    Edge2D edge({ p1, p2 });
                    uniques.emplace(edge);
                }
            }
            return std::vector<Edge2D>(uniques.begin(), uniques.end());
        }

        static bool isPoint(std::vector<Point2D>& points, int row, int col) {
            Point2D p2({ row, col });
            for (auto& p1 : points) {
                if (p1.id == p2.id) {
                    return true;
                }
            }
            return false;
        }

        static bool isInsideAxisAligned(Point2D p, Point2D corner1, Point2D corner2) {
            int minX = std::min(corner1.x, corner2.x) + 1;
            int maxX = std::max(corner1.x, corner2.x) + 1;
            int minY = std::min(corner1.y, corner2.y) + 1;
            int maxY = std::max(corner1.y, corner2.y) + 1;
            return (p.x >= minX && p.x <= maxX) && (p.y >= minY && p.y <= maxY);
        }

    public:
        Solution* part1Test() {
            std::stringstream stream(TEST_INPUT);
            std::vector<Point2D> points = getPoints(stream);
            std::sort(points.begin(), points.end(), Point2D::sortBySize);
            int size = std::max(points[0].x, points[0].y);
            Utils::Matrix2D<char> matrix = Utils::Matrix2D<char>(size, size, '.');

            std::vector<Edge2D> uniquePointSets = getUniquePointSets(points);
            matrix.navigateLTR([&uniquePointSets, &matrix](int row, int col, char c) {
                if (c == 'O') {
                    return;
                }
                for (auto& edge : uniquePointSets) {
                    if (isInsideAxisAligned({ 0, row, col }, edge.first, edge.second)) {
                        matrix[row][col] = 'O';
                        return;
                    }
                }
            });

            matrix.draw(' ');
            return this;
        }
    };
}
