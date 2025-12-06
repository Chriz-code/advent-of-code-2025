#include "utils/filereader.cpp"
#include "utils/printer.cpp"
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

typedef vector<vector<string>> homework;

class Day6
{
private:
    const char *TEST_INPUT =
        "123 328  51 64 \n"
        "45 64  387 23 \n"
        "6 98  215 314 \n"
        "*   +   *   + \n";

    bool isNumber(string& s) {
        istringstream iss(s);
        long long ll;
        return iss >> noskipws >> ll  && iss.eof();
    }

    homework getProblems(stringstream &stream)
    {
        homework problems;

        string problemLine;
        while (getline(stream, problemLine))
        {
            string problem;
            istringstream pstream(problemLine);
            vector<string> lineOfProblems;
            while (getline(pstream, problem, ' '))
            {
                if (!problem.empty())
                {
                    // problem.erase(remove_if(problem.begin(), problem.end(), ::isspace));
                    lineOfProblems.push_back(problem);
                }
            }
            problems.push_back(lineOfProblems);
        }

        const int SIZE = problems.size();
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if (i < j)
                {
                    swap(problems[i][j], problems[j][i]);
                }
            }
        }
        Printer::print2DVector(problems);
        return problems;
    }

public:
    Day6 *part1Test()
    {
        string line;
        stringstream ss(TEST_INPUT);
        homework problems = getProblems(ss);

        for (auto problem : problems) {
            long long sum = 0;

        }

        return this;
    }
};