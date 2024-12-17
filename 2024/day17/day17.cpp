#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <array>
#include <cstdint>
#include "../utils/helper.h"
#include "../utils/timer.h"
using namespace std;


int combos(const array<int, 3>& registers, int operand) {
    if (operand <= 3) {
        return operand;
    } else if (operand <= 6) {
        return registers[operand-4];
    } else {
        return -1;
    }
}


string CPU(const vector<int>& program, array<int, 3> registers) {
    stringstream out;
    for (int j = 0; j < program.size(); j+=2) {
        int operand = program[j+1];
        switch (program[j]) {
        case 0:
            registers[0] = (int)(registers[0] / pow(2, combos(registers, operand)));
            break;
        case 1:
            registers[1] = registers[1] ^ operand;
            break;
        case 2:
            registers[1] = (int)combos(registers, operand) % 8;
            break;
        case 3:
            if (registers[0] == 0) continue;
            j = operand-2;
            break;
        case 4:
            registers[1] = registers[1] ^ registers[2];
            break;
        case 5:
            out << combos(registers, operand) % 8 << ',';
            break;
        case 6:
            registers[1] = (int)(registers[0] / pow(2, combos(registers, operand)));
            break;
        case 7:
            registers[2] = (int)(registers[0] / pow(2, combos(registers, operand)));
            break;
        default:
            break;
        }
    }
    return out.str();
}


int part1(const vector<string>& input) {
    array<int, 3> registers;
    vector<int> program;

    for (int i = 0; i < input.size(); ++i) {
        const string& line = input[i];
        if (line.find_first_not_of(' ') != string::npos) {
            int ind = line.find(':') + 2;
            registers[i] = stoi(line.substr(ind));
        } else {
            int ind = input[i+1].find(':') + 2;
            program = tokenizerToInt(input[i+1].substr(ind), ',');
            break;
        }
    }

    cout << CPU(program, registers) << endl;
    
    return 0;
}

int part2(const vector<string>& input) {
    return 0;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
