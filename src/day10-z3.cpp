#include "c++/z3++.h"
#include "utils/filereader.cpp"
#include "utils/machine.cpp"
#include <string>
#include <vector>
#include <sstream>

namespace Day10 {
    class z3solution {
    private:
        int totalPresses(Utils::machine& machine) {
            using namespace std;
            using namespace z3;
            using button = vector<int>;

            context ctx;
            optimize opt(ctx);

            int noButtons = machine.getButtons().size();
            vector<expr> buttonPresses;

            for (int i = 0; i < noButtons; ++i) {
                expr n = ctx.int_const(("n" + to_string(i)).c_str());
                opt.add(n >= 0);
                buttonPresses.push_back(n);
            }

            vector<int> joltages = machine.getJoltage();
            vector<button> buttons = machine.getButtons();

            for (long long k = 0; k < joltages.size(); ++k) {
                expr slotSum = ctx.int_val(0);
                for (int i = 0; i < noButtons; ++i) {
                    
                    bool affects = false;
                    for (int slot : buttons[i]) {
                        if (slot == k) {
                            affects = true;
                            break;
                        }
                    }

                    if (affects) {
                        slotSum = slotSum + buttonPresses[i];
                    }
                }
                opt.add(slotSum == ctx.int_val(joltages[k]));
            }

            expr resultExpr = ctx.int_val(0);
            for (const auto& n : buttonPresses) {
                resultExpr = resultExpr + n;
            }
            opt.minimize(resultExpr);

            if (opt.check() == sat) {
                model m = opt.get_model();
                cout << "min presses:" << m.eval(resultExpr) << endl;
                return m.eval(resultExpr).as_uint64();
            }
            return 0;
        }

    public:
    // 180 is too low
        z3solution* part2() {
            using namespace std;
            using namespace Utils;

            Utils::FileReader reader("inputs/day10.txt");
            stringstream stream = reader.toStringStream();
            vector<machine> machines;
            string line;

            long long answer = 0;

            while (getline(stream, line)) {
                machine m(line);
                answer += totalPresses(m);
            }
            cout << "I'm so tired of thiz3: " << answer << endl;;
            return this;
        }
    };
}