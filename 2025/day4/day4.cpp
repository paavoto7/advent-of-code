#include <vector>
#include <string>
#include <list>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

// I will add reasoning/documentation in the evening

int part1(const vector<string>& input) {

    constexpr int dirs[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1},
    };

    const auto rows = input.size();
    const auto cols = input[0].size();

    int accessableRolls = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            char pos = input[i][j];
            if (pos == '.') continue;

            int adjRolls = 0;
            for (int k = 0; k < 8; ++k) {
                int y = i + dirs[k][0];
                int x = j + dirs[k][1];

                if (isInBounds(y, x, rows, cols) && input[y][x] == '@') {
                    adjRolls++;
                }
            }

            if (adjRolls < 4) accessableRolls++;
        }
    }
    
    return accessableRolls;
}

int part2(vector<string> input) {

    constexpr int dirs[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1},
    };

    const auto rows = input.size();
    const auto cols = input[0].size();

    int accessableRolls = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (input[i][j] == '.') continue;

            int adjRolls = 0;

            for (int k = 0; k < 8; ++k) {
                // Could be without static cast, as isInBounds checks for too high values
                int y = static_cast<int>(i) + dirs[k][0];
                int x = static_cast<int>(j) + dirs[k][1];

                if (isInBounds(y, x, rows, cols) && input[y][x] == '@') {
                    adjRolls++;
                }
            }

            if (adjRolls < 4) {
                accessableRolls++;
                input[i][j] = '.';
                // Go to the top-left corner in the eight adjacent grid
                i -= 1 - (i == 0);
                j -= 2 - (j == 0);
            }
        }
    }
    
    return accessableRolls;
}

int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day4.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
