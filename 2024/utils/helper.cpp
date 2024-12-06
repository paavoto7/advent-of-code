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

std::string getOneString(std::string fileLocation) {
    std::ifstream Input(fileLocation);

    std::string line;
    std::stringstream ss;

    while (getline(Input, line)) {
        ss << line;
    }

    Input.close();

    return ss.str();
}

std::vector<std::vector<char>> convertTo2DChars(const std::vector<std::string> &inp) {
    std::vector<std::vector<char>> grid;
    for (int i = 0; i < inp.size(); ++i) {
        std::vector<char> line(inp[i].begin(), inp[i].end());
        grid.push_back(line);
    }
    return grid;
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

std::vector<int> stringVecToIntVec(std::vector<std::string> original) {
    std::vector<int> newVect;

    for(std::string element: original) {
        newVect.push_back(std::stoi(element));
    }
    return newVect;
}

std::vector<int> stringToIntVec(std::string original) {
    std::vector<int> newVect;

    for(int i = 0; i < original.length(); ++i) {
        newVect.push_back((int) (original[i] - '0')); // Converts the char int to int
    }
    return newVect;
}


std::vector<std::vector<int>> stringVecTo2DIntVec(const std::vector<std::string> &original, char delimiter) {
    std::vector<std::vector<int>> newVect;
    for (std::string line: original) {
        std::stringstream ss(line);
        std::vector<int> intvect;
        std::string temp;
        while (std::getline(ss, temp, ',')) {
            intvect.push_back(stoi(temp));
        }
        if (intvect.size() > 0) {
            newVect.push_back(intvect);
        }
    }
    return newVect;
}


/* Simply calculates the dot product of two vectors */
int dotProduct(const std::vector<int> &vector1, const std::vector<int> &vector2) {

    if (vector1.size() != vector2.size()) {
        throw std::invalid_argument("Vectors are not the same length");
    }

    int sum = 0;

    for (int i = 0; i < vector1.size(); ++i) {
        sum += vector1[i]*vector2[i];
    }
    
    return sum;
}