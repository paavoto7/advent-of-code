#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <regex>
#include "../utils/helper.h"
using namespace std;


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

    auto beforeP1 = chrono::high_resolution_clock::now();
    int result1 = part1(input);
    auto afterP1 = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(afterP1 - beforeP1).count();
    cout << "Part 1: " << result1 << " - Time: " << time1 / 1000.0 << "ms" << endl;;

    auto beforeP2 = chrono::high_resolution_clock::now();
    int result2 = part2(input);
    auto afterP2 = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::microseconds>(afterP2 - beforeP2).count();
    cout << "Part 2: " << result2 << " - Time: " << time2 / 1000.0 << "ms" << endl;
}
