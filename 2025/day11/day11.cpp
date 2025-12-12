#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

// Very simple and naive dfs without memoization
// Works well as the search space for the first part is small
int Search(const unordered_map<string, vector<string>>& graph,
           const string& start = "you", const string& target = "out"
    ) {
    stack<string> s;
    s.push(start);

    int outCounter = 0;
    while (!s.empty()) {
        auto node = s.top();
        s.pop();

        if (node == target) {
            outCounter++;
            continue;
        }
        
        for (auto& neighbour: graph.at(node)) {
            s.push(neighbour);
        }
    }

    return outCounter;
}

int part1(const vector<string>& input) {
    unordered_map<string, vector<string>> graph;

    for (auto& line: input) {
        auto nodes = tokenizer(line, ' ');

        graph.try_emplace(nodes[0].substr(0, 3), nodes.begin() + 1, nodes.end());
    }
    
    return Search(graph);
}

int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    //timer(part2, input, "Part 2: ");
}
