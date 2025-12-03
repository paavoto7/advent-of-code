#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;


bool moveBoxes(vector<string>& warehouse, int x, int y, const pair<int, int>& dir) {
    if (warehouse[y][x] == '#') {
        return false;
    } else {
        if (warehouse[y][x] == 'O') {
            return moveBoxes(warehouse, x+dir.first, y+dir.second, dir);
        } else {
            warehouse[y][x] = 'O';
            return true;
        }
    }
}


int part1(const vector<string>& input) {
    int sum = 0;
    vector<string> warehouse;
    string sequence;
    pair<int, int> robot;
    const unordered_map<char, pair<int, int>> directions{
        {'^', {0, -1}},
        {'v', {0, 1}},
        {'<', {-1, 0}},
        {'>', {1, 0}}
    };

    for (int i = 0; i < input.size(); ++i) {
        int pos = input[i].find('@');
        if (pos != string::npos) {
            robot = {i, pos};
        }
        if (input[i].find_first_not_of(' ') == string::npos) {
            warehouse = {input.begin(), input.begin()+i};
            for (int j = i; j < input.size(); ++j) {
                sequence += input[j];
            }
            break;
        }
    }

    const int maxY = warehouse.size();
    const int maxX = warehouse[0].size();
    //print2DGrid(warehouse);

    for (const char& cmd: sequence) {
        const auto& direction = directions.at(cmd);
        int nextY = robot.first+direction.second;
        int nextX = robot.second+direction.first;

        char& next = warehouse[nextY][nextX];
        char& current = warehouse[robot.first][robot.second];

        if (next == '#') {
            continue;
        } else if (next == '.') {
            next = '@';
            current = '.';
        } else if (next == 'O') {
            if (moveBoxes(warehouse, nextX, nextY, direction)) {
                warehouse[nextY][nextX] = '@';
                current = '.';
            } else {
                continue;
            }
        }
        robot.first += direction.second;
        robot.second += direction.first;
    }

    for (int i = 1; i < maxY-1; ++i) {
        for (int j = 1; j < maxX-1; ++j) {
            if (warehouse[i][j] == 'O') {
                sum += i * 100 + j;
            }
        }
    }

    return sum;
}


int part2(const vector<string>& input) {
    int sum = 0;

    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
