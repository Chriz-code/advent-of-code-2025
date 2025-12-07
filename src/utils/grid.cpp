#ifndef GRID_H
#define GRID_H

#include <vector>
#include <sstream>

typedef std::pair<int, int> Point;

template <class T>
class Grid {
private:
    std::vector<std::vector<T>> grid;

    Grid(std::vector<std::vector<T>> grid) {
        this->grid = grid;
    }
public:
    static Grid<T> toGrid(
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

    vector<T>& operator [] (int row) {
        return grid[row];
    }

    T& operator [] (Point p) {
        return grid[p.first][p.second];
    }

    void navigate(function<void(Point)> onStep) {
        for (int row = 0; row < grid.size(); row++) {
            for (int col = 0; col < grid[row].size(); col++) {
                onStep({ row, col });
            }
        }
    }

    void print(bool commaSeperator = true) {
        for (auto row : grid) {
            cout << "[";
            for (auto col = row.begin(); col != row.end(); ++col) {
                if (std::next(col) == row.end()) {
                    cout << *col;
                }
                else {
                    cout << *col;
                    if (commaSeperator) {
                        cout << ", ";
                    }
                }
            }
            cout << "]" << endl;
        }
    }

};
#endif