#include "utils/filereader.cpp"
#include "utils/range.cpp"
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Day5
{
private:
    const char *TEST_INPUT =
        "3-5\n"
        "10-14\n"
        "16-20\n"
        "12-18\n"
        "\n"
        "1\n"
        "5\n"
        "8\n"
        "11\n"
        "17\n"
        "32";

    bool tryGetRange(string line, Range &outRange)
    {
        int rangeSplitIdx = line.find('-');
        bool isRange = rangeSplitIdx < line.length();
        if (isRange)
        {
            string start = line.substr(0, rangeSplitIdx);
            string end = line.substr(rangeSplitIdx + 1);
            outRange = {stoll(start), stoll(end)};
            return true;
        }
        return false;
    }

    bool isIngredientFresh(string line, vector<Range> ranges)
    {
        if (!line.empty())
        {
            long long ingredient = stoll(line);
            for (Range range : ranges)
            {
                if (ingredient >= range.start && ingredient <= range.end)
                {
                    return true;
                }
            }
        }
        return false;
    }

    vector<Range> chainRanges(vector<Range> ranges)
    {
        vector<Range> chain;
        for (int ri = 0; ri < ranges.size(); ri++)
        {
            Range range = ranges[ri];
            if (chain.empty())
            {
                chain.push_back(range);
                continue;
            }
            for (int fi = 0; fi < chain.size(); fi++)
            {
                if (range.start < chain[fi].end && range.end >= chain[fi].end)
                {
                    range.start = chain[fi].end;
                }
            }
            chain.push_back(range);
        }
        return chain;
    }

    vector<Range> collapseChain(vector<Range> chain)
    {
        vector<Range> collapes;
        for (int ci = 0; ci < chain.size(); ci++)
        {
            Range c = chain[ci];
            if (collapes.empty())
            {
                collapes.push_back(c);
                continue;
            }
            bool swapped = false;
            for (int coi = 0; coi < collapes.size(); coi++)
            {
                if (c.start <= collapes[coi].end)
                {
                    collapes[coi].end = c.end;
                    swapped = true;
                    break;
                }
            }
            if (!swapped)
            {
                collapes.push_back(c);
            }
        }
        return collapes;
    }

    int countRange(vector<Range> ranges)
    {
        int result;
        Range prev({ranges[0].start, ranges[0].end});
        for (Range v : ranges)
        {
            cout << v.start << ":" << v.end << endl;
            result += (v.end - v.start) + 1;
            prev = v;
        }
        return result;
    }

public:
    Day5 *part1Test()
    {
        int result = 0;
        vector<Range> ranges;

        string line;
        stringstream ss(TEST_INPUT);
        while (getline(ss, line))
        {
            Range range;
            if (tryGetRange(line, range))
            {
                ranges.push_back(range);
                continue;
            }
            if (isIngredientFresh(line, ranges))
            {
                result++;
            }
        }
        cout << "IM SO FRESH " << result << endl;
        return this;
    }

    // 607
    Day5 *part1()
    {
        FileReader reader("inputs/day5.txt");

        int result = 0;
        vector<Range> ranges;

        string line;
        while (getline(*reader.stream, line))
        {
            Range range;
            if (tryGetRange(line, range))
            {
                ranges.push_back(range);
                continue;
            }
            if (isIngredientFresh(line, ranges))
            {
                result++;
            }
        }
        cout << "IM SO FRESH " << result << endl;
        return this;
    }

    Day5 *part2Test()
    {
        vector<Range> ranges;

        string line;
        stringstream ss(TEST_INPUT);
        while (getline(ss, line))
        {
            Range range;
            if (tryGetRange(line, range))
            {
                ranges.push_back(range);
            }
        }

        sort(ranges.begin(), ranges.end());

        int result = countRange(ranges);

        cout << "IM SO FRESH " << result << endl;
        return this;
    }

    // 1351599951 --Too low
    // 1351599937
    // 1504060042 -- Too low
    // 103731696
    Day5 *part2()
    {
        vector<Range> ranges;

        string line;
        FileReader reader("inputs/day5.txt");
        while (getline(*reader.stream, line))
        {
            Range range;
            if (tryGetRange(line, range))
            {
                ranges.push_back(range);
            }
        }

        sort(ranges.begin(), ranges.end());

        int result = countRange(ranges);

        cout << "IM SO FRESH " << result << endl;
        return this;
    }
};