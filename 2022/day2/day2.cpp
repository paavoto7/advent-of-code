#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include "../../2024/utils/helper.h"
#include "../../2024/utils/gridPrinter.h"
using namespace std;

const unordered_map<char, int> hands = {
    {'A', 'Z'},
    {'X', 'C'},
    {'B', 'X'},
    {'Y', 'A'},
    {'C', 'Y'},
    {'Z', 'B'},
};


/* The magic number 87 is the ascii value for capital X minus one
*/
int part1(const vector<string>& input) {
    int sum = 0;
    
    for (const string& line: input) {
        char opp = line[0];
        char me = line[2];
        if (hands.at(me) == opp) {
            sum += me - 87 + 6;
        } else if (hands.at(opp) == me) {
            sum += me - 87;
        } else {
            sum += me - 87 + 3;
        }
    }
    return sum;
}


/* The magic number 64 is the ascii value for capital A minus one
*/
int part2(const vector<string>& input) {
    int sum = 0;
    
    for (const string& line: input) {
        char opp = line[0];
        char goal = line[2];
        if (goal == 'X') {
            // Defeat
            sum += hands.at(opp) - 87;
        } else if (goal == 'Y') {
            // Draw
            sum += opp - 64 + 3;
        } else {
            // Victory
            // Rock paper scissors conditions form circle so this just uses that
            sum += hands.at(hands.at(opp)) - 64 + 6;
        }
    }
    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "./inputs/day2.txt";

    // Pass the already parsed input for both
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

