

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>

template <typename T, typename Function>
void timer(Function func, const T& input, std::string text) {
    auto beforeP = std::chrono::high_resolution_clock::now();
    auto result = func(input);
    auto afterP = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(afterP - beforeP).count();
    std::cout << text << result << " - Time: " << time / 1000.0 << "ms" << std::endl;;
}

#endif