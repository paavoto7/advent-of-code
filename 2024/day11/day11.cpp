#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;

void blinker(unordered_map<long long, long long>& stones, unordered_map<long long, long long>& prevStones) {
    
    for (const auto& [stone, amount]: prevStones) {
        if (stone == 0) {
            stones[1] += amount;
        } else if (lengthFinder(stone) % 2 == 0) {
            auto [first, second] = splitNum(stone);
            stones[first] += amount;
            stones[second] += amount;
        } else {
            stones[stone*2024] += amount;
        }
    }
    swap(prevStones, stones);
    stones.clear();
}


int part1(const string& input) {
    int sum = 0;

    unordered_map<long long, long long> stoneTimes;
    unordered_map<long long, long long> prevStones;
    for (auto stone: tokenizerToLongLong(input, ' ')) {
        prevStones[stone]++;
    }

    for (int i = 0; i < 25; ++i){
        blinker(stoneTimes, prevStones);
    }

    for (const auto& [stone, amount]: prevStones) {    
        sum += amount;
    }

    return sum;
}


long long part2(const string& input) {
    long long sum = 0;

    unordered_map<long long, long long> stoneTimes;
    unordered_map<long long, long long> prevStones;
    for (auto stone: tokenizerToLongLong(input, ' ')) {
        prevStones[stone]++;
    }

    for (int i = 0; i < 75; ++i){
        blinker(stoneTimes, prevStones);
    }
    
    for (const auto& [stone, amount]: prevStones) {    
        sum += amount;
    }

    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    string input = getOneString(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
