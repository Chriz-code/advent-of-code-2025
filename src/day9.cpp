#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include "utils/matrix.cpp"
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

namespace Day9 {
    struct Point2D {
        int id;
        int row, col;

        bool operator < (const Point2D& other) const {
            return id < other.id;
        }

        void moveTowards(Point2D& p) {
            row += std::clamp(p.row - row, -1, 1);
            col += std::clamp(p.col - col, -1, 1);
        }
    };

    struct PointPositionIsGreater {
        bool operator()(const Point2D& p1, const Point2D& p2) const {
            if (std::max(p1.row, p1.col) > std::max(p2.row, p2.col))
                return true;
            return false;
        }
    };

    typedef std::pair<Point2D, Point2D> Edge2D;

    class Solution {
    private:
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
            int minR = std::min(corner1.row, corner2.row);
            int maxR = std::max(corner1.row, corner2.row);
            int minC = std::min(corner1.col, corner2.col);
            int maxC = std::max(corner1.col, corner2.col);
            return (p.row >= minR && p.row <= maxR) && (p.col >= minC && p.col <= maxC);
        }

        static long long calcArea(Point2D& topLeft, Point2D& bottomRight) {
            long long w = abs(bottomRight.row - topLeft.row) + 1;
            long long l = abs(bottomRight.col - topLeft.col) + 1;
            return w * l;
        }

        static std::vector<Edge2D> getUniquePointSets(std::vector<Point2D>& points) {
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
                int col = stoi(numbers[0]);
                int row = stoi(numbers[1]);
                points.push_back({ id, row, col });
                id++;
            }
            return points;
        }

        void drawBordersOn(Utils::Matrix2D<char>& matrix, std::vector<Point2D>& points) {
            for (int i = 0; i < points.size(); ++i) {
                Point2D next = points[(i + 1) % points.size()];
                Point2D step = points[i];
                while (step.row != next.row || step.col != next.col) {
                    matrix[step.row][step.col] = 'X';
                    step.moveTowards(next);
                }
            }
        }

        void fillBorders(Utils::Matrix2D<char>& matrix) {
            std::vector<Point2D> toFill;
            matrix.navigateLTR([&matrix, &toFill](const int& row, const int& col, const char& c) {
                if (c == 'X') {
                    return;
                }

                int ray = 0;
                char prev = matrix[row][0];
                for (int x = 0; x < col; ++x) {
                    char cur = matrix[row][x];
                    if (prev != cur && cur == 'X') {
                        ray++;
                    }
                    prev = cur;
                }
                if (ray % 2 != 0) {
                    ray = 0;
                    prev = matrix[0][col];
                    for (int y = 0; y < row; ++y) {
                        char cur = matrix[y][col];
                        if (prev != cur && cur == 'X') {
                            ray++;
                        }
                        prev = cur;
                    }
                    if (ray % 2 != 0) {
                        toFill.push_back({ -1, row, col });
                    }
                }
            });
            for (auto& p : toFill)
                matrix[p.row][p.col] = 'X';
        }

    public:
        Solution* part1Test() {
            std::stringstream stream(TEST_INPUT);
            std::vector<Point2D> points = getPoints(stream);
            std::vector<Edge2D> uniquePointSets = getUniquePointSets(points);

            long long area = 0;
            for (auto& p : uniquePointSets) {
                area = std::max(
                    area,
                    calcArea(p.first, p.second)
                );
            }
            std::cout << area << std::endl;

            //Utils::Matrix2D<char> matrix = Utils::Matrix2D<char>(9, 14, '.');
            //matrix.navigateLTR([&uniquePointSets, &matrix](int row, int col, char c) {
            //    if (c == 'O') {
            //        return;
            //    }
            //    for (auto& edge : uniquePointSets) {
            //        if (isInsideAxisAligned({ -1, row, col }, edge.first, edge.second)) {
            //            matrix[row][col] = 'O';
            //            return;
            //        }
            //    }
            //});
//
            //matrix.draw(' ');
            return this;
        }

        Solution* part1() {
            Utils::FileReader reader("inputs/day9.txt");
            std::stringstream stream = reader.toStringStream();
            std::vector<Point2D> points = getPoints(stream);

            std::vector<Edge2D> uniquePointSets = getUniquePointSets(points);

            long long area = 0;
            for (auto& p : uniquePointSets) {
                area = std::max(
                    area,
                    calcArea(p.first, p.second)
                );
            }
            std::cout << area << std::endl;
            return this;
        }

        Solution* part2Test() {
            std::stringstream stream(TEST_INPUT);
            std::vector<Point2D> points = getPoints(stream);

            Utils::Matrix2D<char> matrix = Utils::Matrix2D<char>(9, 14, '.');
            drawBordersOn(matrix, points);
            fillBorders(matrix);

            //std::vector<Edge2D> uniquePointSets = getUniquePointSets(points);


            matrix.draw(' ');
            return this;
        }

        Solution* part2() {
            Utils::FileReader reader("inputs/day9.txt");
            std::stringstream stream = reader.toStringStream();
            std::vector<Point2D> points = getPoints(stream);

            //This is a bad solution I think..

            Utils::Matrix2D<char> matrix = Utils::Matrix2D<char>(100000, 100000, '.');
            drawBordersOn(matrix, points);
            //fillBorders(matrix);

            //std::vector<Edge2D> uniquePointSets = getUniquePointSets(points);


            matrix.draw(' ');
            return this;
        }
    };
}
