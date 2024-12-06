
#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

std::vector<std::string> getStringInput(std::string fileLocation);

std::string getOneString(std::string fileLocation);

std::vector<std::vector<char>> convertTo2DChars(std::vector<std::string> inp);

std::vector<std::string> tokenizer(const std::string & original, char delimiter = ' ');

std::vector<int> stringVecToIntVec(std::vector<std::string> original);

std::vector<int> stringToIntVec(std::string original);

std::vector<std::vector<int>> stringVecTo2DIntVec(const std::vector<std::string> &original, char delimiter = ' ');

/* Simply calculates the dot product of two vectors */
int dotProduct(std::vector<int> vector1, std::vector<int> vector2);

#endif