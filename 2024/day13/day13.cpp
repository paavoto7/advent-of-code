#include <string>
#include <iostream>
#include <vector>
#include "../utils/helper.h"
#include "../utils/timer.h"
using namespace std;


void inverse(vector<vector<double>>& matrix) {
    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[1][0];
    double d = matrix[1][1];

    double determinant = a*d - b*c;

    matrix[0][0] = d / determinant;
    matrix[0][1] = (-b) / determinant;
    matrix[1][0] = (-c) / determinant;
    matrix[1][1] = a / determinant;
}


bool verify(const vector<vector<double>>& matrix, int buttonA, int buttonB, int ind) {
    return buttonA*matrix[ind][0] + buttonB*matrix[ind+1][0] == matrix[ind+2][0] &&
        buttonA*matrix[ind][1] + buttonB*matrix[ind+1][1] == matrix[ind+2][1];
}


int part1(const vector<string>& input) {
    int sum = 0;

    vector<vector<double>> matrixes;
    
    for (const string& line: input) {
        if (line.find_first_not_of(' ') == string::npos) continue;
        int colon = line.find(':');
        vector<string> tokens = tokenizer(line.substr(colon+1), ',');
        // A bit hardcoded but easy to convert to a more dynamic one
        vector<double> ints{stod(tokens[0].substr(3)), stod(tokens[1].substr(3))};
        matrixes.push_back(ints);
    }

    for (int i = 0; i < matrixes.size(); i+=3) {
        // Creating a new 2x2 matrix just simplifies the logic and the cost is minimal too
        vector<vector<double>> vec{matrixes[i], matrixes[i+1]};
        inverse(vec);

        int buttonA = 0, buttonB = 0;
        for (int j = 0; j < 2; j++) {
            buttonA += (int)(vec[j][0] * matrixes[i+2][j]);
            buttonB += (int)(vec[j][1] * matrixes[i+2][j]);
        }

        if (verify(matrixes, buttonA, buttonB, i)) {
            sum += 3*buttonA+buttonB;
        }
    }
    return sum;
}


// Quite literally the same as part1,
// but we just add the 10000000000000 to the targets
long long part2(const vector<string>& input) {
    long long sum = 0;

    vector<vector<double>> matrixes;

    for (const string& line: input) {
        if (line.find_first_not_of(' ') == string::npos) continue;
        int colon = line.find(':');
        vector<string> tokens = tokenizer(line.substr(colon+1), ',');
        vector<double> ints{stod(tokens[0].substr(3)), stod(tokens[1].substr(3))};
        matrixes.push_back(ints);
    }

    for (int i = 0; i < matrixes.size(); i+=3) {
        vector<vector<double>> vec{matrixes[i], matrixes[i+1]};
        inverse(vec);
        
        long long buttonA = 0;
        long long buttonB = 0;
        for (int j = 0; j < 2; j++) {
            buttonA += (long long)(vec[j][0] * (matrixes[i+2][j] + 10000000000000));
            buttonB += (long long)(vec[j][1] * (matrixes[i+2][j] + 10000000000000));
        }

        // This is now here due to it being simple to just add the trillion to target
        if (buttonA*matrixes[i][0] + buttonB*matrixes[i+1][0] == (matrixes[i+2][0] + 10000000000000)&&
        buttonA*matrixes[i][1] + buttonB*matrixes[i+1][1] == (matrixes[i+2][1] + 10000000000000)) {
            sum += 3 * buttonA + buttonB;
        }
    }
    return sum;
}


int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day9.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
