#include "utils/filereader.cpp"
#include "utils/gridify.cpp"
#include "utils/printer.cpp"
#include <vector>
#include <string>
#include <functional>

using namespace std;

typedef vector<vector<string>> grid;

class Day7 {
private:
    const char* TEST_INPUT =
        ".......S.......\n"
        "...............\n"
        ".......^.......\n"
        "...............\n"
        "......^.^......\n"
        "...............\n"
        ".....^.^.^.....\n"
        "...............\n"
        "....^.^...^....\n"
        "...............\n"
        "...^.^...^.^...\n"
        "...............\n"
        "..^...^.....^..\n"
        "...............\n"
        ".^.^.^.^.^...^.\n"
        "...............";

    void navGrid(grid& g, function<void(int, int)> onStep) {
        for (int row = 0; row < g.size(); row++) {
            for (int col = 0; col < g[row].size(); col++) {
                onStep(row, col);
            }
        }
    }

    static void countSplits(grid& diagram, long long& noSplit, int rowIdx, int colIdx) {
        string step = diagram[rowIdx][colIdx];
        if (step == "^") {
            bool hasSplit = false;

            int prevRow = rowIdx - 1;
            while (prevRow >= 0) {
                string prev = diagram[prevRow][colIdx];
                if (prev == "^") {
                    break;
                }
                if (prev == "S") {
                    hasSplit = true;
                    break;
                }

                vector<string> row = diagram[prevRow];
                if (colIdx - 1 >= 0) {
                    string leftCol = row[colIdx - 1];
                    if (leftCol == "^") {
                        hasSplit = true;
                        break;
                    }
                }

                if (colIdx + 1 < row.size()) {
                    string rightCol = row[colIdx + 1];
                    if (rightCol == "^") {
                        hasSplit = true;
                        break;
                    }
                }

                prevRow--;
            }

            if (hasSplit) {
                noSplit++;
            }
        }
    }

public:
    Day7* part1Test() {
        stringstream ss(TEST_INPUT);
        grid diagram = Gridify::createGridFromString<string>(
            ss,
            '\n',
            [](char& v) { return string({ v }); }
        );
        Printer::print2DVector(diagram, false);

        long long noSplit = 0;
        navGrid(diagram, [&diagram, &noSplit](int rowIdx, int colIdx) {
            Day7::countSplits(diagram, noSplit, rowIdx, colIdx);    
        });
        cout << "My yellow stream has splits " << noSplit << endl;

        return this;
    }
    // 1696 -- too high
    Day7* part1() {
        FileReader reader("inputs/day7.txt");
        stringstream stream = reader.toStringStream();
        grid diagram = Gridify::createGridFromString<string>(
            stream,
            '\n',
            [](char& v) { return string({ v }); }
        );
        Printer::print2DVector(diagram, false);

        long long noSplit = 0;
        navGrid(diagram, [&diagram, &noSplit](int rowIdx, int colIdx) {
            Day7::countSplits(diagram, noSplit, rowIdx, colIdx);    
        });
        cout << "My yellow stream has splits " << noSplit << endl;

        return this;
    }
};