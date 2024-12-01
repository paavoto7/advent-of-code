"""This is a very naive solution that "actually" expands the universe.
This worked for part one but for obvious reasons was horrible for part two.
The part 2 solution can be used for this too by simply omitting the multiplier"""


def main():
    universe = []
    galaxies = {}
    with open("day11.txt", "r") as f:
        for num, line in enumerate(f):
            line = line.strip()
            if "#" in line:
                universe.append(list(line))
                for ind in find_indexes(line, "#"):
                    galaxies[len(galaxies)+1] = [num, ind]
            else:
                # Expand the rows
                universe.append(list(line))
                universe.append(list(line))


    expand_columns(universe, galaxies)

    galaxies.clear()

    for row_num, line in enumerate(universe):
        for ind in find_indexes(line, "#"):
            galaxies[len(galaxies)+1] = (row_num, ind)
            
    count = 0
    for i in range(1, len(galaxies)):
        for j in range(i, len(galaxies)):
            count += (abs(galaxies[j+1][0]-galaxies[i][0]))+(abs(galaxies[j+1][1]-galaxies[i][1]))
    
    print(count)


def expand_columns(universe, galaxies: dict):
    full_cols = {ind for _, ind in galaxies.values()}
    for line in universe:
        length = len(line)
        for i in range(len(line)):
            if i not in full_cols:
                if line[i+(len(line)-length)] == "#":
                    n = i+(len(line)-length)
                    while line[n] == "#":
                        n += 1
                    line.insert(n, ".")
                else:
                    line.insert(i+(len(line)-length), ".")


def find_indexes(line, char):
    return [i for i, ltr in enumerate(line) if ltr == char]


if __name__ == "__main__":
    main()

