#include <vector>
#include <string>
#include <algorithm>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

struct Coordinate {
    int x;
    int y;

    Coordinate(int x, int y): x(x), y(y) {}

    long long area(const Coordinate& other) const {
        return (llabs(x - other.x) + 1) * (llabs(y - other.y) + 1); 
    }
};

/*
The solution checks every coordinate in the input with
ones that are after it in the read vector. It is simply
a brute-force check without any sorting or other major
optimizations.

The time complexity is effectively O(n^2), but for an input
size of ~500, it is quite instantaneous and acceptable.
*/
long long part1(const vector<string>& input) {
    vector<Coordinate> coordinates;
    
    for (auto& line: input) {
        auto comma = line.find_first_of(',');

        auto lower = stoi(line.substr(0, comma));
        auto upper = stoi(line.substr(comma + 1));

        coordinates.emplace_back(lower, upper);
    }

    const auto len = coordinates.size();

    long long maxArea = 0;
    long long interArea = 0;
    for (size_t i = 0; i < len; ++i) {
        auto& coord = coordinates[i];
        
        for (size_t j = i + 1; j < len; ++j) {
            interArea = coord.area(coordinates[j]);

            if (interArea > maxArea) maxArea = interArea;
        }
    }
    
    return maxArea;
}

int part2([[maybe_unused]] const vector<string>& input) {
    return 0;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
