#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

/*
Just adding this here for my own reference and for the sake
of not having to delete code I already wrote.
*/

struct numInd {
    int ind;
    char val;
};

numInd findLargest(const string& bank, int from, int to) {
    numInd largest = {0, '0'};

    for (int i = from; i < to; ++i) {
        if (bank[i] > largest.val) {
            largest.val = bank[i];
            largest.ind = i;
        }
    }
    return largest;
}

// This solution is correct as well for the first part, but is significantly slower
int part1(const vector<string>& input) {
    vector<vector<int>> banks;
    for (auto& line: input) {
        banks.push_back(stringToIntVec(line));
    }
    
    int joltage = 0;

    for (auto& bank: banks) {
        auto maxIt = max_element(bank.begin(), bank.end());
        int max = *maxIt;

        int second;
        if (next(maxIt) == bank.end()) {
            second = max;
            max = *max_element(bank.begin(), maxIt);
        } else {
            second = *max_element(maxIt + 1, bank.end());
        }

        joltage += max * 10 + second;
    }
    
    return joltage;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
}
