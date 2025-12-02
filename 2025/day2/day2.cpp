#include <vector>
#include <string>

#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;

long long part1(const vector<string>& input) {
    
    vector<vector<string>> ranges;

    for (auto row : tokenizer(input[0], ',')) {
        ranges.push_back(tokenizer(row, '-'));
    }

    long long invIdSum = 0;
    
    for (auto range : ranges) {
        long long start = stoll(range[0]);
        long long end = stoll(range[1]);
        
        for (long long i = start; i <= end; i++) {
            if (lengthFinder(i) % 2 != 0) {
                continue;
            }
            
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

// Added just for reference, doing later
long long part2(const vector<string>& input) {
    
    vector<vector<string>> ranges;

    for (auto row : tokenizer(input[0], ',')) {
        ranges.push_back(tokenizer(row, '-'));
    }

    long long invIdSum = 0;
    
    for (auto range : ranges) {
        long long start = stoll(range[0]);
        long long end = stoll(range[1]);
        //if (start % 2 != 0 ) start--;
        for (long long i = start; i <= end; i++) {
            if (lengthFinder(i) % 2 != 0) continue;
            
            string x = to_string(i);

            if (x.substr(0, x.length() / 2).compare(x.substr(x.length() / 2)) == 0) {
                invIdSum += i;
                
            } 
            continue;
            
            auto splits = splitNum(i);

            if (splits.first == splits.second) {
                //cout << i << endl;
                //cout << splits.first << " " << splits.second << endl;
                invIdSum += i;
                // Small trick to improve running time
                i += splits.first;
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
