#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "../../2024/utils/helper.h"
#include "../../2024/utils/gridPrinter.h"
using namespace std;


int part1(const vector<string> &input) {
    int most = 0;
    int accum = 0;
    for (const string &line: input) {
        
        if (line.find_first_not_of(' ') != string::npos) {
            accum += stoi(line);
        } else {
            if (accum > most) most = accum;
            accum = 0;
        }
    }
    return most > accum ? most : accum;
}


void setInt(int &a, int &b, int &c, int accum) {
    if (accum > a) {
        c = b;
        b = a;
        a = accum;
    } else if (accum > b) {
        c = b;
        b = accum;
    } else if (accum > c) {
        c = accum;
    }
}

/* I decided to go this one as it is on my machine 2x fast
*/
int part2(const vector<string> &input) {
    int accum = 0;
    int first = 0, second = 0, third = 0;
    for (const string &line: input) {
        
        if (line.find_first_not_of(' ') != string::npos) {
            accum += stoi(line);
        } else {
            setInt(first, second, third, accum);
            accum = 0;
        }
    }
    setInt(first, second, third, accum);
    return first + second + third;
}


/* This approach is safer and more readable, but slower.
*/
int part22(const vector<string> &input) {
    int accum = 0;
    int first = 0, second = 0, third = 0;
    vector<int> sums;
    for (const string &line: input) {
        
        if (line.find_first_not_of(' ') != string::npos) {
            accum += stoi(line);
        } else {
            sums.push_back(accum);
            accum = 0;
        }
    }
    sums.push_back(accum);
    sort(sums.begin(), sums.end(), greater<>());
    return sums[0] + sums[1] + sums[2];
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day6.txt";

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

