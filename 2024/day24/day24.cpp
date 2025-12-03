#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <queue>
#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;


struct Gate {
    string op1;
    string command;
    string op2;
    string out;
};


uint64_t part1(const vector<string>& input) {
    map<string, int> wires;
    queue<Gate> gates;

    for (const string& line: input) {
        if (line.length() == 6) {
            int ind = line.find(':');
            wires[line.substr(0, ind)] = line[ind+2] - '0';
        } else if (line.find_first_not_of(' ') != string::npos) {
            const auto gate = tokenizer(line, ' ');
            gates.push({gate[0], gate[1], gate[2], gate[4]});
        }
    }

    while (!gates.empty()) {
        const Gate gate = gates.front();
        gates.pop();
        
        if (!wires.count(gate.op1) || !wires.count(gate.op2)) {
            gates.push(gate);
            continue;
        }
        
        if (gate.command == "AND") {
            wires[gate.out] = wires[gate.op1] && wires[gate.op2];
        } else if (gate.command == "OR") {
            wires[gate.out] = wires[gate.op1] || wires[gate.op2];
        } else { // XOR
            wires[gate.out] = wires[gate.op1] != wires[gate.op2];
        }
    }

    stringstream bits;
    for (const auto& [wire, value]: wires) {
        if (wire[0] == 'z') {
            bits << value;
        }
    }

    string out = bits.str();
    reverse(out.begin(), out.end()); // Faster than own method

    return stoull(out, 0, 2);;
}


int part2(const vector<string>& input) {
    return 0;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day24.txt";

    const vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
