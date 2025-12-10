import math


def main():
    with open("day6.txt", "r") as f:
        time, distance = f.read().splitlines()
        time = int("".join(time.split()[1:]))
        distance = int("".join(distance.split()[1:]))

        times = 1
        times *= simulation(time, distance)

        print("Brute force: "+str(times))
        print("Quadratic solution: "+str(solve_quad(-1, time, -distance)))


# I first created the naive brute force method
def simulation(time, distance):
    times = 0
    for i in range(1, time):
        new_time = i*(time-i)
        if new_time > distance:
            times += 1
    return times


# A quadratic solution
# The answer is the range where hold_time * (total_time - hold_time) > record_time
# Which expanded is -hold_time^2 + hold_time * total_time - record_time > 0
def solve_quad(a, b, c):
    root_1 = (-b+math.sqrt(b**2-4*a*c))/(2*a) # Find root 1
    root_2 = (-b-math.sqrt(b**2-4*a*c))/(2*a) # Find root 2
    return int(root_2-root_1)


if __name__ == "__main__":
    main()

