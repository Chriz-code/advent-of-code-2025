#include "utils/filereader.cpp"
#include "utils/position.cpp"
#include <vector>
#include <sstream>
#include <format>

namespace Day4 {
    typedef std::vector<std::vector<char>> charboard;

    class Solution {
    private:
        const char* TEST_INPUT =
            "..@@.@@@@.\n"
            "@@@.@.@.@@\n"
            "@@@@@.@.@@\n"
            "@.@@@@..@.\n"
            "@@.@@@@.@@\n"
            ".@@@@@@@.@\n"
            ".@.@.@.@@@\n"
            "@.@@@.@@@@\n"
            ".@@@@@@@@.\n"
            "@.@.@@@.@.";

        Utils::Position directions[8] = {
            {-1, -1},
            {-1, 0}, // Top
            {-1, 1},
            {0, 1}, // Right
            {1, 1},
            {1, 0}, // Down
            {1, -1},
            {0, -1} // Left
        };

        charboard createPuzzle(std::stringstream input) {
            charboard result;
            std::string line;
            while (getline(input, line)) {
                std::vector<char> row;
                for (char c : line) {
                    row.push_back(c);
                }
                result.push_back(row);
            }
            return result;
        }

        void printBoard(charboard& board) {
            for (std::vector<char> row : board) {
                for (char c : row) {
                    std::cout << c;
                }
                std::cout << "\n";
            }
        }

        char getNeighboor(charboard& board, Utils::Position position) {
            int row = position.row;
            int col = position.col;
            if (row < 0 || row >= board.size()) {
                return '-';
            }
            if (col < 0 || col >= board[row].size()) {
                return '-';
            }
            return board[row][col];
        }

        void markAccessablePapers(charboard& board, int& noAccessablePapers) {
            noAccessablePapers = 0;
            for (int row = 0; row < board.size(); row++) {
                std::vector<Utils::Position> markups;
                for (int col = 0; col < board[row].size(); col++) {
                    char character = board[row][col];
                    if (character != '@') {
                        continue;
                    }
                    int noPaperNeighbours = 0;
                    for (Utils::Position dir : directions) {
                        Utils::Position neighboorPos = {
                            row + dir.row,
                            col + dir.col,
                        };
                        char neighboor = getNeighboor(board, neighboorPos);
                        if (neighboor == '@') {
                            noPaperNeighbours++;
                        }
                    }
                    if (noPaperNeighbours < 4) {
                        noAccessablePapers++;
                        markups.push_back({ row, col });
                    }
                }

                for (Utils::Position pos : markups) {
                    board[pos.row][pos.col] = 'x';
                }
            }
        }

    public:
        Solution* part1Test() {
            charboard puzzle = createPuzzle(std::stringstream(TEST_INPUT));
            printBoard(puzzle);
            std::cout << std::string(puzzle[0].size(), '-') << std::endl;
            int result = 0;
            markAccessablePapers(puzzle, result);
            printBoard(puzzle);
           std:: cout << "I forked up " << result << std::endl;
            return this;
        }
        // 12131 -- too high
        // 1560
        Solution* part1() {
            Utils::FileReader reader("inputs/day4.txt");
            charboard puzzle = createPuzzle(reader.toStringStream());

            printBoard(puzzle);
            std::cout << std::string(puzzle[0].size(), '-') << std::endl;

            int result = 0;
            markAccessablePapers(puzzle, result);

            printBoard(puzzle);

            std::cout << "I forked up " << result << std::endl;
            return this;
        }

        Solution* part2Test() {
            charboard puzzle = createPuzzle(std::stringstream(TEST_INPUT));
            printBoard(puzzle);
            std::cout << std::string(puzzle[0].size(), '-') << std::endl;
            int result = 0;
            int collected = 0;
            while (true) {
                markAccessablePapers(puzzle, collected);
                result += collected;
                std::cout << "Collected: " << collected << std::endl;
                if (collected == 0) {
                    break;
                }
            }
            printBoard(puzzle);
            std::cout << "I forked up " << result << std::endl;
            return this;
        }

        // 9609
        Solution* part2() {
            Utils::FileReader reader("inputs/day4.txt");
            charboard puzzle = createPuzzle(reader.toStringStream());

            printBoard(puzzle);
            std::cout << std::string(puzzle[0].size(), '-') << std::endl;

            int result = 0;
            int collected = 0;
            while (true) {
                markAccessablePapers(puzzle, collected);
                result += collected;
                std::cout << "Collected: " << collected << std::endl;
                if (collected == 0) {
                    break;
                }
            }

            printBoard(puzzle);
            std::cout << "I forked up " << result << std::endl;

            return this;
        }
    };
}
