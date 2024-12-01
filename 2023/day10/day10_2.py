"""Credit for the idea of using Shoelace formula and Pick's theorem in the part 2
goes to the AoC Reddit community"""


def main():
    grid = []
    S_loc = tuple()
    with open("day10.txt", "r") as f:
        for x, line in enumerate(f):
            grid.append(list(line.strip("\n")))
            if "S" in line:
                S_loc = (x, line.index("S"))

    biggest, enclosed = 0, 0
    directions = [(0, 1), (0, -1), (-1, 0), (1, 0)]

    for dir in directions:
        length, tiles = find_loop(grid, tuple(map(lambda x, y: x + y, dir, S_loc)), S_loc)
        if length > biggest:
            biggest = length
            enclosed = tiles
    
    print("Farthest: "+str(biggest)+"\nEnclosed tiles: "+str(enclosed))


def find_loop(grid, start, goal):
    directions = {"|": [(-1, 0), (1, 0)],
                  "-": [(0, -1), (0, 1)],
                  "L": [(-1, 0), (0, 1)],
                  "J": [(-1, 0), (0, -1)],
                  "7": [(0, -1), (1, 0)],
                  "F": [(0, 1), (1, 0)]}
    current = start
    previous = goal
    edges = [goal]
    length = 1
    cur_char = grid[goal[0]][goal[1]]
    while True:
        # Can't go over the edges
        if current[0] < 0:
            return -1
        
        if current == goal:
            return length // 2, shoelace_picks(edges, length)
        
        if (cur_char := grid[current[0]][current[1]]) == ".":
            return -1
        
        # Append the edges
        if not cur_char == "-"  and not cur_char == "|":
            edges.append(current)

        pos_1 = tuple(map(lambda x, y: x + y, current, directions[cur_char][0]))
        pos_2 = tuple(map(lambda x, y: x + y, current, directions[cur_char][1]))

        if previous != pos_1:
            previous = current
            current = pos_1
        else:
            previous = current
            current = pos_2

        length += 1


# This function counts first the area of the pipe loop using the Shoelace formula (https://en.wikipedia.org/wiki/Shoelace_formula)
# Then using the Pick's theorem (A = i + b/2 - 1) solved for i (https://en.wikipedia.org/wiki/Pick%27s_theorem)
def shoelace_picks(coords, length):
    shoelace = 0
    for i in range(0, len(coords)):
        shoelace += coords[i-1][0]*coords[i][1]-coords[i][0]*coords[i-1][1]
    pick = abs(0.5 * shoelace)-length/2+1
    return pick


if __name__ == "__main__":
    main()

