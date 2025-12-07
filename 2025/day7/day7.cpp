#include <vector>
#include <string>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

/*
Both parts solved with a very simple and similar solution.

The part 1 iterates over the input updating the beams vector
when it hits a caret. Upon hitting a caret, it splits the beam
by setting c - 1 and c + 1 to true. On each hit, it increments
splits counter.

Part 2 does almost the same, but changes the beams vector to be
long longs instead of bools. Now when hitting a caret, we simply
add the value in the beam that hit to the split ones, and set
the hitting one to 0. This could kind of be classified as a DP solution,
but is really a simple form of Pascal's pyramid.

The time complexity for both parts is O(n).
*/

int part1(const vector<string>& input) {
    const size_t height = input.size();
    const size_t width = input[0].size() - 1; // Really widthMinusOne
    
    vector<bool> beams(width, false);
    beams[width / 2] = true;

    int splits = 0;
    for (size_t i = 1; i < height; ++i) {
        auto& row = input[i];
        for (size_t j = 1; j < width; ++j) {
            if (row[j] == '.' || !beams[j]) continue;

            beams[j] = false;
            beams[j - 1] = true;
            beams[j + 1] = true;
            splits++;
            
        }
    }
    
    return splits;
}

long long part2(const vector<string>& input) {

    const size_t height = input.size();
    const size_t width = input[0].size() - 1; 
    
    vector<long long> lines(width, 0);
    lines[width / 2] = 1; // Start position

    long long splits = 0;
    for (size_t i = 1; i < height; ++i) {
        auto& row = input[i];
        for (size_t j = 1; j < width; ++j) {
            if (row[j] == '.') continue;
            // This is not needed for part 2 apparently
            //if (lines[j] == 0) continue;
            
            lines[j - 1] += lines[j];
            lines[j + 1] += lines[j];
            lines[j] = 0;
            
        }
    }

    for (long long space: lines) {
        splits += space;
    }
    
    return splits;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day7.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
