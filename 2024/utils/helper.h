
#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

std::vector<std::string> getStringInput(std::string fileLocation);

std::vector<std::string> tokenizer(const std::string & original, char delimiter = ' ');

/* Simply calculates the dot product of two vectors */
int dotProduct(std::vector<int> vector1, std::vector<int> vector2);

#endif
