#include <vector>
#include <string>
#include <algorithm>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

// Documentation and optimisation coming again in the evening.

struct range {  
    long lower;
    long upper;
    
    range(long a, long b): lower(a), upper(b) {}

    bool operator < (const range& other) const {
        return lower < other.lower ;
    }
   
};

void splitAndConvert(const vector<string>& input, vector<range>& ranges, vector<long>& ids) {
    const size_t len = input.size();
    size_t i = 0;

    for (; i < len; ++i) {
        auto& line = input[i];
        if (line.empty()) break;
        auto dashPos = line.find_first_of('-');

        auto lower = stol(line.substr(0, dashPos));
        auto upper = stol(line.substr(dashPos + 1));

        ranges.emplace_back(lower, upper);
    }

    for (i += 1; i < len; ++i) {
        ids.push_back(stol(input[i]));
    }
    
}

int part1(const vector<string>& input) {
    
    vector<range> ranges;
    vector<long> ids;
    
    splitAndConvert(input, ranges, ids);

    int fresh = 0;
    for (long id: ids) {
        //cout << id << endl;
        for (auto& ran: ranges) {
            //cout << id << endl;
            if (id >= ran.lower && id <= ran.upper) {
                fresh++;
                break;
            }
        }
    }
    
    return fresh;
}


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

        if (next.lower <= current.upper) {
            if (next.upper > current.upper) {
                current.upper = next.upper;
            }
        } else { // next lower bigger than curr upper
            valids.push_back(current);
            current = next;
        }
    }
    valids.push_back(current);

    long fresh = 0;
    for (auto& ran: valids) {
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
