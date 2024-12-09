#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../utils/helper.h"
#include "../utils/timer.h"
using namespace std;


long part1(const string& diskMap) {
    long sum = 0;

    vector<int> optiDisk;
    int currID = 0;

    for (int i = 0; i < diskMap.length(); ++i) {
        int toInsert = i % 2 == 0 ? currID++ : -1;
        for (int j = 0; j < (diskMap[i]-'0'); ++j) {
            optiDisk.push_back(toInsert);
        }
    }

    int back = optiDisk.size() - 1;
    const int len = optiDisk.size();
    for (int i = 0; i < len; ++i) {
        if (optiDisk[i] == -1) {
            while (optiDisk[back] == -1) back--;
            if (back <= i) break;

            swap(optiDisk[i], optiDisk[back--]);
            sum += i * optiDisk[i];
        } else {
            sum += i * optiDisk[i];
        }
    }
    return sum;
}


long part2(const string& diskMap) {
    long sum = 0;

    vector<int> optiDisk;
    unordered_map<int, int> idPos;

    int currID = 0;

    for (int i = 0; i < diskMap.length(); ++i) {
        int toInsert = i % 2 == 0 ? currID++ : -1;
        int amount = (diskMap[i]-'0');
        for (int j = 0; j < amount; ++j) {
            optiDisk.push_back(toInsert);
        }
        if (toInsert != -1) {
            idPos[toInsert] = amount;
        }
    }

    int back = optiDisk.size()-1;
    const int len = optiDisk.size();
    
    // Not ideal, but it solves the problem
    for (int i = idPos.size()-1; i > 0; --i) {
        int nums = idPos.at(i);
        while(optiDisk[back] != i) back--;

        for (int j = 0; j < back; ++j) {
            if (optiDisk[j] == -1) {

                int spaces = 0;
                while (optiDisk[j+spaces] == -1) {
                    spaces++;
                }
                if (nums <= spaces) {
                    swap_ranges(optiDisk.begin()+j, optiDisk.begin()+j+nums, optiDisk.begin()+back-nums+1);
                    break;
                }
            }
        }
    }

    for (int n = 0; n < len; ++n) {
        if (optiDisk[n] >= 0){
            sum += n * optiDisk[n];
        }
    }

    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    string input = getOneString(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
