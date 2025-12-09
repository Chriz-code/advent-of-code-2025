#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

namespace Day1 {
    using namespace std;
    
    class Solution {
    private:
        const string inputFile = "inputs/day1.txt";

        int dial = 50;
        int result = 0;

        ifstream* stream() {
            ifstream* inputStream = new ifstream(inputFile);

            if (!(*inputStream).is_open()) {
                cout << "Unable to open file" << endl;
                return nullptr;
            }
            return inputStream;
        }

        int mod2(int a, int m) {
            return (a % m + m) % m;
        }

        int loopDial(int value) {
            return mod2(value, 100);
        }

        int turnDial(string line) {
            int turn = stoi(line.substr(1));
            if (line[0] == 'L') {
                return -turn;
            }
            else {
                return turn;
            }
        }

        void landOnZero() {
            if (dial == 0) {
                result += 1;
            }
        }

    public:
        void reset() {
            dial = 50;
            result = 0;
        }

        Solution* part1Test() {
            reset();
            stringstream ss("L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82");

            result = 0;
            dial = 50;

            string line;
            while (getline(ss, line, '\n')) {
                dial = loopDial(dial + turnDial(line));
                cout << "The dial is rotated " << line << " to point at ";
                landOnZero();
                cout << "\n";
            }
            return this;
        }

        Solution* part2Test() {
            reset();

            stringstream ss("L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82");

            string line;
            while (getline(ss, line)) {
                int turn = turnDial(line);
                if (turn < 0) {
                    for (int i = 0; i > turn; i--) {
                        int l = loopDial(dial - 1);
                        if (l == 0) {
                            cout << "*" << endl;
                            result++;
                        }
                        dial = l;
                    }
                }
                else {
                    for (int i = 0; i < turn; i++) {
                        int l = loopDial(dial + 1);
                        if (l == 0) {
                            cout << "*" << endl;
                            result++;
                        }
                        dial = l;
                    }
                }

                cout << "The dial is rotated " << line << " to point at " << dial << endl;
                cout << "\n";
            }
            return this;
        }

        // The right answer is 1139
        Solution* part1() {
            reset();

            ifstream* input = stream();
            string line;
            while (getline(*input, line)) {
                dial = loopDial(dial + turnDial(line));
                cout << "The dial is rotated " << line << " to point at ";
                landOnZero();
                cout << "\n";
            }
            (*input).close();
            return this;
        }

        // 6546
        // 6085 --too low
        // 7756 --too high
        Solution* part2() {
            reset();

            ifstream* input = stream();
            string line;
            while (getline(*input, line)) {
                int turn = turnDial(line);
                if (turn < 0) {
                    for (int i = 0; i > turn; i--) {
                        int l = loopDial(dial - 1);
                        if (l == 0) {
                            cout << "*" << endl;
                            result++;
                        }
                        dial = l;
                    }
                }
                else {
                    for (int i = 0; i < turn; i++) {
                        int l = loopDial(dial + 1);
                        if (l == 0) {
                            cout << "*" << endl;
                            result++;
                        }
                        dial = l;
                    }
                }

                cout << "The dial is rotated " << line << " to point at " << dial << endl;
                cout << "\n";
            }
            (*input).close();
            return this;
        }

        void printResult() {
            cout << "The result of day1 is " << result << endl;
        }
    };
}
