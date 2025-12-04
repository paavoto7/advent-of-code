#include <vector>
#include <string>
#include "../../utils/helper.h"
#include "../../utils/timer.h"

using namespace std;
using namespace utils;

/*
This is a simple linear brute-force grid traversal solution.
All it does is loop over each element and check it's adjacent cells.
In the adjacency loop it breaks early if the needed 4 adjacent is reached.
Initially I didn't have that, but upon testing it provided some
performance improvements.
*/
int part1(const vector<string>& input) {

    constexpr int dirs[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1},
    };

    const int rows = static_cast<int>(input.size());
    const int cols = static_cast<int>(input[0].size());

    int accessibleRolls = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (input[i][j] == '.') continue;

            int adjRolls = 0;
            for (int k = 0; k < 8; ++k) {
                int y = i + dirs[k][0];
                int x = j + dirs[k][1];

                if (isInBounds(y, x, rows, cols) && input[y][x] == '@') {
                    adjRolls++;
                }

                if (adjRolls == 4) break;
            }

            if (adjRolls < 4) accessibleRolls++;
        }
    }
    
    return accessibleRolls;
}

/*
This was a pleasant part 2. The solution is largely the same as part 1.

The main difference is that, besides incrementing the accessible rolls,
it changes current to a dot (not roll) and goes back to the top-left corner
in the eight-sized adjacency grid.

It naively re-iterates all the elements on the previous level after removing one.
Of course, this is highly inefficient, but I achieve runtimes of approximately
5-6 ms with -O2 and 4-6 ms with -O3. Without it is ~27-28 ms.

Might come back later and optimise, but I will leave it as is for now.
*/
int part2(vector<string> input) {

    constexpr int dirs[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1},
    };

    const int rows = static_cast<int>(input.size());
    const int cols = static_cast<int>(input[0].size());

    int accessibleRolls = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (input[i][j] == '.') continue;

            int adjRolls = 0;

            for (int k = 0; k < 8; ++k) {
                // Could be without static cast, as isInBounds checks for too high values
                int y = i + dirs[k][0];
                int x = j + dirs[k][1];

                if (isInBounds(y, x, rows, cols) && input[y][x] == '@') {
                    adjRolls++;
                }

                if (adjRolls == 4) break;
            }

            if (adjRolls < 4) {
                accessibleRolls++;
                input[i][j] = '.';
                // Go to the top-left corner in the eight adjacent grid
                if (i > 0) i--;
                j -= (j > 0) ? 2 : 1;
            }
        }
    }
    
    return accessibleRolls;
}

int main(int argc, char *argv[]) {
    string filepath = argc == 2 ? argv[1] : "../inputs/day4.txt";

    // Pass the already parsed input for both
    vector<string> input = getStringInput(filepath);

    timer(part1, input, "Part 1: ");
    timer(part2, input, "Part 2: ");
}
