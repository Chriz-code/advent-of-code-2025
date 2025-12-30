#ifndef MACHINE_H
#define MACHINE_H

#include "stringutils.cpp"
#include <string>
#include <functional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace Utils {
    using namespace std;

    using button = vector<int>;

    class machine {
    private:
        function<vector<string>(string, char)> split = Utils::StringUtils::split;

        string _src;
        string _goal;

        string _display;
        vector<button> _buttons;
        vector<int> _joltage;

        vector<button> to_buttons(vector<string> parts) {
            using namespace std;

            vector<button> result;
            for (auto& p : parts) {
                p.erase(remove(p.begin(), p.end(), '('), p.end());
                p.erase(remove(p.begin(), p.end(), ')'), p.end());
                button button;
                vector<string> nums = split(p, ',');
                for (auto& n : nums) {
                    button.push_back(stoi(n));
                }
                result.push_back(button);
            }
            return result;
        }

        vector<int> to_joltage(string joltages) {
            vector<int> result;
            joltages.erase(remove(joltages.begin(), joltages.end(), '{'), joltages.end());
            joltages.erase(remove(joltages.begin(), joltages.end(), '}'), joltages.end());
            for (auto& s : split(joltages, ',')) {
                result.push_back(stoi(s));
            }
            return result;
        }

        vector<pair<string, button>> next_states(const string& current) {
            vector<pair<string, button>> actions;
            for (auto& b : _buttons) {
                string next = current;
                for (auto& t : b) {
                    // plus 1 to skip '['
                    next[t + 1] = (next[t + 1] == '.') ? '#' : '.';
                }
                actions.push_back({ next, b });
            }
            return actions;
        }

    public:
        machine(string line) {
            vector<string> parts = split(line, ' ');
            _src = line;
            _goal = *parts.begin();
            _display = _goal;
            replace(_display.begin(), _display.end(), '#', '.');
            _buttons = to_buttons(vector<string>(parts.begin() + 1, parts.end() - 1));
            _joltage = to_joltage(parts.back());
        }

        int distance_to(const string node) {
            int distance = 0;
            for (int i = 0; i < min(_goal.length(), node.length()); ++i) {
                if (_goal[i] != node[i]) {
                    distance++;
                }
            }
            int gl = _goal.length();
            int nl = node.length();
            return distance += abs(gl - nl);
        }

        int bfs() {
            queue<string> q;
            unordered_map<string, string> parent;
            unordered_set<string> visited;
            vector<string> path;

            q.push(_display);
            visited.insert(_display);
            parent[_display] = "";

            bool found = false;
            while (!q.empty()) {
                string curr = q.front();
                q.pop();
                if (curr == _goal) {
                    found = true;
                    break;
                }
                for (auto& neighboor : next_states(curr)) {
                    if (visited.find(neighboor.first) == visited.end()) {
                        visited.insert(neighboor.first);
                        parent[neighboor.first] = curr;
                        q.push(neighboor.first);
                    }
                }

            }

            if (found) {
                string curr = _goal;
                while (!(curr == "")) {
                    path.push_back(curr);
                    curr = parent[curr];
                }
                reverse(path.begin(), path.end());
            }
            return path.size() - 1;
        }
    
        string getSrc() {
            return _src;
        }

        string getGoal() {
            return _goal;
        }

        string getDisplay() {
            return _display;
        }

        vector<button> getButtons() {
            return _buttons;
        }

        vector<int> getJoltage() {
            return _joltage;
        }
    };
}
#endif
