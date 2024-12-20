#include <string>
#include <iostream>
#include <vector>
#include "../utils/helper.h"
#include "../utils/timer.h"
using namespace std;


bool isDesing(const vector<string>& towels, const string& design) {
    const int designLen = design.length();
    vector<bool> dynamic(designLen+1, false);
    dynamic[0] = true;
    
    for (int i = 1; i <= designLen; ++i) {
        for (const auto& towel: towels) {
            const int len = towel.length();
            if (i >= len && design.compare(i-len, len, towel) == 0) {
                dynamic[i] = dynamic[i-len];
                if (dynamic[i]) break;
            }
        }
    }
    return dynamic[designLen];
}

long long allDesignWays(const vector<string>& towels, const string& design) {
    const int designLen = design.length();
    vector<long long> dynamic(designLen+1, 0);
    dynamic[0] = 1;
    
    for (int i = 1; i <= designLen; ++i) {
        for (const auto& towel: towels) {
            const int len = towel.length();
            if (i >= len && design.compare(i-len, len, towel) == 0) {
                dynamic[i] += dynamic[i-len];
            }
        }
    }
    return dynamic[designLen];
}


int part1(const vector<string>& input) {
    int designs = 0;
    vector<string> combinations = tokenizer(input[0], ',');

    // First doesn't have whitespace
    for (int j = 1; j < combinations.size(); ++j) {
        combinations[j].erase(0, 1); // Remove whitespace
    }

    // Start from 2 due to an empty line
    for (int i = 2; i < input.size(); ++i) {
        designs += isDesing(combinations, input[i]);
    }

    return designs;
}


long long part2(const vector<string>& input) {
    long long designs = 0;
    vector<string> combinations = tokenizer(input[0], ',');

    // First doesn't have whitespace
    for (int j = 1; j < combinations.size(); ++j) {
        combinations[j].erase(0, 1); // Remove whitespace
    }
    
    // Start from 2 due to an empty line
    for (int i = 2; i < input.size(); ++i) {
        designs += allDesignWays(combinations, input[i]);
    }

    return designs;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day19.txt";

    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
