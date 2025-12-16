#include <algorithm>
#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>

namespace Day11 {
    struct test {
        const char* INPUT =
            "aaa: you hhh\n"
            "you: bbb ccc\n"
            "bbb: ddd eee\n"
            "ccc: ddd eee fff\n"
            "ddd: ggg\n"
            "eee: out\n"
            "fff: out\n"
            "ggg: out\n"
            "hhh: ccc fff iii\n"
            "iii: out";

        const char* INPUT_2 =
            "svr: aaa bbb\n"
            "aaa: fft\n"
            "fft: ccc\n"
            "bbb: tty\n"
            "tty: ccc\n"
            "ccc: ddd eee\n"
            "ddd: hub\n"
            "hub: fff\n"
            "eee: dac\n"
            "dac: fff\n"
            "fff: ggg hhh\n"
            "ggg: out\n"
            "hhh: out";
    };

    class Solution {
        using device = std::unordered_map<std::string, std::vector<std::string>>;
        using memoization = std::unordered_map<std::string, long long>;
        using visited = std::vector<std::string>;

        class memoization_dfs {
            device devices;
            memoization memo;

        public:
            memoization_dfs(device& devices) {
                this->devices = devices;
            }

            void reset() {
                memo.clear();
            }

            long long paths(std::string from, std::string to) {
                using namespace std;
                if (from == to) {
                    return 1;
                }

                if (memo.find(from) != memo.end()) {
                    return memo[from];
                }

                long long path = 0;

                if (devices.find(from) != devices.end()) {
                    for (const auto& neighbor : devices.at(from)) {
                        path += paths(neighbor, to);
                    }
                }

                memo[from] = path;

                return path;
            }
        };

    private:
        test t;

        device toMap(std::stringstream& stream) {
            using namespace std;
            string line;
            device result;
            while (getline(stream, line)) {
                vector<string> split = Utils::StringUtils::split(line, ':');
                string key = split[0];

                vector<string> values = Utils::StringUtils::split(split[1], ' ');
                auto ne = remove_if(values.begin(), values.end(), [](string value) {
                    return value.empty();
                });
                values.erase(ne);
                result[key] = values;
            }
            return result;
        }

        int dfs(device& devices, std::string from, std::string to = "out") {
            if (from == to) {
                return 1;
            }

            long long ret = 0;
            for (auto& ng : devices[from]) {
                ret += dfs(devices, ng, to);
            }
            return ret;
        };

    public:
        Solution* part1Test() {
            std::stringstream stream(t.INPUT);
            auto map = toMap(stream);
            std::cout << "Dedotaded wam: " << dfs(map, "you") << std::endl;
            return this;
        }

        Solution* part1() {
            Utils::FileReader reader("inputs/day11.txt");
            std::stringstream stream = reader.toStringStream();
            auto map = toMap(stream);
            std::cout << "Dedotaded wam: " << dfs(map, "you") << std::endl;
            return this;
        }

        Solution* part2Test() {
            std::stringstream stream(t.INPUT_2);
            device map = toMap(stream);
            memoization_dfs dfs(map);

            long long sum = 1;
            
            sum *= dfs.paths("svr", "fft");
            std::cout << "svr -> fft:" << sum << std::endl;;
            dfs.reset();

            sum *= dfs.paths("fft", "dac");
            std::cout << "fft -> dac:" << sum << std::endl;
            dfs.reset();
            
            sum *= dfs.paths("dac", "out");
            std::cout << "dac -> out:" << sum << std::endl;
            std::cout << "Dedotaded wam: " << sum << std::endl;
            return this;
        }

        Solution* part2() {
            Utils::FileReader reader("inputs/day11.txt");
            std::stringstream stream = reader.toStringStream();
            device map = toMap(stream);
            memoization_dfs dfs(map);

            long long sum = 1;
            
            sum *= dfs.paths("svr", "fft");
            std::cout << "fft -> dac:" << sum << std::endl;;
            dfs.reset();
            
            sum *= dfs.paths("fft", "dac");
            std::cout << "dac -> out:" << sum << std::endl;
            dfs.reset();
            
            sum *= dfs.paths("dac", "out");
            std::cout << "srv -> fft:" << sum << std::endl;
            std::cout << "Dedotaded wam: " << sum << std::endl;
            return this;
        }
    };
}