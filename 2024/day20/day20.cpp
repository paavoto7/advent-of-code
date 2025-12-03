#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <utility>
#include <unordered_map>
#include <cmath>
#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;

struct Coordinate {
    int y;
    int x;
    int distance;

    bool operator == (const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator > (const Coordinate& other) const {
        return distance > other.distance;
    }
};

struct HashNode {
    size_t operator()(const Coordinate& n) const {
        return hash<int>{}(n.x) ^ (hash<int>{}(n.y) << 1);
    }
};


unordered_map<Coordinate, int, HashNode> dijkstra(const vector<string>& memory, int y, int x, const pair<int, int>& end) {
    const int maxY = memory.size();
    const int maxX = memory[0].size();

    const Coordinate root{y, x, 0};

    priority_queue<Coordinate, vector<Coordinate>, greater<Coordinate>> pqueue;
    pqueue.push(root);

    unordered_map<Coordinate, int, HashNode> distances;
    distances[root] = 0;

    constexpr array<pair<int, int>, 4> dirs = {
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
    };

    while (!pqueue.empty()) {
        const auto node = pqueue.top();
        pqueue.pop();

        if (node.y == end.first && node.x == end.second) {
            return distances;
        }

        for (const auto& dir: dirs) {
            const int newY = node.y + dir.second;
            const int newX = node.x + dir.first;
            
            if (!isInBounds(newY, newX, maxY, maxX) || memory[newY][newX] == '#') continue;

            const Coordinate newNode{newY, newX, node.distance+1};

            if (distances.find(newNode) == distances.end() || newNode.distance < distances[newNode]) {
                distances[newNode] = newNode.distance;
                pqueue.push(newNode);
            }
        }
    }
    return distances;
}


int part1(const vector<string>& input) {
    int cheats = 0;
    pair<int, int> start;
    pair<int, int> end;

    constexpr array<pair<int, int>, 4> dirs = {
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
    };

    for (int i = 0; i < input.size(); ++i) {
        const auto& line = input[i];
        int startInd = line.find('S');
        int endInd = line.find('E');
        if (startInd != string::npos) {
            start = {i, startInd};
        }
        if (endInd != string::npos) {
            end = {i, endInd};
        }
    }

    const auto distances = dijkstra(input, start.first, start.second, end);
    const int maxY = input.size();
    const int maxX = input[0].size();

    for (int i = 1; i < maxY-1; ++i) {
        for (int j = 1; j < maxX-1; ++j) {
            if (input[i][j] == '#') continue;

            const Coordinate node{i, j};
            const int distance = distances.at(node);

            for (const auto& dir: dirs) {
                const int newY = node.y + dir.second*2;
                const int newX = node.x + dir.first*2;

                if (isInBounds(newY, newX, maxY, maxX) &&
                    input[newY][newX] != '#' &&
                    distances.at({newY, newX}) - distance > 100)
                {
                    cheats++;
                }
            }
        }
    }
    return cheats;
}


int manhattan(const Coordinate& a, const Coordinate& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}


int part2(const vector<string>& input) {
    int cheats = 0;
    pair<int, int> start;
    pair<int, int> end;

    for (int i = 0; i < input.size(); ++i) {
        const auto& line = input[i];
        int startInd = line.find('S');
        int endInd = line.find('E');
        if (startInd != string::npos) {
            start = {i, startInd};
        }
        if (endInd != string::npos) {
            end = {i, endInd};
        }
    }

    const auto distances = dijkstra(input, start.first, start.second, end);
    const int maxY = input.size();
    const int maxX = input[0].size();
    const int shortcutLen = 20;

    for (int i = 1; i < maxY-1; ++i) {
        for (int j = 1; j < maxX-1; ++j) {
            if (input[i][j] == '#') continue;

            const Coordinate node{i, j};
            const int distance = distances.at(node);

            for (int k = -shortcutLen; k <= shortcutLen; ++k) {
                int inner = shortcutLen - abs(k);
                for (int n = -inner; n <= inner; ++n) {
                    const int newY = node.y + n;
                    const int newX = node.x + k;

                    if (isInBounds(newY, newX, maxY, maxX) &&
                        input[newY][newX] != '#')
                    {
                        const Coordinate newCoord{newY, newX};
                        if (distances.at(newCoord) - distance - manhattan(newCoord, node) >= 100) {
                            cheats++;
                        }
                    }
                }
            }
        }
    }
    return cheats;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day19.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
