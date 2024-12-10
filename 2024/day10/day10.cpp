#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <array>
#include <utility>
#include "../utils/helper.h"
#include "../utils/timer.h"
using namespace std;


/* A pretty standard BFS that finds all valid paths.
   It doesn't end without queue being empty and has a few conditions
   besides the regular basecase and whether a node has been visited.

   Only difference between first and second part is the use
   of the ignoreVisited variable.
*/
int searchPath(const vector<string>& topograph, int i, int j, const char target = '9', bool ignoreVisited = false) {
    int paths = 0;
    // Could be a 2D vector or vector of pairs but this seems the fastest
    constexpr int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    const int maxY = topograph.size();
    const int maxX = topograph[0].size();

    queue<pair<int, int>> nodes;
    nodes.push({i, j});

    unordered_set<pair<int, int>, HashPairs> visited;
    visited.insert({i, j});

    while (!nodes.empty()) {
        const auto node = nodes.front();
        nodes.pop();

        char current = topograph[node.first][node.second];

        if (current == target) {
            paths++;
        } else {
            // Some optimisations, result is better time but less clean code
            for (const auto& [y, x]: dirs) {
                int first = node.first + y;
                int second = node.second + x;

                if (isInBounds(first, second, maxY, maxX) &&
                    topograph[first][second] == current+1)
                {
                    const pair<int, int> next = {first, second};
                    if (!ignoreVisited && visited.insert(next).second) {
                        nodes.push(next);
                    } else if (ignoreVisited) {
                        nodes.push(next);
                    }
                }
            }
        }
    }
    return paths;
}


int part1(const vector<string>& topograph) {
    int sum = 0;
    for (int i = 0; i < topograph.size(); ++i) {
        for (int j = 0; j < topograph[0].length(); ++j) {
            if (topograph[i][j] == '0') {
                sum += searchPath(topograph, i, j);
            }
        }
    }
    return sum;
}


int part2(const vector<string>& topograph) {
    int sum = 0;

    for (int i = 0; i < topograph.size(); ++i) {
        for (int j = 0; j < topograph[0].length(); ++j) {
            if (topograph[i][j] == '0') {
                sum += searchPath(topograph, i, j, '9', true);
            }
        }
    }

    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
