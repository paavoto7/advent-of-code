
#ifndef GRIDPRINTER_H
#define GRIDPRINTER_H

#include <vector>
#include <iostream>

template <typename T>
void print2DGrid(const std::vector<std::vector<T>> &grid) {
    for (const auto &line: grid) {
        for (const auto &c: line) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

void print2DGrid(const std::vector<std::string> &grid) {
    for (const auto &line: grid) {
        for (const auto &c: line) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

#endif