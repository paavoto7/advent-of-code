#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include "../utils/helper.h"
#include "../utils/timer.h"
#include "../utils/gridPrinter.h"
using namespace std;


uint64_t part1(const vector<string>& input) {
    uint64_t sum = 0;
    constexpr int modulo = 16777216;

    for (const string& line: input) {
        uint64_t secret = stoll(line);
        for (int i = 0; i < 2000; i++) {
            secret = (secret ^ (secret * 64)) % modulo;
            secret = (secret ^ (secret / 32)) % modulo;
            secret = (secret ^ (secret * 2048)) % modulo;
        }
        sum += secret;
    }
    return sum;
}


void sequencer(uint64_t secret, unordered_map<uint64_t, uint64_t>& sequences) {
    constexpr int modulo = 16777216;
    // Base 19 total values for four numbers
    constexpr int baseMod = 19 * 19 * 19 * 19;

    vector<bool> alreadyAdded(baseMod, false);
    
    int price = secret % 10;
    int index = 0;

    for (int i = 0; i < 2000; ++i) {
        secret = (secret ^ (secret * 64)) % modulo;
        secret = (secret ^ (secret / 32)) % modulo;
        secret = (secret ^ (secret * 2048)) % modulo;
        
        int newPrice = secret % 10;
        
        // Convert the numbers into base 19
        index = (index * 19 + newPrice - price + 9) % baseMod;
        if (!alreadyAdded[index]) {
            sequences[index] += newPrice;
            alreadyAdded[index] = true;
        }
        price = newPrice;
    }
}


/* At first I mapped the sequences of the four numbers as vectors
   to the map, but that ran in ~6 seconds. A bit of
   optimisation and the solution now runs in ~500 ms.
   The four numbers are always in [-9, 9] (+9=>[0, 18]) range, so
   base 19 numbers were possible to represent the sequences.
*/
uint64_t part2(const vector<string>& input) {
    uint64_t sum = 0;
    unordered_map<uint64_t, uint64_t> sequences;

    for (const auto& line: input) {
        sequencer(stoi(line), sequences);
    }

    for (const auto& [_, v]: sequences) {
        sum = max(sum, v);
    }

    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day19.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
