#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include "utils/matrix.cpp"
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

namespace Day9 {
    class CompressionSolution {
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

        struct Point2D {
            int col = -1;
            int row = -1;

            Point2D operator +(const Point2D& other) {
                return Point2D{ col + other.col, row + other.row };
            }

            Point2D operator *(const int& other) {
                return Point2D{ col * other, row * other };
            }

            friend std::ostream& operator<<(std::ostream& os, const Point2D& p) {
                os << "(" << p.col << "," << p.row << ")";
                return os;
            }
        };

        struct Square2D {
            Point2D p1;
            Point2D p2;
            long long area;

            static long long calcArea(Point2D topLeft, Point2D bottomRight) {
                long long w = abs(bottomRight.row - topLeft.row) + 1;
                long long l = abs(bottomRight.col - topLeft.col) + 1;
                return w * l;
            }

            Square2D(const Point2D p1, const Point2D p2): p1(p1), p2(p2), area(calcArea(p1, p2)) {}

            bool operator < (const Square2D& other) const { return area < other.area; }

            friend std::ostream& operator << (std::ostream& os, const Square2D& s) {
                os << s.p1 << " : " << s.p2 << " : Area: " << s.area;
                return os;
            }
        };

        struct Flood {
        private:
            const Point2D UP{ 0, -1 };
            const Point2D DOWN{ 0, 1 };
            const Point2D LEFT{ -1, 0 };
            const Point2D RIGHT{ 1, 0 };

            std::vector<Point2D>& points;
            int maxRow;
            int maxCol;

            void floor(std::vector<std::vector<int>>& matrix) {
                Point2D direction;
                long long length;

                points.push_back(points.at(0));

                Point2D prev;
                for (auto& current : points) {
                    if (prev.col == -1) { prev = current; continue; }

                    if (prev.col != current.col) {
                        direction = (prev.col - current.col < 0 ? RIGHT : LEFT);
                        length = abs(prev.col - current.col) + 1LL;
                    }
                    else {
                        direction = (prev.row - current.row < 0 ? DOWN : UP);
                        length = abs(prev.row - current.row) + 1LL;
                    }
                    for (int i = 0; i < length; i++) {
                        Point2D dist = direction * i;
                        matrix[prev.row + dist.row][prev.col + dist.col] = 1;
                    }
                    prev = current;
                }
                points.pop_back();
            }

            void flood(std::vector<std::vector<int>>& matrix) {
                std::queue<Point2D> que;
                que.emplace(maxCol * 0.5, maxRow * 0.5);

                while (!que.empty()) {
                    Point2D p = que.front();
                    que.pop();
                    if (matrix[p.row][p.col] == 0) {
                        matrix[p.row][p.col] = 1;
                        que.emplace(p.col + 1, p.row);
                        que.emplace(p.col - 1, p.row);
                        que.emplace(p.col, p.row + 1);
                        que.emplace(p.col, p.row - 1);
                    }
                }
            }

        public:
            Flood(
                std::vector<Point2D>& points,
                int maxRow,
                int maxCol
            ) : points(points), maxRow(maxRow), maxCol(maxCol) {}

            std::vector<std::vector<int>> fill(std::vector<std::vector<int>>& matrix) {
                floor(matrix);
                flood(matrix);
                return matrix;
            }
        };

        test t;

        std::vector<Point2D> getPoints(std::stringstream& stream) {
            using namespace std;
            string line;
            vector<Point2D> points;
            while (getline(stream, line)) {
                vector<string> numbers = Utils::StringUtils::split(line, ',');
                int col = stoi(numbers[0]);
                int row = stoi(numbers[1]);
                points.push_back({ row, col });
            }
            return points;
        }

