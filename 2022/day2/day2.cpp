#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

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

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}

