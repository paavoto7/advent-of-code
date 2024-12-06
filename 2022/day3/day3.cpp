#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include "../../2024/utils/helper.h"
#include "../../2024/utils/gridPrinter.h"
using namespace std;


int part1(const vector<string>& input) {
    int sum = 0;
    
    for (const string& line: input) {
        int middle = line.length() / 2;
        string first = line.substr(0, middle);
        string second = line.substr(middle);

        for (char c: first) {
            if (second.find(c) != string::npos) {
                if (islower(c)) {
                    sum += c - 'a' + 1;
                } else {
                    sum += c - 38;
                }
                break;
            }
        }
    }

    return sum;
}


int part2(const vector<string>& input) {
    int sum = 0;
    
    for (int i = 0; i < input.size(); i += 3) {
        
        // Using string_view here seems to perform a bit worse
        const string& first = input[i];
        const string& second = input[i+1];
        const string& third = input[i+2];

        for (char c: input[i]) {
            if (second.find(c) != string::npos && third.find(c) != string::npos) {
                if (islower(c)) {
                    sum += c - 'a' + 1;
                } else {
                    sum += c - 38;
                }
                break;
            }
        }
    }

    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "./inputs/day3.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    auto beforeP1 = chrono::high_resolution_clock::now();
    int result1 = part1(input);
    auto afterP1 = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::microseconds>(afterP1 - beforeP1).count();
    cout << "Part 1: " << result1 << " - Time: " << time1 / 1000.0 << "ms" << endl;;

    auto beforeP2 = chrono::high_resolution_clock::now();
    int result2 = part2(input);
    auto afterP2 = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::microseconds>(afterP2 - beforeP2).count();
    cout << "Part 2: " << result2 << " - Time: " << time2 / 1000.0 << "ms" << endl;
}

