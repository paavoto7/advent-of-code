

def main():
    with open("day6.txt", "r") as f:
        time, distance = f.read().splitlines()
        time = list(map(int, time.split()[1:]))
        distance = list(map(int, distance.split()[1:]))
        times = 1
        for i in range(len(time)):
            times *= simulation(time[i], distance[i])
        print(times)


def simulation(time, distance):
    times = 0
    for i in range(1, time):
        new_time = i*(time-i)
        if new_time > distance:
            times += 1
    return times



if __name__ == "__main__":
    main()