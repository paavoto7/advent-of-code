#include <vector>
#include <string>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

struct numInd {
    int ind;
    char val;
};

// A simple helper function to search for the highest number
// in a specified window without using any substrings.
numInd findLargest(const string& bank, int from, int to) {
    numInd largest = {0, '0'};

    for (int i = from; i < to; ++i) {
        if (bank[i] > largest.val) {
            largest.val = bank[i];
            largest.ind = i;
        }
    }
    return largest;
}

/*
This is very straightforward. We first search for the maximum
value in a bank. The second value we search from the remaining part i.e. {n + 1, size(bank)}.
If the max is the last value, we move max to be the second value.
Then search for the first value in the same way from {0, size(bank) - 1}.

Choosing the first occurence of the maximum value locks everything before it out. 
As the problem works by taking number 1 and number 2 to make 
number 12 (e.g. 8 and 4 = 84 => n1 * 10 + n2 = n3). We can see that when
numbers range from 1 to 9: max * 10 > (max - 1) * 10 + 9.
Same is true for edge case after reducing the search window.
*/
int part1(const vector<string>& input) {
    
    int joltage = 0;

    for (auto& bank: input) {
        auto largest = findLargest(bank, 0, bank.length());

        numInd second;
        if (largest.ind == bank.length() - 1) {
            second = largest;
            largest = findLargest(bank, 0, largest.ind);
        } else {
            second = findLargest(bank, largest.ind + 1, bank.length());
        }
        
        joltage += (largest.val - '0') * 10 + (second.val - '0');
        
    }
    
    return joltage;
}

/*
The solution uses a simple sliding window/two pointer technique.
The solution works for the input, but something more general
would have been better. In any case, this is relatively performant and correct.

The same findLargest as in first part is utilised here.
The reason we move the left to the chosen max value is that
if we chose a preceding smaller value, the total would clearly be smaller.
Skipping over values also must make the window smaller as we can't
afford to skip anymore then.
*/
long long part2(const vector<string>& input) {
    long long joltage = 0;

    const int batteries = 12;
    // All are same length
    const int window = input[0].length() - batteries + 1;
    for (auto& bank: input) {
        long long jolt = 0;

        int left = 0;
        int right = left + window;

        for (int i = batteries; i > 0; --i) {
            auto largest = findLargest(bank, left, right);
            
            // Move the sliding window pointers forward
            right++;
            left = largest.ind + 1;

            jolt = jolt * 10 + (largest.val - '0');
        }

        joltage += jolt;
    }
    
    return joltage;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
