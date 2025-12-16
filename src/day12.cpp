#include "utils/stringutils.cpp"
#include "utils/filereader.cpp"
#include <vector>
#include <string>
#include <sstream>

namespace Day12 {
    struct test {
        const char* INPUT =
            "0:\n"
            "###\n"
            "##.\n"
            "##.\n"
            "\n"
            "1:\n"
            "###\n"
            "##.\n"
            ".##\n"
            "\n"
            "2:\n"
            ".##\n"
            "###\n"
            "##.\n"
            "\n"
            "3:\n"
            "##.\n"
            "###\n"
            "##.\n"
            "\n"
            "4:\n"
            "###\n"
            "#..\n"
            "###\n"
            "\n"
            "5:\n"
            "###\n"
            ".#.\n"
            "###\n"
            "\n"
            "4x4: 0 0 0 0 2 0\n"
            "12x5: 1 0 1 0 2 2\n"
            "12x5: 1 0 1 0 3 2";
    };

    struct present {
        std::vector<std::string> shape;
        int size() {
            return shape.size() * shape[0].length();
        }
    };

    struct tree {
        int rows, cols;
        std::vector<int> requirements;
    };

    class christmas {
    public:
        std::vector<present> presents;
        std::vector<Day12::tree> trees;

        tree toTree(std::string s) {
            using namespace std;
            tree tree;
            vector<string> split = Utils::StringUtils::split(s, ':');
            vector<string> dimensions = Utils::StringUtils::split(split[0], 'x');

            tree.rows = stoi(dimensions[0]);
            tree.cols = stoi(dimensions[1]);

            vector<string> nums = Utils::StringUtils::split(split[1], ' ');
            for (auto& num : nums) {
                if (!num.empty())
                    tree.requirements.push_back(stoi(num));
            }

            return tree;
        }

        christmas(std::stringstream& stream) {
            using namespace std;
            string line;

            present present;

            while (getline(stream, line)) {
                if (line.find('x') != std::string::npos) {
                    trees.push_back(toTree(line));
                    continue;
                }
                if (line.empty() && !present.shape.empty()) {
                    presents.push_back(present);
                    present = *new Day12::present();
                    continue;
                }
                if (line.find('#') != std::string::npos) {
                    present.shape.push_back(line);
                }
            }
        }
    };

    class Solution {
    private:
        test t;

        bool areaTest(std::vector<present>& presents, tree& tree) {
            long long totalArea = tree.rows * tree.cols;
            for (int i = 0; i < presents.size(); ++i) {
                int pSize = presents[i].size();
                int noP = tree.requirements[i];
                totalArea -= pSize * noP;
            }
            return totalArea >= 0;
        }

    public:
        Solution* part1Test() {
            using namespace std;
            stringstream stream(t.INPUT);
            christmas c(stream);
            int sum = 0;
            for (int i = 0; i < c.trees.size(); ++i) {
                cout << "Do presents fit with area under tree[" << i << "]: ";
                if (areaTest(c.presents, c.trees[i])) {
                    sum++;
                    cout << "True" << endl;
                }
                else {
                    cout << "False" << endl;
                }
            }
            return this;
        }

        Solution* part1() {
            using namespace std;

            Utils::FileReader reader("inputs/day12.txt");
            std::stringstream stream = reader.toStringStream();
            christmas c(stream);
            int sum = 0;
            for (int i = 0; i < c.trees.size(); ++i) {
                if (areaTest(c.presents, c.trees[i])) {
                    sum++;
                }
            }
            cout << "Big ahh trees: " << sum << endl;
            return this;
        }
    };
}