

def main():
    grid = []
    S_loc = tuple()
    with open("day10.txt", "r") as f:
        for x, line in enumerate(f):
            grid.append(list(line.strip("\n")))
            if "S" in line:
                S_loc = (x, line.index("S"))

    biggest = 0
    directions = [(0, 1), (0, -1), (-1, 0), (1, 0)]

    for dir in directions:
        length = find_loop(grid, tuple(map(lambda x, y: x + y, dir, S_loc)), S_loc)
        if length > biggest:
            biggest = length
            
    print(biggest)


def find_loop(grid, start, goal):
    directions = {"|": [(-1, 0), (1, 0)],
                  "-": [(0, -1), (0, 1)],
                  "L": [(-1, 0), (0, 1)],
                  "J": [(-1, 0), (0, -1)],
                  "7": [(0, -1), (1, 0)],
                  "F": [(0, 1), (1, 0)]}
    current = start
    previous = goal
    length = 1
    cur_char = grid[goal[0]][goal[1]]
    while True:
        if current == goal:
            return length // 2
        
        if (cur_char := grid[current[0]][current[1]]) == ".":
            return -1
        
        pos_1 = tuple(map(lambda x, y: x + y, current, directions[cur_char][0]))
        pos_2 = tuple(map(lambda x, y: x + y, current, directions[cur_char][1]))

        if previous != pos_1:
            previous = current
            current = pos_1
        else:
            previous = current
            current = pos_2
        length += 1


if __name__ == "__main__":
    main()

    