

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void timer(std::function<int(std::vector<std::string>)> func, const T& input, std::string text) {
    auto beforeP = std::chrono::high_resolution_clock::now();
    int result = func(input);
    auto afterP = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(afterP - beforeP).count();
    std::cout << text << result << " - Time: " << time / 1000.0 << "ms" << std::endl;;
}

#endif