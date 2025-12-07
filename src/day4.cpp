#include "utils/filereader.cpp"
#include "utils/position.cpp"
#include <vector>
#include <sstream>
#include <format>

typedef vector<vector<char>> charboard;

class Day4
{
private:
    const char *TEST_INPUT =
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

    Position directions[8] = {
        {-1, -1},
        {-1, 0}, // Top
        {-1, 1},
        {0, 1}, // Right
        {1, 1},
        {1, 0}, // Down
        {1, -1},
        {0, -1} // Left
    };

    charboard createPuzzle(stringstream input)
    {
        charboard result;
        string line;
        while (getline(input, line))
        {
            vector<char> row;
            for (char c : line)
            {
                row.push_back(c);
            }
            result.push_back(row);
        }
        return result;
    }

    void printBoard(charboard& board)
    {
        for (vector<char> row : board)
        {
            for (char c : row)
            {
                cout << c;
            }
            cout << "\n";
        }
    }

    char getNeighboor(charboard& board, Position position)
    {
        int row = position.row;
        int col = position.col;
        if (row < 0 || row >= board.size())
        {
            return '-';
        }
        if (col < 0 || col >= board[row].size())
        {
            return '-';
        }
        return board[row][col];
    }

    void markAccessablePapers(charboard& board, int& noAccessablePapers) {
        noAccessablePapers = 0;
        for (int row = 0; row < board.size(); row++) {
            vector<Position> markups;
            for (int col = 0; col < board[row].size(); col++) {
                char character = board[row][col];
                if (character != '@')
                {
                    continue;
                }
                int noPaperNeighbours = 0;
                for (Position dir : directions)
                {
                    Position neighboorPos = {
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
                    markups.push_back({row, col});
                }
            }
            
            for (Position pos : markups) {
                board[pos.row][pos.col] = 'x';
            }
        }
    }

public:
    Day4 *part1Test()
    {
        charboard puzzle = createPuzzle(stringstream(TEST_INPUT));
        printBoard(puzzle);
        cout << string(puzzle[0].size(), '-') << endl;
        int result = 0;
        markAccessablePapers(puzzle, result);
        printBoard(puzzle);
        cout << "I forked up " << result << endl;
        return this;
    }
    // 12131 -- too high
    // 1560
    Day4 *part1()
    {
        FileReader reader("inputs/day4.txt");
        charboard puzzle = createPuzzle(reader.toStringStream());
        
        printBoard(puzzle);
        cout << string(puzzle[0].size(), '-') << endl;
        
        int result = 0;
        markAccessablePapers(puzzle, result);
        
        printBoard(puzzle);
        
        cout << "I forked up " << result << endl;
        return this;
    }

    Day4 *part2Test() {
        charboard puzzle = createPuzzle(stringstream(TEST_INPUT));
        printBoard(puzzle);
        cout << string(puzzle[0].size(), '-') << endl;
        int result = 0;
        int collected = 0;
        while (true) {
            markAccessablePapers(puzzle, collected);
            result += collected;
            cout << "Collected: " << collected << endl;
            if (collected == 0) {
                break;
            }
        }
        printBoard(puzzle);
        cout << "I forked up " << result << endl;
        return this;
    }

    // 9609
    Day4 *part2() {
        FileReader reader("inputs/day4.txt");
        charboard puzzle = createPuzzle(reader.toStringStream());
        
        printBoard(puzzle);
        cout << string(puzzle[0].size(), '-') << endl;
        
        int result = 0;
        int collected = 0;
        while (true) {
            markAccessablePapers(puzzle, collected);
            result += collected;
            cout << "Collected: " << collected << endl;
            if (collected == 0) {
                break;
            }
        }
        
        printBoard(puzzle);
        cout << "I forked up " << result << endl;
        
        return this;
    }
};