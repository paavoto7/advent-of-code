#include <string>
#include <iostream>
#include <vector>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;


int recurse(const vector<int>& operands, long long target, long long current, int depth, int max_depth) {
    if (depth == max_depth) {
        return current == target ? 1 : 0;
    } else {
        return recurse(operands, target, current* (long long)operands[depth], depth+1, max_depth)
            || recurse(operands, target, current+operands[depth], depth+1, max_depth);
    }
}


// The idea: (15, 43) -> (15 * 100) + 43 -> 1500 + 43 -> 1543
long long concat(long long a, long long b) {
    long long pow = 1;
    while (pow <= b) {
        pow *= 10LL;
    }
    return a * pow + b;
}


int recurse_concat(const vector<int>& operands, const long long target, long long current, int depth, const int max_depth) {
    if (depth == max_depth) {
        return current == target ? 1 : 0;
    } else {
        return recurse_concat(operands, target, current* (long long)operands[depth], depth+1, max_depth)
            || recurse_concat(operands, target, current+operands[depth], depth+1, max_depth)
            || recurse_concat(operands, target, concat(current, operands[depth]), depth+1, max_depth);
    }
}


long long part1(const vector<string>& grid) {
    
    long long sum = 0;
    
    for (const string& line: grid) {
        int colon = line.find(':');
        long long target = stoll(line.substr(0, colon));
        vector<int> operands = tokenizerToInt(line.substr(colon+1), ' ');

        if (recurse(operands, target, operands[0], 1, operands.size())) {
            sum += target;
        }
    }
    
    return sum;
}


long long part2(const vector<string>& grid) {
    long long sum = 0;
    
    for (const string& line: grid) {
        int colon = line.find(':');
        long long target = stoll(line.substr(0, colon));
        vector<int> operands = tokenizerToInt(line.substr(colon+1), ' ');

        if (recurse_concat(operands, target, operands[0], 1, operands.size())) {
            sum += target;
        }
    }
    
    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day6.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
