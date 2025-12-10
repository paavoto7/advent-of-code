#include <string>
#include <vector>
#include <iostream>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;


int part1(const vector<string>& input) {
    int sum = 0;
    
    for (const string& line: input) {
        int middle = line.length() / 2;
        string first = line.substr(0, middle);
        string second = line.substr(middle);

        for (char c: first) {
            if (second.find(c) != string::npos) {
                if (islower(c)) {
                    sum += c - 'a' + 1;
                } else {
                    sum += c - 38;
                }
                break;
            }
        }
    }

    return sum;
}


int part2(const vector<string>& input) {
    int sum = 0;
    
    for (int i = 0; i < input.size(); i += 3) {
        
        // Using string_view here seems to perform a bit worse
        const string& first = input[i];
        const string& second = input[i+1];
        const string& third = input[i+2];

        for (char c: first) {
            if (second.find(c) != string::npos && third.find(c) != string::npos) {
                // The two magic numbers below are due to the ranges starting at 1
                if (islower(c)) {
                    sum += c - 'a' + 1;
                } else {
                    sum += 'z'-'a' + (c - 'A') + 2;
                }
                break;
            }
        }
    }

    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "./inputs/day3.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}

