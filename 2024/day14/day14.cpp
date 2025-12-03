#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <unordered_map>
#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;


constexpr int x = 101, y = 103;

void robotAdder(const vector<string>& input, vector<vector<pair<int, int>>>& robots) {
    for (const string& line: input) {
        vector<pair<int, int>> pairs;
        const auto& xys = tokenizer(line, ' ');
        for (int j = 0; j < 2; ++j) {
            int n = xys[j].find('=');
            auto nums = tokenizerToInt(xys[j].substr(n+1), ',');
            pairs.push_back({nums[0], nums[1]});
        }
        robots.push_back(pairs);
    }
}


int safetyFactor(const vector<vector<pair<int, int>>>& robots, unordered_map<int, int>& quadrants, const int& seconds) {
    constexpr int qx = x / 2, qy = y / 2;
    for (const auto& robot: robots) {
        int newX = robot[0].first + ((robot[1].first * seconds) % x);
        int newY = robot[0].second + ((robot[1].second * seconds) % y);

        // Account for out of bounds
        if (newX < 0 || newX >= x) newX += copysign(1, -newX)*x;
        if (newY < 0 || newY >= y) newY += copysign(1, -newY)*y;
        
        if (newX < qx && newY < qy) {
            quadrants[1]++;
        } else if (newX > qx && newY < qy) {
            quadrants[2]++;
        } else if (newX < qx && newY > qy) {
            quadrants[3]++;
        } else if (newX > qx && newY > qy) {
            quadrants[4]++;
        }
    }
    return quadrants[1] * quadrants[2] * quadrants[3] * quadrants[4]; 
}


int part1(const vector<string>& input) {
    int sum = 0;
    int seconds = 100;
    vector<vector<pair<int, int>>> robots;
    unordered_map<int, int> quadrants;
    
    robotAdder(input, robots);

    sum = safetyFactor(robots, quadrants, seconds);
    
    return sum;
}

// At least for my input, the christmas tree appears when the safety factor is minimised.
int part2(const vector<string>& input) {
    int low = 0;
    int seconds = x * y;
    int sum = INT32_MAX;
    vector<vector<pair<int, int>>> robots;
    unordered_map<int, int> quadrants;
    
    robotAdder(input, robots);

    for (int i = 1; i < seconds+1; ++i) {
        int safetyScore = safetyFactor(robots, quadrants, i);
        quadrants.clear();

        if (safetyScore < sum) {
            sum = safetyScore;
            low = i;
        }   
    }
    return low;
}



int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
