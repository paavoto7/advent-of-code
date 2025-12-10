import re

def main():
    sum = 0
    power = 0

    with open("day2.txt", "r") as games:
        for line in games:
            sets = "".join(line[8:].replace("\n", "").split(";"))
            
            red = find_amount(sets, "red")
            green = find_amount(sets, "green")
            blue = find_amount(sets, "blue")
            
            # Sum for part 1
            if red <= 12 and green <= 13 and blue <= 14:
                sum += int(re.match("Game ([0-9]+)", line).group(1))
            
            # Power for part 2
            power += red * green * blue
            
    
    print("Sum is: "+str(sum)+"\nPower is: "+str(power))
            
            
# find the max amount of given color in the sets
def find_amount(set, colour):
    return max(map(lambda x: int(x), re.findall(f"([0-9]+) {colour}", set)))


if __name__ == "__main__":
    main()
