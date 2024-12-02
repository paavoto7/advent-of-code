#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include "../utils/helper.h"
using namespace std;


bool checkIsIncreasing(vector<int> tokens) {
    // Leaving this here even though it is not very foolproof
    int sum = 0;
    for (int i = 1; i < tokens.size(); ++i) {
        sum += tokens[i];
    }
    return tokens[0] < (sum / (tokens.size()-1));
}


bool isAscending(vector<int> tokens, bool reverse = false) {
    for (int i = 0; i < tokens.size()-1; i++) {
        if (!reverse && tokens[i] < tokens[i+1]) {
            return false;
        } else if (reverse && tokens[i] > tokens[i+1]) {
            return false;
        }
    }
    return true;
}


bool isSafe(vector<int> tokens) {
    for (int i = 0; i < tokens.size()-1; i++) {
        int diff = abs(tokens[i] - tokens[i+1]);

        if (!(1 <= diff && diff <= 3)) {
            return false;
        }
    }
    return true;
}


int part1(vector<string> input) {
    int safeCount = 0;

    for (string line: input) {
        vector<int> tokens = stringVecToIntVec(tokenizer(line));
        int previous = -1;
        bool isIncreasing = checkIsIncreasing(tokens);

        if ((isAscending(tokens) || isAscending(tokens, true)) && isSafe(tokens)) {
            safeCount++;
        }
    }
    return safeCount;
}


int part2(vector<string> input) {
    /* This solution is very ugly.
    It doesn't consider edge cases and the time complexity
    is not desirable. On the other hand, it does work so
    I guess it is sufficient enough.
    */

    int safeCount = 0;

    for (string line: input) {
        vector<int> originalTokens = stringVecToIntVec(tokenizer(line));

        for (int j = 0; j < originalTokens.size(); ++j) {
            vector<int> tokens = originalTokens;
            // Do this to generate all sublists where one number is taken out.
            tokens.erase(tokens.begin()+j);

            // If the order isn't right, no need to go forward
            if (!isAscending(tokens) && !isAscending(tokens, true)) continue;

            if (isSafe(tokens)) {
                safeCount++;
                break; // Break to save resources.
            }
        }
    }
    return safeCount;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../../inputs/day2.txt";

    vector<string> input = getStringInput(filepath);

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
