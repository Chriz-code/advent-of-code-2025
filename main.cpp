#include <iostream>
#include "days/day1.cpp"

int main(int, char**){
    std::cout << "Hello, from advent-of-code-2025!\n";

    Day1 day1;
    int testResult = day1.part1Test();
    //cout << "The result of day1Test is " << testResult << endl;
    cout << "The result of day1 is " << day1.part1() << endl;

}
//16
//461
//698