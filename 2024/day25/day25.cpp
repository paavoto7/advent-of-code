#include <string>
#include <iostream>
#include <vector>
#include <array>
#include "../utils/helper.h"
#include "../utils/timer.h"
#include "../utils/gridPrinter.h"
using namespace std;


int part1(const vector<string>& input) {
    const int width = 5;
    vector<array<int, width>> locks, keys;

    array<int, width> buffer{-1, -1, -1, -1, -1};
    const int len = input.size();

    for (int i = 0; i <= len; ++i) {
        
        if (i == len || input[i] == "") {
            if (input[i-1][0] != '#') {
                locks.push_back(buffer);
            } else {
                keys.push_back(buffer);
            }
            buffer.fill(-1);
            continue;
        }

        for (int j = 0; j < width; ++j) {
            buffer[j] += (input[i][j] == '#') ? 1 : 0;
        }
    }

    int fits = 0;
    // It is naive, but it works well and fast
    for (const auto& lock: locks) {
        for (const auto& key: keys) {
            bool toAdd = true;
            for (int k = 0; k < width; ++k) {
                if (lock[k] + key[k] > width) {
                    toAdd = false;
                    break;
                }
            }
            if (toAdd) fits++;
        }
    }

    return fits;
}


string part2(const vector<string>& input) {
    return "Not yet 50 stars...";
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day25.txt";

    const vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
