#include "utils/filereader.cpp"
#include "utils/gridify.cpp"
#include "utils/printer.cpp"
#include "utils/grid.cpp"
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <numeric>

namespace Day7 {
    using namespace std;

    class Solution {
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

        static void countSplits(Utils::Grid<string>& diagram, long long& noSplit, Utils::Point2D point) {
            string step = diagram[point];
            if (step == "^") {
                bool hasSplit = false;

                int prevRow = point.first - 1;
                while (prevRow >= 0) {
                    string prev = diagram[{prevRow, point.second}];
                    if (prev == "^") {
                        break;
                    }
                    if (prev == "S") {
                        hasSplit = true;
                        break;
                    }

                    vector<string> row = diagram[prevRow];
                    if (point.second - 1 >= 0) {
                        string leftCol = row[point.second - 1];
                        if (leftCol == "^") {
                            hasSplit = true;
                            break;
                        }
                    }

                    if (point.second + 1 < row.size()) {
                        string rightCol = row[point.second + 1];
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

        static void countTimelines(Utils::Grid<string>& diagram, map<Utils::Point2D, long long>& splits, Utils::Point2D point) {
            string value = diagram[point];
            if (value == "^") {
                splits[point] = 0;

                int prevRow = point.first - 1;
                while (prevRow >= 0) {
                    string prev = diagram[{prevRow, point.second}];
                    if (prev == "^") {
                        break;
                    }
                    if (prev == "S") {
                        splits[point] = 1;
                        break;
                    }

                    vector<string> row = diagram[prevRow];
                    int leftCol = point.second - 1;
                    if (leftCol >= 0) {
                        if (row[leftCol] == "^") {
                            splits[point] += splits[{prevRow, leftCol}];
                        }
                    }

                    int rightCol = point.second + 1;
                    if (rightCol < row.size()) {
                        if (row[rightCol] == "^") {
                            splits[point] += splits[{prevRow, rightCol}];
                        }
                    }

                    prevRow--;
                }
            }
        }

    public:
        Solution* part1Test() {
            stringstream ss(TEST_INPUT);
            Utils::Grid<string> diagram = Utils::Grid<string>::toGrid(
                ss,
                '\n',
                [](char& v) { return string({ v }); }
            );
            diagram.print();

            long long noSplit = 0;

            diagram.navigateLTR([&diagram, &noSplit](Utils::Point2D point) {
                Solution::countSplits(diagram, noSplit, point);
            }
            );
            cout << "My yellow stream has splits " << noSplit << endl;

            return this;
        }

        Solution* part1() {
            Utils::FileReader reader("inputs/day7.txt");
            stringstream stream = reader.toStringStream();
            Utils::Grid<string> diagram = Utils::Grid<string>::toGrid(
                stream,
                '\n',
                [](char& v) { return string({ v }); }
            );
            diagram.print();

            long long noSplit = 0;
            diagram.navigateLTR([&diagram, &noSplit](Utils::Point2D point) {
                Solution::countSplits(diagram, noSplit, point);
            });
            cout << "My yellow stream has splits " << noSplit << endl;

            return this;
        }

        Solution* part2Test() {
            stringstream ss(TEST_INPUT);
            Utils::Grid<string> diagram = Utils::Grid<string>::toGrid(
                ss,
                '\n',
                [](char& v) { return string({ v }); }
            );
            diagram.print(false);

            map<Utils::Point2D, long long> splits;

            diagram.navigateLTR([&diagram, &splits](Utils::Point2D point) {
                Solution::countTimelines(diagram, splits, point);
            });

            long long sum = 0;
            for (auto p : splits) {
                sum += p.second;
            }
            cout << "My yellow stream has splits " << sum << endl;

            return this;
        }

        Solution* part2() {
            Utils::FileReader reader("inputs/day7.txt");
            stringstream stream = reader.toStringStream();
            Utils::Grid<string> diagram = Utils::Grid<string>::toGrid(
                stream,
                '\n',
                [](char& v) { return string({ v }); }
            );
            diagram.print(false);

            map<Utils::Point2D, long long> splits;

            diagram.navigateLTR([&diagram, &splits](Utils::Point2D point) {
                Solution::countTimelines(diagram, splits, point);
            });

            long long sum = 0;
            for (auto p : splits) {
                sum += p.second;
            }
            // plus 1 for good measure
            cout << "My yellow stream has splits " << sum + 1 << endl;

            return this;
        }
    };
}