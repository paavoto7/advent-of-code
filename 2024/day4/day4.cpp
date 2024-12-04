#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <chrono>
#include "../utils/helper.h"
using namespace std;


int search(const vector<vector<char>> &grid, int posY, int posX, const array<int, 2> &dir, const string &word = "XMAS") {
    int maxX = grid[posY].size(), maxY = grid.size();
    int curry = posY, currx = posX;

    for (int i = 0; i < word.size(); ++i) {
        
        if (curry >= maxY || curry < 0 || currx >= maxX || currx < 0) {
            return 0;
        }
        if (grid[curry][currx] != word[i]) {
            return 0;
        }
        curry += dir[0];
        currx += dir[1];
    }
    return 1;
}

int part1(const vector<vector<char>> &grid) {
    int wordCount = 0;

    array<array<int, 2>, 8> directions = {{
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}
    }};

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 'X') {
                for (auto direction: directions) {
                    wordCount += search(grid, i, j, direction);
                }
            }
        }
    }
    
    return wordCount;
}


bool isInvalid(char c) {
    return c == 'A' || c == 'X';
}


int search_X(const vector<vector<char>> &grid, int posY, int posX) {
    int dirs[4][2] = {{-1, -1}, {1, 1}, {1, -1}, {-1, 1}};

    for (int i = 0; i < 4; i += 2) {

        int dx1 = posX + dirs[i][0], dy1 = posY + dirs[i][1];
        int dx2 = posX + dirs[i+1][0], dy2 = posY + dirs[i+1][1];

        char first = grid[dy1][dx1];
        char second = grid[dy2][dx2];
        
        if (first == second || isInvalid(first) || isInvalid(second)) {
            return 0;
        }
    }
    return 1;
}

int part2(const vector<vector<char>> &grid) {
    
    int wordCount = 0;

    for (int i = 1; i < grid.size()-1; ++i) {
        for (int j = 1; j < grid[0].size()-1; ++j) {
            if (grid[i][j] == 'A') {
                wordCount += search_X(grid, i, j);
            }
        }
    }

    return wordCount;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../../inputs/day4.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);
    vector<vector<char>> grid = convertTo2DChars(input);

    auto beforeP1 = chrono::high_resolution_clock::now();
    int result1 = part1(grid);
    auto afterP1 = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(afterP1 - beforeP1).count();
    cout << "Part 1: " << result1 << " - Time: " << time1 / 1000.0 << "ms" << endl;;

    auto beforeP2 = chrono::high_resolution_clock::now();
    int result2 = part2(grid);
    auto afterP2 = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::microseconds>(afterP2 - beforeP2).count();
    cout << "Part 2: " << result2 << " - Time: " << time2 / 1000.0 << "ms" << endl;
}