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
        " 45 64  387 23 \n"
        "  6 98  215 314\n"
        "*   +   *   +  \n";

    bool isNumber(string &s)
    {
        istringstream iss(s);
        long long ll;
        return iss >> noskipws >> ll && iss.eof();
    }

    homework getProblems(stringstream &stream)
    {
        homework problems;
        int row = 0;
        string rowstr;
        while (getline(stream, rowstr))
        {
            int col = 0;
            string colstr;
            istringstream pstream(rowstr);
            while (getline(pstream, colstr, ' '))
            {
                if (!colstr.empty())
                {
                    if (problems.size() < col + 1)
                    {
                        problems.push_back(vector<string>());
                    }
                    problems[col].push_back(colstr);
                    col++;
                }
            }
            row++;
        }

        Printer::print2DVector(problems);
        return problems;
    }

    long long performOperation(long long a, long long b, string operation)
    {
        if (operation == "*")
        {
            return a * b;
        }
        if (operation == "+")
        {
            return a + b;
        }
        if (operation == "-")
        {
            return a - b;
        }
        if (operation == "/")
        {
            return a / b;
        }
        return -1;
    }

    homework getProblemsRTLC(stringstream &stream)
    {
        homework problems;
        int row = 0;
        string rowstr;
        while (getline(stream, rowstr))
        {
            int col = 0;
            for (auto colstr : rowstr)
            {
                if (colstr != ' ')
                {
                    if (problems.size() < col + 1)
                    {
                        problems.push_back(vector<string>());
                    }
                    problems[col].push_back(string({colstr}));
                    col++;
                }
            }
            row++;
        }

        Printer::print2DVector(problems);
        return problems;
    }

public:
    Day6 *part1Test()
    {
        long long total = 0;

        stringstream ss(TEST_INPUT);
        homework problems = getProblems(ss);
        for (auto problem : problems)
        {
            vector<string>::iterator current = problem.begin();
            string operation = problem.back();
            long long sum = stoll(*current);
            current++;
            while (current != problem.end())
            {
                if (*current != operation)
                {
                    sum = performOperation(sum, stoll(*current), operation);
                }
                current++;
            }
            total += sum;
        }

        cout << "Mathematical! " << total << endl;

        return this;
    }

    Day6 *part1()
    {
        long long total = 0;

        FileReader reader("inputs/day6.txt");
        stringstream stream = reader.toStringStream();

        homework problems = getProblems(stream);
        for (auto problem : problems)
        {
            vector<string>::iterator current = problem.begin();
            string operation = problem.back();
            long long sum = stoll(*current);
            current++;
            while (current != problem.end())
            {
                if (*current != operation)
                {
                    sum = performOperation(sum, stoll(*current), operation);
                }
                current++;
            }
            total += sum;
        }

        cout << "Mathematical! " << total << endl;

        return this;
    }

    Day6 *part2Test()
    {
        long long total = 0;

        stringstream ss(TEST_INPUT);
        homework problems = getProblemsRTLC(ss);
        for (auto problem : problems)
        {
            vector<string>::iterator current = problem.begin();
            string operation = problem.back();
            long long sum = stoll(*current);
            current++;
            while (current != problem.end())
            {
                if (*current != operation)
                {
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