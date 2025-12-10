#include <vector>
#include <string>

#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;

/*
The solution is not overly elegant or clever, but works well.

In the second part I just decided to go with blunt range-check.
I'm quite sure there is some relatively simple and more elegant
solution to it, but that is left for later.
*/

int part1(const vector<string>& input) {
    int pointToZero = 0;

    int dial = 50; // The start value
    for (auto rot : input) {
        auto dir = rot[0] == 'L' ? -1 : 1;
        auto amount = stoi(rot.substr( 1 ));
        
        dial = (dial + dir * amount) % 100;
 
        if (dial == 0) {
            ++pointToZero;
        }
    }
    
    return pointToZero;
}

int part2(const vector<string>& input) {
    int pointToZero = 0;

    int dial = 50; // The start value
    for (auto rot : input) {
        auto dir = rot[0] == 'L' ? -1 : 1;
        auto amount = stoi(rot.substr( 1 ));
        
        // Add how many times we go over 0
        pointToZero += amount / 100;
        
        bool wasZero = dial == 0;

        dial += dir * (amount % 100);

        // Very blunt, optimise later
        if (dial > 99 || dial < 0) {
            dial -= dir * 100;
            // If it was non-zero and is now non-zero, it has crossed
            // Multiple passes is handled earlier
            if (!wasZero && dial != 0) ++pointToZero;
        }

        if (dial == 0) {
            ++pointToZero;
        }
    }
    
    return pointToZero;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day1.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
