#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "../utils/helper.h"
#include "../utils/timer.h"
using namespace std;


struct dividedPair {
    long long first;
    long long second;
};

dividedPair splitNum(const long long& a) {
    long long divider = 10;
    while (a / divider >= divider) {
        divider *= 10;
    }
    return dividedPair{a / divider, a % divider};
}


int lengthFinder(long long n) {
    int len = 1;
    while (n /= 10LL) ++len;
    return len;
}


void blinker(unordered_map<long long, long long>& stones) {

    const auto original = stones;    
    
    for (const auto& [stone, amount]: original) {
        if (amount < 1) continue;
        stones[stone] -= amount;
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
}


int part1(const string& input) {
    int sum = 0;

    unordered_map<long long, long long> stoneTimes;
    for (auto stone: tokenizerToLongLong(input, ' ')) {
        stoneTimes[stone]++;
    }

    for (int i = 0; i < 25; ++i){
        blinker(stoneTimes);
    }

    for (const auto& [stone, amount]: stoneTimes) {    
        sum += amount;
    }

    return sum;
}


long long part2(const string& input) {
    long long sum = 0;

    unordered_map<long long, long long> stoneTimes;
    for (auto stone: tokenizerToLongLong(input, ' ')) {
        stoneTimes[stone]++;
    }

    for (int i = 0; i < 75; ++i){
        blinker(stoneTimes);
    }
    
    for (const auto& [stone, amount]: stoneTimes) {    
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
