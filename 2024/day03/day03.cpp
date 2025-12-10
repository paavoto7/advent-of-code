#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <regex>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

int regCalc(regex reg, string input) {
    
    auto words_begin = sregex_iterator(input.begin(), input.end(), reg);
    auto words_end = sregex_iterator();

    int total = 0;
    
    while (words_begin != words_end) {
        
        string mul = words_begin->str();
        int comma = mul.find(",");
        int a = stoi(mul.substr(4, comma-4)), b = stoi(mul.substr(comma+1, mul.size()-2-comma));
        total += a * b;

        words_begin++;
    }
    
    return total;
}


int part1(string input) {
    regex reg("mul\\([0-9]+\\,[0-9]+\\)");

    return regCalc(reg, input);
}


int part2(string input) {
    // This regex find a do or start of file until it finds don't or end of file.
    regex reg("(^|do\\(\\))(.*?)(don't|$)");
    auto words_begin = sregex_iterator(input.begin(), input.end(), reg);
    auto words_end = sregex_iterator();

    int total = 0;
    // Here because it is faster this way
    regex regcalc("mul\\([0-9]+\\,[0-9]+\\)");
    
    while (words_begin != words_end) {
        
        string doDont = words_begin->str();

        total += regCalc(regcalc, doDont);

        words_begin++;
    }
    
    return total;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../../inputs/day2.txt";

    string input = getOneString(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
