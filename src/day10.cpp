#include "utils/stringutils.cpp"
#include "utils/filereader.cpp"
#include "utils/machine.cpp"
#include <string>
#include <vector>
#include <sstream>

namespace Day10 {
    using namespace std;
    using namespace Utility;

    class solution {
    private:
        const char* TEST_INPUT =
            "[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}\n"
            "[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}\n"
            "[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}";
    public:
        solution* part1Test() {
            stringstream stream(TEST_INPUT);
            vector<machine> machines;
            string line;
            long long sum = 0;
            while (getline(stream, line)) {
                machine m(line);
                sum += m.bfs();
            }
            cout << "I'm so tired of this: " << sum;
            return this;
        }

        solution* part1() {
            Utils::FileReader reader("inputs/day10.txt");
            stringstream stream = reader.toStringStream();
            vector<machine> machines;
            string line;
            long long sum = 0;
            while (getline(stream, line)) {
                machine m(line);
                sum += m.bfs();
            }
            cout << "I'm so tired of this: " << sum;
            return this;
        }
    };
}
