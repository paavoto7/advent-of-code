#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../utils/helper.h"
using namespace std;

int part1(vector<int> left, vector<int> right) {

    int sum = 0;
    int size = left.size();

    for (int i = 0; i < size; ++i) {
        // Get the minimums using a standard function
        auto leftMin = *min_element(left.begin(), left.end());
        auto rightMin = *min_element(right.begin(), right.end());

        // Remove them from the vectors to be able do the above again
        left.erase(find(left.begin(), left.end(), leftMin));
        right.erase(find(right.begin(), right.end(), rightMin));

        sum += abs(leftMin - rightMin);
    }

    return sum;

}

int part2(vector<int> left, vector<int> right) {

    int size = left.size();
    vector<int> amounts(size, 0);

    // Loop over both lists to count the amounts
    for (int i = 0; i < size; ++i) {
        for (int num: right) {
            if (left[i] == num) {
                amounts[i]++;
            }
        }
    }

    return dotProduct(left, amounts);

}

int main() {

    vector<string> lines = getStringInput("../../inputs/day1.txt");
    vector<int> left;
    vector<int> right;

    // Break the lines to two lists
    for (string line: lines) {
        vector<string> tokens = tokenizer(line);
        left.push_back(stoi(tokens[0]));
        right.push_back(stoi(tokens[1]));
    }

    cout << "Part 1: " << part1(left, right) << endl;
    cout << "Part 2: " << part2(left, right) << endl;
}
