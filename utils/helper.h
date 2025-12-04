
#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <iostream>

namespace utils {

std::vector<std::string> getStringInput(std::string fileLocation);

std::string getOneString(std::string fileLocation);

std::vector<std::vector<char>> convertTo2DChars(const std::vector<std::string> &inp);

std::vector<std::string> tokenizer(const std::string & original, char delimiter = ' ');

std::vector<int> tokenizerToInt(const std::string& original, char delimiter);

std::vector<long long> tokenizerToLongLong(const std::string& original, char delimiter);

std::vector<int> stringVecToIntVec(std::vector<std::string> original);

std::vector<int> stringToIntVec(std::string original);

std::vector<std::vector<int>> stringVecTo2DIntVec(const std::vector<std::string> &original, char delimiter = ' ');

struct HashPairs {
    template <typename T, typename I>
    std::size_t operator()(const std::pair<T, I>& p) const {
        return std::hash<T>{}(p.first) ^ (std::hash<I>{}(p.second) << 1);
    }
};

inline bool isInBounds(int y, int x, int maxY, int maxX) {
    return y >= 0 && x >= 0 && y < maxY && x < maxX;
}

inline bool isInBounds(int y, int x, size_t maxY, size_t maxX) {
    return y >= 0 && x >= 0 && static_cast<size_t>(y) < maxY && static_cast<size_t>(x) < maxX;
}

/* Simply calculates the dot product of two vectors */
int dotProduct(const std::vector<int> &vector1, const std::vector<int> &vector2);

struct dividedPair {
    long long first;
    long long second;
};

dividedPair splitNum(long long a);

int lengthFinder(long long n);
}

#endif
