#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
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
            for (int k = 0; k < 4; ++k) {
                pair<int, int> next = {node.first + dirs[k][0], node.second + dirs[k][1]};
                if (isInBounds(next.first, next.second, maxY, maxX) &&
                    topograph[next.first][next.second] == current+1 &&
                    (ignoreVisited || !visited.count(next)))
                {
                    nodes.push(next);
                    visited.insert(next);
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