        std::unordered_map<int, int> createMapFrom(std::vector<Point2D>& points) {
            using namespace std;
            unordered_map<int, int> map;

            vector<int> values;
            for (auto& p : points) {
                values.push_back(p.col);
                values.push_back(p.row);
            }

            sort(values.begin(), values.end());

            int count = 0;
            for (auto v : values) {
                if (map.find(v) == map.end()) {
                    map.insert({ v, count });
                    count++;
                }
            }
            return map;
        }

        std::vector<std::vector<int>> compressCoordinates(std::vector<Point2D>& points, std::unordered_map<int, int>& map) {
            using namespace std;

            vector<Point2D> points_compressed;
            points_compressed.reserve(map.size());

            int maxcol{ 0 };
            int maxrow{ 0 };

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

            Flood f = {
                points_compressed,
                maxrow,
                maxcol
            };
            return f.fill(result);
        }

        bool checkLinesForZero(const std::vector<std::vector<int>>& matrix, const Point2D p1, const Point2D p2) {
            if (p1.col - p2.col <= 0) {
                for (int i = p1.col; i <= p2.col; i++) { if (matrix[p1.row][i] == 0) { return true; } }
                for (int i = p1.col; i <= p2.col; i++) { if (matrix[p2.row][i] == 0) { return true; } }
            }
            else {
                for (int i = p1.col; i >= p2.col; i--) { if (matrix[p1.row][i] == 0) { return true; } }
                for (int i = p1.col; i >= p2.col; i--) { if (matrix[p2.row][i] == 0) { return true; } }
            }

            if (p1.row - p2.row <= 0) {
                for (int i = p1.row; i <= p2.row; i++) { if (matrix[i][p1.col] == 0) { return true; } }
                for (int i = p1.row; i <= p2.row; i++) { if (matrix[i][p2.col] == 0) { return true; } }
            }
            else {
                for (int i = p1.row; i >= p2.row; i--) { if (matrix[i][p1.col] == 0) { return true; } }
                for (int i = p1.row; i >= p2.row; i--) { if (matrix[i][p2.col] == 0) { return true; } }
            }

            return false;
        }

        Square2D findLargestSquare(
            std::vector<Point2D> points,
            std::unordered_map<int, int> map,
            std::vector<std::vector<int>> matrix
        ) {
            using namespace std;

            vector<Square2D> squares;
            for (int i = 0; i < points.size(); i++) {
                for (int j = i + 1; j < points.size(); j++) {
                    Point2D p1 = points.at(i);
                    Point2D p2 = points.at(j);
                    squares.push_back({
                        p1,
                        p2,
                    });
                }
            }
            
            sort(squares.rbegin(), squares.rend(), [](const Square2D& a, const Square2D& b) {
                return a < b;
            });
            
            points.clear();

            Square2D* largestSquare;
            for (Square2D& square : squares) {
                Point2D p1{
                    map.at(square.p1.col),
                    map.at(square.p1.row)
                };
                Point2D p2{
                    map.at(square.p2.col),
                    map.at(square.p2.row)
                };
                if (checkLinesForZero(matrix, p1, p2)) { continue; }
                largestSquare = &square; break;
            }
            return *largestSquare;
        }

    public:
        CompressionSolution* part2Test() {
            using namespace std;
            stringstream stream(t.INPUT);
            vector<Point2D> points = getPoints(stream);

            unordered_map<int, int> map = createMapFrom(points);

            std::vector<std::vector<int>> matrix = compressCoordinates(points, map);

            Square2D largestSquare = findLargestSquare(points, map, matrix);

            cout << largestSquare << endl;
            return this;
        }

        //1351617690
        CompressionSolution* part2() {
            using namespace std;
            Utils::FileReader reader("inputs/day9.txt");
            stringstream stream = reader.toStringStream();
            vector<Point2D> points = getPoints(stream);

            unordered_map<int, int> map = createMapFrom(points);

            std::vector<std::vector<int>> matrix = compressCoordinates(points, map);

            Square2D largestSquare = findLargestSquare(points, map, matrix);

            cout << largestSquare << endl;
            return this;
        }
    };
}