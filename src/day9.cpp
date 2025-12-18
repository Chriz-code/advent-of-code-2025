#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include "utils/matrix.cpp"
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <ostream>
#include <unordered_map>
#include <queue>

namespace Day9 {
    struct test {
        const char* INPUT =
            "7,1\n"
            "11,1\n"
            "11,7\n"
            "9,7\n"
            "9,5\n"
            "2,5\n"
            "2,3\n"
            "7,3";
    };

    struct basePoint2D {
        int col = -1, row = -1;
    };

    static long long calcArea(basePoint2D& topLeft, basePoint2D& bottomRight) {
        long long w = abs(bottomRight.row - topLeft.row) + 1;
        long long l = abs(bottomRight.col - topLeft.col) + 1;
        return w * l;
    }

    class Solution {
        struct Point2D : basePoint2D {
            int id;

            Point2D(int id = -1, int row = -1, int col = -1) : id(id), basePoint2D({ row, col }) {}

            bool operator < (const Point2D& other) const {
                return id < other.id;
            }

            void moveTowards(Point2D& p) {
                //row += std::clamp(p.row - row, -1, 1);
                //col += std::clamp(p.col - col, -1, 1);
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

        Day9::test t;

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
            std::stringstream stream(t.INPUT);
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
            std::stringstream stream(t.INPUT);
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

    class CompressionSolution {
        struct Point2D : basePoint2D {
            Point2D(const int col, const int row) : basePoint2D({ col, row }) {}
            friend std::ostream& operator<<(std::ostream& os, const Point2D& p) {
                os << "(" << p.col << "," << p.row << ")";
                return os;
            }
        };

        struct Square2D {
            Point2D p1;
            Point2D p2;
            long long area;

            bool operator<(const Square2D& other) const { return area < other.area; }
            Square2D(const Point2D tl, const Point2D br, const long long area) : p1(tl), p2(br), area(area) {}
            friend std::ostream& operator<<(std::ostream& os, const Square2D& s) {
                os << s.p1 << " : " << s.p2 << " : Area: " << s.area;
                return os;
            }
        };

        Day9::test t;

        std::vector<Point2D> readPoints(std::stringstream& stream) {
            using namespace std;
            vector<Point2D> points;
            points.reserve(1000);

            string line;
            while (getline(stream, line)) {
                std::vector<std::string> numbers = Utils::StringUtils::split(line, ',');
                int col = stoi(numbers[0]);
                int row = stoi(numbers[1]);
                points.emplace_back(col, row);
            }

            return points;
        }

        std::unordered_map<int, int> createAndFillMap(std::vector<Point2D>& points) {
            using namespace std;
            unordered_map<int, int> map;

            vector<int> values;
            for (const Point2D& p : points) {
                values.emplace_back(p.col);
                values.emplace_back(p.row);
            }
            sort(values.begin(), values.end());
            int count = 0;
            for (const int v : values) {
                if (!map.count(v)) {
                    map.insert({ v, count });
                    ++count;
                }
            }
            return map;
        }

        void fillFloor(std::vector<std::vector<int>>& floor, std::vector<Point2D>& points) {
            Point2D p1({ -1, -1 });
            char direction;
            long long length;
            points.emplace_back(points.at(0));
            for (const Point2D& p : points) {
                if (p1.col == -1) { p1 = p; continue; }

                if (p1.col != p.col) {
                    direction = (p1.col - p.col < 0 ? 'r' : 'l');
                    length = static_cast<long long>(abs(p1.col - p.col)) + 1ULL;
                }
                else {
                    direction = (p1.row - p.row < 0 ? 'd' : 'u');
                    length = static_cast<long long>(abs(p1.row - p.row)) + 1ULL;
                }
                for (int i = 0; i < length; i++) {
                    switch (direction) {
                    case 'u': floor[p1.row - i][p1.col] = 1; break;
                    case 'd': floor[p1.row + i][p1.col] = 1; break;
                    case 'l': floor[p1.row][p1.col - i] = 1; break;
                    case 'r': floor[p1.row][p1.col + i] = 1; break;
                    }
                }
                p1 = p;
            }
            points.pop_back();
        }

        void floodFill(std::vector<std::vector<int>>& arr, const int maxRow, const int maxCol) {
            std::queue<Point2D> q;
            q.emplace(maxCol * 0.5, maxRow * 0.4);
            while (!q.empty()) {
                Point2D p = q.front();
                q.pop();
                if (arr[p.row][p.col] == 0) {
                    arr[p.row][p.col] = 1;
                    q.emplace(p.col + 1, p.row);
                    q.emplace(p.col - 1, p.row);
                    q.emplace(p.col, p.row + 1);
                    q.emplace(p.col, p.row - 1);
                }
            }
        }

        std::vector<std::vector<int>> compressCoordinates(std::vector<Point2D>& points, std::unordered_map<int, int>& map) {
            using namespace std;

            vector<Point2D> points_compressed;
            points_compressed.reserve(map.size());
            int maxcol = 0, maxrow = 0;
            for (Point2D& p : points) {
                maxcol = max(maxcol, map.at(p.col));
                maxrow = max(maxrow, map.at(p.row));
                points_compressed.emplace_back(map.at(p.col), map.at(p.row));
            }

            vector<vector<int>> result;
            result.resize(maxrow + 1);
            for (vector<int>& v : result) {
                v.resize(maxcol + 1);
            }

            fillFloor(result, points_compressed);
            floodFill(result, maxrow, maxcol);
            points_compressed.clear();
            return result;
        }

        bool checkLinesForZero(const std::vector<std::vector<int>>& arr, const Point2D p1, const Point2D p2) {
            if (p1.col - p2.col <= 0) {
                for (int i = p1.col; i <= p2.col; i++) { if (arr[p1.row][i] == 0) { return true; } }
                for (int i = p1.col; i <= p2.col; i++) { if (arr[p2.row][i] == 0) { return true; } }
            }
            else {
                for (int i = p1.col; i >= p2.col; i--) { if (arr[p1.row][i] == 0) { return true; } }
                for (int i = p1.col; i >= p2.col; i--) { if (arr[p2.row][i] == 0) { return true; } }
            }

            if (p1.row - p2.row <= 0) {
                for (int i = p1.row; i <= p2.row; i++) { if (arr[i][p1.col] == 0) { return true; } }
                for (int i = p1.row; i <= p2.row; i++) { if (arr[i][p2.col] == 0) { return true; } }
            }
            else {
                for (int i = p1.row; i >= p2.row; i--) { if (arr[i][p1.col] == 0) { return true; } }
                for (int i = p1.row; i >= p2.row; i--) { if (arr[i][p2.col] == 0) { return true; } }
            }

            return false;
        }

    public:
        CompressionSolution* part2Test() {
            using namespace std;
            stringstream stream(t.INPUT);
            vector<Point2D> points = readPoints(stream);
            unordered_map<int, int> map = createAndFillMap(points);
            std::vector<std::vector<int>> arr = compressCoordinates(points, map);

            vector<Square2D> squares{}; squares.reserve(points.size() * 2);
            for (int i = 0; i < points.size(); i++) {
                for (int j = i + 1; j < points.size(); j++) {
                    Point2D p1 = points.at(i);
                    Point2D p2 = points.at(j);
                    squares.emplace_back(p1, p2, calcArea(p1, p2));
                }
            } sort(squares.rbegin(), squares.rend(), [](const Square2D& a, const Square2D& b) {return a < b;});
            points.clear();

            Square2D* largest_square;
            for (Square2D& sq : squares) {
                Point2D c1{ map.at(sq.p1.col), map.at(sq.p1.row) }, c2{ map.at(sq.p2.col), map.at(sq.p2.row) };
                if (checkLinesForZero(arr, c1, c2)) { continue; }
                largest_square = &sq; break;
            }

            cout << largest_square << endl;
            return this;
        }

        CompressionSolution* part2() {
            using namespace std;
            Utils::FileReader reader("inputs/day9.txt");
            stringstream stream = reader.toStringStream();
            vector<Point2D> points = readPoints(stream);
            return this;
        }
    };
}
