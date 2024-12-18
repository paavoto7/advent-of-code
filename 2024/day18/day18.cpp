#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "../utils/helper.h"
#include "../utils/timer.h"
#include "../utils/gridPrinter.h"
using namespace std;


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

// Not a weighted graph, but Dijkstra works perfectly and it fast enough
int dijkstra(const vector<vector<bool>>& memory, int y, int x, int max) {
    const int maxY = memory.size();
    const int maxX = memory[0].size();

    const Coordinate root{0, 0, 0};

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

        if (node.y == max && node.x == max) {
            return node.distance;
        }

        for (const auto& dir: dirs) {
            const int newY = node.y + dir.second;
            const int newX = node.x + dir.first;

            if (!isInBounds(newY, newX, maxY, maxX) || memory[newY][newX] == true) {
                continue;
            }

            const Coordinate newNode{newY, newX, node.distance+1};
            // Works because of the HashNode struct
            if (distances.find(newNode) == distances.end() || newNode.distance < distances[newNode]) {
                distances[newNode] = newNode.distance;
                pqueue.push(newNode);
            }
        }
    }
    return -1;
}


int part1(const vector<string>& input) {
    const int dimensions = 71;
    const int bytesToSimulate = 1024;
    vector<vector<bool>> bytes(dimensions, vector<bool>(dimensions, false));
    // (x, y)
    vector<pair<int, int>> falling;

    for (const auto& line: input) {
        //int comma = line.find(',');
        const auto& coords = tokenizerToInt(line, ',');
        falling.push_back({coords[0], coords[1]});
    }

    for (int i = 0; i < bytesToSimulate; ++i) {
        const auto& [x, y] = falling[i];
        bytes[y][x] = true;
    }

    return dijkstra(bytes, 0, 0, dimensions-1);
}


/* Just plain and simple brute force solution.
    It is very fast for my input at least when doing it backwards.
    Binary search would be a better option, but I solved it
    with this one already so it I'll leave it as is.
*/
string part2(const vector<string>& input) {
    const int dimensions = 71;
    int bytesToSimulate = 1024;
    vector<vector<bool>> bytes(dimensions, vector<bool>(dimensions, false));
    // (x, y)
    vector<pair<int, int>> falling;

    for (const auto& line: input) {
        //int comma = line.find(',');
        const auto& coords = tokenizerToInt(line, ',');
        falling.push_back({coords[0], coords[1]});
    }

    for (const auto& [x, y]: falling) {
        bytes[y][x] = true;
    }

    int pathFound = -1;
    int max = falling.size()-1;
    while (pathFound == -1 && max > bytesToSimulate) {
        max--;
        const auto& [x, y] = falling[max];
        bytes[y][x] = false;
        pathFound = dijkstra(bytes, 0, 0, dimensions-1);
    }

    //print2DGrid(bytes);
    const auto& p = falling[max];
    return to_string(p.first) + ',' + to_string(p.second);
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
