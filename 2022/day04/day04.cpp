#include <string>
#include <vector>
#include <utility> // Pair
#include <iostream>
#include <chrono>
#include <functional>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;


// This is very inefficient, but convenient enough to justify using it
vector<pair<int, int>> convert(const vector<string>& input) {

    vector<pair<int, int>> output;
    
    for (const string& line: input) {
        for (const string& pair: tokenizer(line, ',')) {
            int dash = pair.find('-');
            int num1 = stoi(pair.substr(0, dash));
            int num2 = stoi(pair.substr(dash+1));
            output.push_back({num1, num2});
        }
    }
    return output;
}

// I did this just to see how it's made. The program doesn't currently use it though.
int overlapper(const vector<string>& input,
               function<bool(pair<int, int> left, pair<int, int> right)> isAllowed)
    {
    int sum = 0;

    vector<pair<int, int>> pairs = convert(input);

    for (int i = 0; i < pairs.size(); i += 2) {
        const auto left = pairs[i];
        const auto right = pairs[i+1];
        
        if (isAllowed(left, right))
        {
            sum++;
        }
    }

    return sum;
}


int part1(const vector<pair<int, int>>& pairs) {
    int sum = 0;

    for (int i = 0; i < pairs.size(); i += 2) {
        const auto left = pairs[i];
        const auto right = pairs[i+1];
        
        if (left.first <= right.first && left.second >= right.second ||
            left.first >= right.first && left.second <= right.second)
        {
            sum++;
        }
    }

    return sum;
}


// Very similar to part 2 but decided to just stick to this for simplicity
int part2(const vector<pair<int, int>>& pairs) {
    int sum = 0;

    for (int i = 0; i < pairs.size(); i += 2) {
        const auto left = pairs[i];
        const auto right = pairs[i+1];
        
        if (left.first <= right.second && left.second >= right.first) {
            sum++;
        }
    }

    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "./inputs/day3.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);
    // Putting the parsing here and not recording here is a beat cheating...
    vector<pair<int, int>> pairs = convert(input);

    timer(part1, pairs, "Part 1: ");
    timer(part2, pairs, "Part 2: ");
}
