#include <vector>
#include <string>

#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;

/*
This first part uses my length finder and number splitting
functions from last year. It could be done easily with substrings,
but this seems to on my machine at least achieve better running time.
The lengthFinder and splitNum are in the utils now.
*/
long long part1(const vector<string>& input) {
    
    vector<vector<string>> ranges;

    for (auto& row : tokenizer(input[0], ',')) {
        ranges.push_back(tokenizer(row, '-'));
    }

    long long invIdSum = 0;
    
    for (auto& range : ranges) {
        const auto start = stoll(range[0]);
        const auto end = stoll(range[1]);
        
        for (auto i = start; i <= end; i++) {
            if (lengthFinder(i) % 2 != 0) continue;
            
            auto splits = splitNum(i);

            if (splits.first == splits.second) {
                invIdSum += i;
                // Small trick to improve running time
                i += splits.first;
            }
            
        }
    }
    
    return invIdSum;
}

// Helper function for second part so it is easier to read
bool isInvalid(const string& id, int n) {
    const int width = id.length() / n;

    // Loop over the n wide segment
    for (int i = 0; i < width; ++i) {
        char first = id[i];

        // Check if the letter/number is same in each n segments
        for (int j = 1; j < n; ++j) {
            if (id[width * j + i] != first) return false;
        }
    }

    return true;
}

/*
I couln't reuse my first part logic really, so this is a bit more complicated.
Different from part 1, it just converts the ranges to strings. This is done
in order to compare with > 2 wide segments.

The running time of this is approximately 3 times higher than the first part.
But had I used substr in the first part, the running time would have been roughly the same.
*/
long long part2(const vector<string>& input) {
    
    vector<vector<string>> ranges;
    // Not beautiful, but has little to no effect on running time
    for (auto& row : tokenizer(input[0], ',')) {
        ranges.push_back(tokenizer(row, '-'));
    }

    long long invIdSum = 0;
    
    for (auto& range : ranges) {
        const auto start = stoll(range[0]);
        const auto end = stoll(range[1]);
        
        for (auto i = start; i <= end; i++) {
            auto id = to_string(i);
            const int n = id.length();

            // Loop over the sequences
            for (int k = 2; k <= n; ++k) {
                if (n % k != 0) continue;

                if (isInvalid(id, k)) {
                    invIdSum += i;
                    break;
                }
            }
        }
    }
    
    return invIdSum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day1.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
