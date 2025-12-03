#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;


int searchArea(const vector<string>& graph, vector<vector<bool>>& visited, int i, int j) {
    int area = 0;
    int perimeter = 0;
    // Could be a 2D vector or vector of pairs but this seems the fastest
    constexpr int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    constexpr char dirChars[4] = {'>', 'v', '<', '^'};
    const int maxY = graph.size();
    const int maxX = graph[0].size();

    char target = graph[i][j];

    queue<pair<int, int>> nodes;
    nodes.push({i, j});

    while (!nodes.empty()) {
        const auto node = nodes.front();
        nodes.pop();

        char current = graph[node.first][node.second];

        if (current == target) {
            area++;
        } else {
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            int first = node.first + dirs[i][0];
            int second = node.second + dirs[i][1];

            if (!isInBounds(first, second, maxY, maxX) || graph[first][second] != current) {
                perimeter++;
                
                continue;
            }
            if (visited[first][second] == false) {
                nodes.push({first, second});
                visited[first][second] = true;
            }
        }
    }
    return area * perimeter;
}


int part1(const vector<string>& input) {
    int sum = 0;

    vector<vector<bool>> visited(input.size(), vector<bool>(input[0].size(), false));

    for (int i = 0; i < input.size(); ++i) {
        for (int j = 0; j < input[0].size(); ++j) {
            if (visited[i][j] == false) {
                visited[i][j] = true;
                sum += searchArea(input, visited, i, j);
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
