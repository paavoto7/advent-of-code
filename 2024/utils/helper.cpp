#include "helper.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<std::string> getStringInput(std::string fileLocation) {
    std::ifstream Input(fileLocation);

    std::string line;
    
    std::vector<std::string> output;

    while (getline(Input, line)) {
        output.push_back(line);
    }

    Input.close();

    return output;
}

std::vector<std::string> tokenizer(const std::string & original, char delimiter) {
    std::stringstream ss(original);
    std::vector<std::string> tokens;
    
    std::string token;

    while (getline(ss, token, delimiter)) {
        // Makes sure no whitespace is added
        if (token.find_first_not_of(' ') != std::string::npos) {
            tokens.push_back(token);
        }
        
    }

    return tokens;
}

/* Simply calculates the dot product of two vectors */
int dotProduct(std::vector<int> vector1, std::vector<int> vector2) {

    if (vector1.size() != vector2.size()) {
        throw std::invalid_argument("Vectors are not the same length");
    }

    int sum = 0;

    for (int i = 0; i < vector1.size(); ++i) {
        sum += vector1[i]*vector2[i];
    }
    
    return sum;
}