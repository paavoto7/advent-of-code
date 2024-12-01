"""This solution uses the simple Manhattan geometry to find the shortest distances.
This works well due to adding the expansion to the coordinates."""


def main():
    galaxies = {}
    empty_rows = []
    with open("day11.txt", "r") as f:
        for num, line in enumerate(f):
            line = line.strip()
            if "#" in line:
                for ind in find_indexes(line, "#"):
                    galaxies[len(galaxies)+1] = [num, ind]
                empty_rows.append(0)
            else:
                empty_rows.append(1)
    
    # Calculate the new coordinates
    expansion(galaxies, empty_rows, 10**6)

    count = 0
    # Loop over the galaxies and count the distance for a pair only once
    for i in range(1, len(galaxies)):
        for j in range(i, len(galaxies)):
            count += (abs(galaxies[j+1][0]-galaxies[i][0]))+(abs(galaxies[j+1][1]-galaxies[i][1]))
    print(count)
    

def expansion(galaxies: dict, empty_rows: list, multiplier = 2):
    full_cols = {ind for _, ind in galaxies.values()}
    empty_cols = [i if i in full_cols else None for i in range(len(galaxies)+1)]

    for key in galaxies.keys():
        ind = galaxies[key][1]
        galaxies[key][1] += empty_cols[:ind].count(None) * (multiplier-1)

        row = galaxies[key][0]
        galaxies[key][0] += empty_rows[:row].count(1) * (multiplier-1)


def find_indexes(line, char):
    return [i for i, ltr in enumerate(line) if ltr == char]


if __name__ == "__main__":
    main()

