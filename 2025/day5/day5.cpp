#include <vector>
#include <string>
#include <algorithm>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

// A simple utility container for the ranges
struct range {  
    long lower;
    long upper;
    
    range(long a, long b): lower(a), upper(b) {}

    bool operator < (const range& other) const {
        return lower < other.lower;
    }
   
};

/*
The solution works by parsing the ranges and looping over
IDs while trying to match each to a range.
Reusing the iterator variable allows to skip if checks in the
ID-loop later.

Sorting the ranges seems to give performance boost on my input and machine,
but as we do not sort IDs, that is anecdotal.

Having IDs sorted would be nice as then we could optimise the range 
checks more. Parsing, sorting and finally looping over IDs instead
of looping once while doing more range checks is unlikely to outperform.

Suppose n is the number of IDs => parsing is O(n), sorting O(n log n)
and looping worst case O(n * m). Of course, the average case might be significantly better.
For the current one we loop and parse in the same time, which results in O(n * m).
The real performance in both cases depends on ones input IDs and range distribution.
*/
int part1(const vector<string>& input) {
    const size_t len = input.size();
    size_t i = 0;

    vector<range> ranges;
    for (; i < len; ++i) {
        auto& line = input[i];
        if (line.empty()) break; // Start of IDs
        auto dashPos = line.find_first_of('-');

        auto lower = stol(line.substr(0, dashPos));
        auto upper = stol(line.substr(dashPos + 1));

        ranges.emplace_back(lower, upper);
    }

    // This interestingly gives some performance boost.
    // Our IDs are not sorted, but it seems that more
    // of the IDs are in the lower end of the ranges.
    // That of course might not be true for all inputs.
    sort(ranges.begin(), ranges.end());

    int fresh = 0;
    for (i += 1; i < len; ++i) {
        auto id = stol(input[i]);

        for (auto& ran: ranges) {
            if (id >= ran.lower && id <= ran.upper) {
                fresh++;
                break;
            }
        }
    }
    
    return fresh;
}

/*
The solution fist builds the ranges like in part 1 and sorts them.
It then merges overlapping ranges into new ones and adds
them to a new vector for non-overlapping ranges.

This allows us to finally loop over each merged range and simply add
the length to the answer.

There are so few ranges (not the range lengths) that sorting and iterating
over them results in very quick execution times.
*/
long part2(const vector<string>& input) {
    vector<range> ranges;

    for (const auto& line: input) {
        if (line.empty()) break;
        auto dashPos = line.find_first_of('-');

        auto lower = stol(line.substr(0, dashPos));
        auto upper = stol(line.substr(dashPos + 1));

        ranges.emplace_back(lower, upper);
    }

    sort(ranges.begin(), ranges.end());

    vector<range> valids;
    range current = ranges[0];

    for (auto& next: ranges) {
        // E.g. 1-10 and 5-15 => 1-15
        if (next.lower <= current.upper) {
            if (next.upper > current.upper) {
                current.upper = next.upper; // Extends the range
            }
        }
        else { // next.lower > current.upper
            valids.push_back(current);
            current = next;
        }
    }
    valids.push_back(current);

    long fresh = 0;
    for (auto& ran: valids) {
        // Plus one as the ranges are inclusive
        fresh += ran.upper - ran.lower + 1;
    }
    
    return fresh;
}

int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
