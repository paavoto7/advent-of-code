#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "../utils/helper.h"
using namespace std;

int part1(vector<int> left, vector<int> right) {

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    
    int sum = 0;
    for (int i = 0; i < left.size(); ++i) {
        sum += abs(left[i] - right[i]);
    }

    return sum;

}

int part2(vector<int> left, vector<int> right) {
    /* Adds all numbers of right to map.
    Multiplies the left values by the amount of
    them in the map.

    I looked at my first solutions time complexity
    and figured there has to be a better way...
    */

    map<int, int> right_amounts;

    // Add the right values into map
    for (int r_value: right) {
       right_amounts[r_value]++;
    }

    int sum = 0;
    for (int l_value: left) {
        sum += l_value * right_amounts[l_value];
    }

    return sum;

}

int main(int argc, char *argv[]) {

    string filepath = "../../inputs/day1.txt";
    filepath = argc == 2 ? argv[1] : "./inputs/test.txt";

    vector<string> lines = getStringInput(filepath);
    vector<int> left, right;

    // Break the lines to two lists
    for (string line: lines) {
        vector<string> tokens = tokenizer(line);
        left.push_back(stoi(tokens[0]));
        right.push_back(stoi(tokens[1]));
    }

    cout << "Part 1: " << part1(left, right) << endl;
    cout << "Part 2: " << part2(left, right) << endl;
}
