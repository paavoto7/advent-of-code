#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "../utils/helper.h"
using namespace std;


/* Get the rules into a map
*/
unordered_map<int, unordered_set<int>> loadRules(const vector<string> &input) {
    unordered_map<int, unordered_set<int>> output;

    for (const string &line: input) {
        if (line.find_first_not_of(" ") != string::npos) {
            int bar = line.find("|");
            output[stoi(line.substr(0,bar))].insert(stoi(line.substr(bar+1, line.size()-1)));
        } else {
            break; // Exit when rules end in the input
        }
    }

    return output;
    
}

/* This was a surprisingly neat solution for today.
   It simply checks for part 1 whether the updates are sorted
   based on the rules. For part 2 the only addition is to
   sort the ones that are incorrect.

   This approach should not work as the ruleset is non-transitive.
   However, the actual updates were structured in a way that this
   did not cause any problems.

   Initially I solved part 1 differently. When my part 2
   solution was starting to get too expensive for my liking,
   I scrapped it. I looked at the input structure and decided to give
   sorting a go based on a that. Luckily it worked for the sake of execution time.
*/
int part12(const vector<string> &input, bool part2) {
    unordered_map<int, unordered_set<int>> rules = loadRules(input);
    vector<vector<int>> nums;

    // Get the "Updates" from the input
    for (int i = 0; i < input.size(); ++i) {
        if (input[i].find_first_not_of(" ") == string::npos) {
            nums = stringVecTo2DIntVec(vector<string> (input.begin()+i, input.end()), ',');
        }
    }

    int sum = 0;

    // Lambda to use for sorting and checking
    auto sortfunc = [&](int a, int b) {
        return rules[a].count(b);
    };

    for (vector<int> vec: nums) {
        bool sorted = is_sorted(vec.begin(), vec.end(), sortfunc);
        if (sorted && !part2) {
            sum += vec[vec.size()/2];
        } else if (!sorted && part2) {
            sort(vec.begin(), vec.end(), sortfunc);
            sum += vec[vec.size()/2];
        }
    }
    return sum;
}


// These are seperate function to measure the time correctly for both
int part1(const vector<string> &input) {
    return part12(input, false);
}

int part2(const vector<string> &input) {
    return part12(input, true);
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day5.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    auto beforeP1 = chrono::high_resolution_clock::now();
    int result1 = part1(input);
    auto afterP1 = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(afterP1 - beforeP1).count();
    cout << "Part 1: " << result1 << " - Time: " << time1 / 1000.0 << "ms" << endl;;

    auto beforeP2 = chrono::high_resolution_clock::now();
    int result2 = part2(input);
    auto afterP2 = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::microseconds>(afterP2 - beforeP2).count();
    cout << "Part 2: " << result2 << " - Time: " << time2 / 1000.0 << "ms" << endl;
}
