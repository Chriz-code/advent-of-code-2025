#ifndef GRID_H
#define GRID_H

#include <vector>
#include <sstream>

namespace Utils {
    typedef std::pair<int, int> Point2D;

    template <typename T>
    class Grid {
    private:
        std::vector<std::vector<T>> grid;

        Grid(std::vector<std::vector<T>> grid) {
            this->grid = grid;
        }

    public:
        static Grid toGrid(
            std::stringstream& ss,
            char delim,
            std::function<T(char&)> converter
        ) {
            std::vector<std::vector<T>> result;
            std::string line;
            while (std::getline(ss, line, delim)) {
                std::vector<T> row;
                for (char c : line) {
                    row.push_back(converter(c));
                }
                result.push_back(row);
            }
            return Grid(result);
        }

        std::vector<T>& operator [] (int row) {
            return grid[row];
        }

        T& operator [] (Point2D p) {
            return grid[p.first][p.second];
        }

        void navigateLTR(std::function<void(Point2D)> onStep) {
            for (int row = 0; row < grid.size(); row++) {
                for (int col = 0; col < grid[row].size(); col++) {
                    onStep({ row, col });
                }
            }
        }

        void print(bool commaSeperator = true) {
            for (auto row : grid) {
                std::cout << "[";
                for (auto col = row.begin(); col != row.end(); ++col) {
                    if (std::next(col) == row.end()) {
                        std::cout << *col;
                    }
                    else {
                        std::cout << *col;
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
