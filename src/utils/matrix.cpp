#ifndef MATRIX_H
#define MATRIX_H

#include <functional>

namespace Utils {
    template<class T>
    class Matrix2D {
    private:
        T** data;
        int rows;
        int columns;

    public:
        Matrix2D(int rows, int columns, T* defaultValue = nullptr) {
            data = new T * [rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = new T[columns];
                for (int j = 0; j < columns; ++j)
                    data[i][j] = defaultValue;
            }
            this->rows = rows;
            this->columns = columns;
        }

        Matrix2D(int rows, int columns, T defaultValue) {
            data = new T * [rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = new T[columns];
                for (int j = 0; j < columns; ++j)
                    data[i][j] = defaultValue;
            }
            this->rows = rows;
            this->columns = columns;
        }

        auto& operator [] (int row) {
            return data[row];
        }

        auto& operator [] (std::pair<int, int> p) {
            return data[p.first][p.second];
        }

        void navigateLTR(std::function<void(int, int, T)> onStep) {
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < columns; col++) {
                    onStep(row, col, data[row][col]);
                }
            }
        }

        void draw(char separator = ',') {
            for (int row = 0; row < rows; row++) {
                std::cout << "[";
                for (int col = 0; col < columns; col++) {
                    std::cout << data[row][col];
                    if (!(col == columns - 1)) {
                        std::cout << separator;
                    }
                }
                std::cout << "]" << std::endl;
            }
        }

        ~Matrix2D() {
            for (int i = 0; i < rows; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
    };
}
#endif
