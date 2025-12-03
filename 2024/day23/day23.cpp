#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <sstream>
#include "../../utils/helper.h"
#include "../../utils/timer.h"
#include "../../utils/gridPrinter.h"

using namespace std;
using namespace utils;


int hashConns(string a, string b, string c) {
    return hash<string>{}(a) ^ hash<string>{}(b) ^ hash<string>{}(c);
}


int part1(const vector<string>& input) {
    int sum = 0;
    unordered_map<string, unordered_set<string>> connections;
    unordered_set<int> pools;

    for (const auto& line: input) {
        const auto computers = tokenizer(line, '-');
        connections[computers[0]].insert(computers[1]);
        connections[computers[1]].insert(computers[0]);
    }
    
    for (auto const& [comp, comps]: connections) {
        const vector<string> conns(comps.begin(), comps.end());

        const bool first = comp[0] == 't';
        for (int i = 0; i < conns.size(); ++i) {
            bool second = conns[i][0] == 't';
            for (int j = i+1; j < conns.size(); ++j) {
                
                if ((first || second || conns[j][0] == 't') &&
                    connections.at(conns[i]).count(conns[j]) &&
                    pools.insert(hashConns(comp, conns[i], conns[j])).second)
                {
                    sum++;
                }
            }
        }
    }
    return sum;
}


unordered_set<string> intersection(const unordered_set<string>& a, const unordered_set<string>& b) {
    unordered_set<string> result;
    for (const auto& v: a) {
        if (b.count(v)) {
            result.insert(v);
        }
    }
    return result;
}

// https://en.wikipedia.org/wiki/Bron-Kerbosch_algorithm#Without_pivoting
void bronKerbosch(set<string>& R, unordered_set<string> P, unordered_set<string> X, const unordered_map<string, unordered_set<string>>& graph, string& l) {
    if (P.empty() && X.empty()) {
        // R size + second letters + amount of commas
        if (l.length() < R.size()*3) {
            stringstream ss;
            for (const auto& v: R) {
                ss << v << ',';
            }
            l = ss.str();
        }
        return;
    }
    const auto tempP = P;
    for (const auto& v: tempP) {
        const auto& neighbours = graph.at(v);
        R.insert(v);
        bronKerbosch(R, intersection(P, neighbours), intersection(X, neighbours), graph, l);

        P.erase(v);
        X.insert(v);
        R.erase(v);
    }
}


/* Bron-Kerbosch algorithm works very well here, but
   it possibly is a bit of an overkill. Apparently
   brute-forcy recursions work as well and many times
   faster even. This was nonetheless a nice way to learn
   about a new algorithm and get a chance to implement it.
*/
string part2(const vector<string>& input) {
    int sum = 0;
    unordered_map<string, unordered_set<string>> connections;
    unordered_set<string> X, P;
    set<string> R;

    // Ugly, but does the job
    for (const auto& line: input) {
        const auto computers = tokenizer(line, '-');
        connections[computers[0]].insert(computers[1]);
        connections[computers[1]].insert(computers[0]);
        P.insert(computers[0]);
        P.insert(computers[1]);
    }

    string l = "";
    bronKerbosch(R, P, X, connections, l);
    l.pop_back();
    return l;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day23.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
