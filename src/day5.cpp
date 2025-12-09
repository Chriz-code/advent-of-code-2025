#include "utils/filereader.cpp"
#include "utils/range.cpp"
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <map>

namespace Day5 {
    using namespace std;

    class Solution {
    private:
        const char* TEST_INPUT =
            "3-5\n"
            "10-14\n"
            "16-20\n"
            "12-18\n"
            "20-20\n"
            //"10-16\n"
            "30-31\n"
            "\n"
            "1\n"
            "5\n"
            "8\n"
            "11\n"
            "17\n"
            "32";

        bool tryGetRange(string line, Utils::Range& outRange) {
            int rangeSplitIdx = line.find('-');
            bool isRange = rangeSplitIdx < line.length();
            if (isRange) {
                string start = line.substr(0, rangeSplitIdx);
                string end = line.substr(rangeSplitIdx + 1);
                outRange = { stoll(start), stoll(end) };
                return true;
            }
            return false;
        }

        bool isIngredientFresh(string line, vector<Utils::Range> ranges) {
            if (!line.empty()) {
                long long ingredient = stoll(line);
                for (Utils::Range range : ranges) {
                    if (ingredient >= range.start && ingredient <= range.end) {
                        return true;
                    }
                }
            }
            return false;
        }

        vector<Utils::Range> chainRanges(vector<Utils::Range> ranges) {
            vector<Utils::Range> chain;
            for (int ri = 0; ri < ranges.size(); ri++) {
                Utils::Range range = ranges[ri];
                if (chain.empty()) {
                    chain.push_back(range);
                    continue;
                }
                for (int fi = 0; fi < chain.size(); fi++) {
                    if (range.start < chain[fi].end && range.end >= chain[fi].end) {
                        range.start = chain[fi].end;
                    }
                }
                chain.push_back(range);
            }
            return chain;
        }

        vector<Utils::Range> collapseChain(vector<Utils::Range> chain) {
            vector<Utils::Range> collapes;
            for (int ci = 0; ci < chain.size(); ci++) {
                Utils::Range c = chain[ci];
                if (collapes.empty()) {
                    collapes.push_back(c);
                    continue;
                }
                bool swapped = false;
                for (int coi = 0; coi < collapes.size(); coi++) {
                    if (c.start <= collapes[coi].end) {
                        collapes[coi].end = c.end;
                        swapped = true;
                        break;
                    }
                }
                if (!swapped) {
                    collapes.push_back(c);
                }
            }
            return collapes;
        }

        void sortRanges(vector<Utils::Range>& ranges) {
            sort(ranges.begin(), ranges.end(),
                [](const Utils::Range& struct1, const Utils::Range& struct2) {
                return (struct1.start < struct2.start);
            });
        }

        long long countRange(vector<Utils::Range> ranges) {
            long long result = 0;

            for (int idx = 0; idx < ranges.size(); idx++) {
                Utils::Range current = ranges[idx];
                cout << current.start << "-" << current.end << endl;

                result += (current.end - current.start) + 1;
                if (idx > 0) {
                    Utils::Range prev = ranges[idx - 1];
                    if (current.start <= prev.end) {
                        long long prevDiff = (prev.end - current.start) + 1;
                        result -= prevDiff;
                        cout << "removed: " << prevDiff << endl;
                    }
                }
            }
            return result;
        }

        vector<Utils::Range> mergeRanges(vector<Utils::Range> ranges) {
            vector<Utils::Range> merged;
            vector<Utils::Range>::iterator current = ranges.begin();
            Utils::Range prev = *current;
            current++;
            while (current != ranges.end()) {
                if (prev.end >= current->start) {
                    prev.end = max(prev.end, current->end);
                }
                else {
                    merged.push_back(prev);
                    prev = *current;
                }
                current++;
            }
            merged.push_back(prev);
            return merged;
        }

    public:
        Solution* part1Test() {
            int result = 0;
            vector<Utils::Range> ranges;

            string line;
            stringstream ss(TEST_INPUT);
            while (getline(ss, line)) {
                Utils::Range range;
                if (tryGetRange(line, range)) {
                    ranges.push_back(range);
                    continue;
                }
                if (isIngredientFresh(line, ranges)) {
                    result++;
                }
            }
            cout << "IM SO FRESH " << result << endl;
            return this;
        }

        // 607
        Solution* part1() {
            Utils::FileReader reader("inputs/day5.txt");

            int result = 0;
            vector<Utils::Range> ranges;

            string line;
            while (getline(*reader.stream, line)) {
                Utils::Range range;
                if (tryGetRange(line, range)) {
                    ranges.push_back(range);
                    continue;
                }
                if (isIngredientFresh(line, ranges)) {
                    result++;
                }
            }
            cout << "IM SO FRESH " << result << endl;
            return this;
        }

        Solution* part2Test() {
            vector<Utils::Range> ranges;

            string line;
            stringstream ss(TEST_INPUT);
            while (getline(ss, line)) {
                Utils::Range range;
                if (tryGetRange(line, range)) {
                    ranges.push_back(range);
                }
            }

            sortRanges(ranges);
            long long result = countRange(ranges);

            cout << "IM SO FRESH " << result << endl;
            return this;
        }

        Solution* part2Test2() {
            vector<Utils::Range> ranges;
            string line;
            stringstream ss(TEST_INPUT);
            while (getline(ss, line)) {
                Utils::Range range;
                if (tryGetRange(line, range)) {
                    ranges.push_back(range);
                }
            }

            sortRanges(ranges);

            vector<Utils::Range> merged = mergeRanges(ranges);

            long long result = 0;
            for (Utils::Range c : merged) {
                cout << c.start << "-" << c.end << endl;
                result += (c.end - c.start) + 1;
            }
            cout << "I'M SO FRESH " << result << endl;
            return this;
        }

        // 1351599951 --Too low
        // 1351599937
        // 1504060042 -- Too low
        // 103731696
        // 432172526092597 -- Not right
        // 297457446068081 -- Not right
        // 388478108115531 -- Not right
        // 373466901069711 -- Not right
        // 297457446068081 -- Not right
        // 320445705285060 -- Not right
        // 299302746359206 -- Not right
        // 299302746359206
        // 
        Solution* part2() {
            vector<Utils::Range> ranges;
            string line;
            Utils::FileReader reader("inputs/day5.txt");
            while (getline(*reader.stream, line)) {
                Utils::Range range;
                if (tryGetRange(line, range)) {
                    ranges.push_back(range);
                }
            }

            sortRanges(ranges);
            long long result = countRange(ranges);

            cout << "IM SO FRESH " << result << endl;
            return this;
        }

        // 299302746359218 -- Not right
        // 299302746359206
        // 342433357244012
        Solution* part2_2() {
            vector<Utils::Range> ranges;
            string line;
            Utils::FileReader reader("inputs/day5.txt");
            while (getline(*reader.stream, line)) {
                Utils::Range range;
                if (tryGetRange(line, range)) {
                    ranges.push_back(range);
                }
            }

            sortRanges(ranges);

            vector<Utils::Range> merged = mergeRanges(ranges);

            long long result = 0;
            for (Utils::Range c : merged) {
                cout << c.start << "-" << c.end << endl;
                result += (c.end - c.start) + 1;
            }
            cout << "I'M SO FRESH " << result << endl;
            return this;
        }
    };
}
