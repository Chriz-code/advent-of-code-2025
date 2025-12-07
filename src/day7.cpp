#include "utils/gridify.cpp"
#include "utils/printer.cpp"
#include <vector>
#include <string>

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

public:
    Day7* part1Test() {
        stringstream ss(TEST_INPUT);
        grid diagram = Gridify::createGridFromString<string>(
            ss,
            '\n',
            [](char& v) { return string({ v }); }
        );
        Printer::print2DVector(diagram, false);

        return this;
    }
};