#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include "../utils/helper.h"
#include "../utils/timer.h"
using namespace std;


struct Node {
    int y;
    int x;
    int distance;
    int direction;

    bool operator == (const Node& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator > (const Node& other) const {
        return distance > other.distance;
    }
};

struct HashNode {
    size_t operator()(const Node& n) const {
        return hash<int>{}(n.x) ^ (hash<int>{}(n.y) << 1) * hash<int>{}(n.direction);
    }
};

bool oppositeDir(const pair<int, int>& p1, const pair<int, int>& p2) {
    return p1.first == -p2.first && p1.second == -p2.second;
}

int dijkstra(const vector<string>& maze, int y, int x) {
    Node root{y, x, 0, 0};
    
    priority_queue<Node, vector<Node>, greater<Node>> pqueue;
    pqueue.push(root);

    unordered_map<Node, int, HashNode> distances;
    distances[root] = 0;

    constexpr array<pair<int, int>, 4> dirs = {
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
    };

    while (!pqueue.empty()) {
        const auto node = pqueue.top();
        pqueue.pop();

        if (maze[node.y][node.x] == 'E') {
            return node.distance;
        }

        for (int i = 0; i < dirs.size(); ++i) {
            const auto& dir = dirs[i];
            int first = node.y + dir.second;
            int second = node.x + dir.first;

            if (maze[first][second] == '#' || oppositeDir(dir, dirs[node.direction])) {
                continue;
            }
            
            int newDist = dir != dirs[node.direction] ? 
                            node.distance + 1001 :
                            node.distance + 1;

            const Node newNode{first, second, newDist, i};
            // Works because of the HashNode struct
            if (distances.find(newNode) == distances.end() || distances[newNode] > newNode.distance) {
                distances[newNode] = newNode.distance;
                pqueue.push(newNode);
            }
        }
    }
    return 0;
}

int part1(const vector<string>& input) {
    pair<int, int> start;

    for (int i = 0; i < input.size(); ++i) {
        int x = input[i].find('S');
        if (x != string::npos) {
            start = {x, i};
            break;
        }
    }

    return dijkstra(input, start.second, start.first);
}

// For the part 2 backtracking we don't care about the direction of the node
struct HashNodeNoDir{
    size_t operator()(const Node& n) const {
        return hash<int>{}(n.x) ^ (hash<int>{}(n.y) << 1);
    }
};


int part2(const vector<string>& maze) {
    pair<int, int> start;

    for (int i = 0; i < maze.size(); ++i) {
        int x = maze[i].find('S');
        if (x != string::npos) {
            start = {x, i};
            break;
        }
    }

    unordered_map<Node, vector<Node>, HashNode> nodes;
    Node end;
    
    Node root{start.second, start.first, 0, 0};
    
    priority_queue<Node, vector<Node>, greater<Node>> pqueue;
    pqueue.push(root);

    unordered_map<Node, int, HashNode> distances;
    distances[root] = 0;

    constexpr array<pair<int, int>, 4> dirs = {
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
    };

    while (!pqueue.empty()) {
        const auto node = pqueue.top();
        pqueue.pop();

        if (maze[node.y][node.x] == 'E') {
            end = node;
            break;
        }

        for (int i = 0; i < dirs.size(); ++i) {
            const auto& dir = dirs[i];
            int first = node.y + dir.second;
            int second = node.x + dir.first;

            if (maze[first][second] == '#' || oppositeDir(dir, dirs[node.direction])) {
                continue;
            }
            
            int newDist = dir != dirs[node.direction] ? 
                            node.distance + 1001 :
                            node.distance + 1;

            const Node newNode{first, second, newDist, i};
            // Works because of the HashNode struct
            if (distances.find(newNode) == distances.end() || distances[newNode] > newNode.distance) {
                distances[newNode] = newNode.distance;
                pqueue.push(newNode);
                nodes[newNode].clear();
                nodes[newNode].push_back(node);
            } else if (distances[newNode] == newNode.distance) {
                nodes[newNode].push_back(node);
            }
        }
    }

    queue<Node> q;
    q.push(end);
    unordered_set<pair<int, int>, HashPairs> uniques;

    while (!q.empty()) {
        const auto node = q.front();
        q.pop();

        uniques.insert({node.x, node.y});

        for (const auto& n: nodes[node]) {
            q.push(n);
        }
    }

    return uniques.size();
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
