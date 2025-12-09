#include "utils/filereader.cpp"
#include "utils/printer.cpp"
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

namespace Day6 {
    using namespace std;

    typedef vector<vector<string>> homework;

    class Solution {
    private:
        const char* TEST_INPUT =
            "123 328  51 64 \n"
            " 45 64  387 23 \n"
            "  6 98  215 314\n"
            "*   +   *   +  \n";

        bool isNumber(string& s) {
            istringstream iss(s);
            long long ll;
            return iss >> noskipws >> ll && iss.eof();
        }

        homework getProblems(stringstream& stream) {
            homework problems;
            int row = 0;
            string rowstr;
            while (getline(stream, rowstr)) {
                int col = 0;
                string colstr;
                istringstream pstream(rowstr);
                while (getline(pstream, colstr, ' ')) {
                    if (!colstr.empty()) {
                        if (problems.size() < col + 1) {
                            problems.push_back(vector<string>());
                        }
                        problems[col].push_back(colstr);
                        col++;
                    }
                }
                row++;
            }

            Utils::Printer::print2DVector(problems);
            return problems;
        }

        long long performOperation(long long a, long long b, string operation) {
            if (operation == "*") {
                return a * b;
            }
            if (operation == "+") {
                return a + b;
            }
            if (operation == "-") {
                return a - b;
            }
            if (operation == "/") {
                return a / b;
            }
            return -1;
        }

        homework getProblemsRTLC(stringstream& stream) {
            vector<string> grid;
            string rowstr;
            while (getline(stream, rowstr)) {
                grid.push_back(rowstr);
            }

            homework problems = homework({ vector<string>() });

            string sign;
            vector<string> numbers;

            int colSize = grid[0].length();
            for (int col = 0; col < colSize; col++) {
                string number;
                for (int row = 0; row < grid.size(); row++) {
                    if (grid[row][col] == ' ') {
                        continue;
                    }

                    string s = string({ grid[row][col] });
                    if (isNumber(s)) {
                        number += s;
                        continue;
                    }
                    sign = s;
                }
                if (number.empty()) {
                    problems.back().push_back(sign);
                    problems.push_back(vector<string>());
                }
                else {
                    problems.back().push_back(number);
                }
            }
            // Last column is not empty
            problems.back().push_back(sign);

            Utils::Printer::print2DVector(problems);
            return problems;
        }

    public:
        Solution* part1Test() {
            long long total = 0;

            stringstream ss(TEST_INPUT);
            homework problems = getProblems(ss);
            for (auto problem : problems) {
                vector<string>::iterator current = problem.begin();
                string operation = problem.back();
                long long sum = stoll(*current);
                current++;
                while (current != problem.end()) {
                    if (*current != operation) {
                        sum = performOperation(sum, stoll(*current), operation);
                    }
                    current++;
                }
                total += sum;
            }

            cout << "Mathematical! " << total << endl;

            return this;
        }

        Solution* part1() {
            long long total = 0;

            Utils::FileReader reader("inputs/day6.txt");
            stringstream stream = reader.toStringStream();

            homework problems = getProblems(stream);
            for (auto problem : problems) {
                vector<string>::iterator current = problem.begin();
                string operation = problem.back();
                long long sum = stoll(*current);
                current++;
                while (current != problem.end()) {
                    if (*current != operation) {
                        sum = performOperation(sum, stoll(*current), operation);
                    }
                    current++;
                }
                total += sum;
            }

            cout << "Mathematical! " << total << endl;

            return this;
        }

        Solution* part2Test() {
            long long total = 0;

            stringstream ss(TEST_INPUT);
            homework problems = getProblemsRTLC(ss);
            for (auto problem : problems) {
                vector<string>::iterator current = problem.begin();
                string operation = problem.back();
                long long sum = stoll(*current);
                current++;
                while (current != problem.end()) {
                    if (*current != operation) {
                        sum = performOperation(sum, stoll(*current), operation);
                    }
                    current++;
                }
                total += sum;
            }

            cout << "Mathematical! " << total << endl;

            return this;
        }

        Solution* part2() {
            long long total = 0;

            Utils::FileReader reader("inputs/day6.txt");
            stringstream stream = reader.toStringStream();

            homework problems = getProblemsRTLC(stream);
            for (auto problem : problems) {
                vector<string>::iterator current = problem.begin();
                string operation = problem.back();
                long long sum = stoll(*current);
                current++;
                while (current != problem.end()) {
                    if (*current != operation) {
                        sum = performOperation(sum, stoll(*current), operation);
                    }
                    current++;
                }
                total += sum;
            }

            cout << "Mathematical! " << total << endl;

            return this;
        }
    };
}