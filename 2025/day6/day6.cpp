#include <vector>
#include <string>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

// Documentation and reasoning coming later

long part1(const vector<string>& input) {
    vector<vector<int>> values;
    for (size_t i = 0; i < input.size() - 1; ++i) {
        values.push_back(
            tokenizerToInt(input[i], ' ')
        );
    }
    
    vector<string> operations = tokenizer(input.back(), ' ');

    auto sum = [](long tot, int n) { return tot + n; };
    auto prod = [](long tot, int n) { return tot * n; };
    
    long totalSum = 0;

    const auto width = operations.size();
    const auto height = values.size();
    for (size_t i = 0; i < width; ++i) {

        long interSum = values[0][i];
        auto op = operations[i] == "+" ? sum : prod;
        
        for (size_t j = 1; j < height; ++j) {
            interSum = op(interSum, values[j][i]);
        }
        totalSum += interSum;
    }
    
    return totalSum;
}

long part2(const vector<string>& input) {
    enum class Op { sum, prod };

    Op op = Op::sum;

    long totalSum = 0;
    long interSum = 0;
    
    const auto& operations = input.back();

    const auto width = operations.size();
    const auto height = input.size() - 1;
    for (size_t i = 0; i < width; ++i) {

        char operation = operations[i];
        // If a new +/* is found, the next sef of columns starts
        if (operation != ' ') {
            totalSum += interSum;
            if (operation == '+') {
                op = Op::sum;
                interSum = 0;
            } else {
                op = Op::prod;
                interSum = 1; // To correctly multiply
            }
        }

        long inter = 0;
        // Loop over each digit in column
        for (size_t j = 0; j < height; ++j) {
            char val = input[j][i];
            
            if (val == ' ') continue;
            inter = inter * 10 + (val - '0');
            
        }
        
        if (op == Op::sum) {
            interSum += inter;
        } else if (inter != 0) { // No column results in 0
            interSum *= inter;
        }
    }

    totalSum += interSum;
    
    return totalSum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
