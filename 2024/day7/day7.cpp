#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include "../utils/helper.h"
using namespace std;


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

    auto beforeP1 = chrono::high_resolution_clock::now();
    long long result1 = part1(input);
    auto afterP1 = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(afterP1 - beforeP1).count();
    cout << "Part 1: " << result1 << " - Time: " << time1 / 1000.0 << "ms" << endl;;

    auto beforeP2 = chrono::high_resolution_clock::now();
    long long result2 = part2(input);
    auto afterP2 = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::microseconds>(afterP2 - beforeP2).count();
    cout << "Part 2: " << result2 << " - Time: " << time2 / 1000.0 << "ms" << endl;
}
