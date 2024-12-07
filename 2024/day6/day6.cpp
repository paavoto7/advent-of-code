#include <string>
#include <array>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <utility>
#include "../utils/helper.h"
#include "../utils/gridPrinter.h"
using namespace std;

/* Today I didn't create a shared function or variables.
   Could come back and do that but this solution even for
   part 2 runs under a second. 
*/


pair<int, int> findGuard(const vector<string> &input, char guard) {
    for (int i = 0; i < input.size(); ++i) {
        auto x = find(input[i].begin(), input[i].end(), guard);
        if (x != input[i].end()) {
            return {distance(input[i].begin(), x), i};
        }
    }
    return {-1, -1}; // Just return incorrect position if fails
}


int part1(vector<string> grid, int currx, int curry) {
    int sum = 0;
    
    int width = grid[0].size();
    int height = grid.size();
    int maxSteps = width * height;

    constexpr int size = 4;
    constexpr array<pair<int, int>, size> directions = {
        {{0, -1}, {1, 0}, {0, 1}, {-1, 0}} // (x, y)
    };
    int currDir = 0;

    int newX, newY;

    while (sum < maxSteps) {
        if (grid[curry][currx] != 'X') {
            sum++;
            grid[curry][currx] = 'X';
        }

        newX = currx + directions[currDir].first;
        newY = curry + directions[currDir].second;

        if (newX < 0 || newX>= width || newY < 0 || newY >= height) {
            break;
        }

        if (grid[newY][newX] == '#') {
            currDir = (currDir + 1) % size;
        } else {
            currx = newX;
            curry = newY;
        }
    }
    // print2DGrid(grid);
    return sum;
}


/* Simple improvement would be to only place the obstacles
   on the path taken in part 1. This solution runs under
   a second so I decided to leave it this way for now.
*/
int part2(vector<string> grid, int currx, int curry) {
    int loops = 0;

    int width = grid[0].size();
    int height = grid.size();
    int maxSteps = width * height;

    constexpr int size = 4;
    constexpr array<pair<int, int>, size> directions = {
        {{0, -1}, {1, 0}, {0, 1}, {-1, 0}} // (x, y)
    };
    
    //int currDir = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Skip if already an obstacle or starting position
            if (grid[i][j] == '#' || (j == currx && i == curry)) continue;

            // Try a new position for the current run
            grid[i][j] = '#';

            int currDir = 0;
            // Just the copies for each iteration
            int currxx = currx, curryy = curry;
            int newX, newY;
            bool completed = true;

            for (int k = 0; k < maxSteps; ++k) {
                
                newX = currxx + directions[currDir].first;
                newY = curryy + directions[currDir].second;

                if (newX < 0 || newX >= width || newY < 0 || newY >= height) {
                    completed = false;
                    break;
                }

                if (grid[newY][newX] == '#') {
                    currDir = (currDir + 1) % size;
                } else {
                    currxx = newX;
                    curryy = newY;
                }
            }
            if (completed) {
                loops++;
            }
            // Doing this instead of copying after every iteration was faster
            grid[i][j] = '.';
        }
    }
    return loops;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day6.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);
    auto [currx, curry] = findGuard(input, '^');

    auto beforeP1 = chrono::high_resolution_clock::now();
    int result1 = part1(input, currx, curry);
    auto afterP1 = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(afterP1 - beforeP1).count();
    cout << "Part 1: " << result1 << " - Time: " << time1 / 1000.0 << "ms" << endl;;

    auto beforeP2 = chrono::high_resolution_clock::now();
    int result2 = part2(input, currx, curry);
    auto afterP2 = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::microseconds>(afterP2 - beforeP2).count();
    cout << "Part 2: " << result2 << " - Time: " << time2 / 1000.0 << "ms" << endl;
}
