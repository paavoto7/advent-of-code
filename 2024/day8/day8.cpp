#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>
#include "../utils/helper.h"
#include "../utils/gridPrinter.h"
#include "../utils/timer.h"
using namespace std;


unordered_map<char, vector<pair<int, int>>> signals(const vector<string>& grid) {
    unordered_map<char, vector<pair<int, int>>> output;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] != '.') {
                output[grid[i][j]].push_back({i, j});
            }
        }
    }
    return output;
}


bool isInBounds(int a, int b, int maxY, int maxX) {
    return a >= 0 && b >= 0 && a < maxY && b < maxX;
}

// Time complexity is quite bad but the input is small and this is very fast stil
int part1(const vector<string>& grid) {
    const unordered_map<char, vector<pair<int, int>>> transmitters = signals(grid);
    set<pair<int, int>> coordinates;

    const int maxY = grid.size();
    const int maxX = grid[0].size();

    for (const auto& [key, values]: transmitters) {
        for (const auto& pair1: values) {
            for (const auto& pair2: values) {
                if (pair1 == pair2) continue;
                int y = 2 * pair1.first - pair2.first;
                int x = 2 * pair1.second - pair2.second;
                
                if (isInBounds(y, x, maxY, maxX)) {
                    coordinates.insert({y, x});
                }
            }
        }
    }

    /*
    vector<string> newgrid = grid;
    for (auto pair: coordinates) {
        newgrid[pair.first][pair.second] = '#';
    }
    print2DGrid(newgrid);
    */
    
    return coordinates.size();
}


int part2(const vector<string>& grid) {
    int sum = 0;
    const unordered_map<char, vector<pair<int, int>>> transmitters = signals(grid);
    set<pair<int, int>> coordinates;

    const int maxY = grid.size();
    const int maxX = grid[0].size();

    for (const auto& [key, values]: transmitters) {
        sum += values.size();
        for (const auto& pair1: values) {
            for (const auto& pair2: values) {
                if (pair1 == pair2) continue;
                
                int y = pair1.first - pair2.first;
                int x = pair1.second - pair2.second;
                int newY = pair1.first + y, newX = pair1.second + x;

                while (isInBounds(newY, newX, maxY, maxX)) {
                    if (grid[newY][newX] == '.' && coordinates.insert({newY, newX}).second) {
                        sum++;
                    }
                    newY += y;
                    newX += x;
                }
            }
        }
    }
    
    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day6.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
