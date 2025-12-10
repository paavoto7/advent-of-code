


def main():
    with open("day5.txt", "r") as f:
        parts = f.read().split("\n\n")
        seeds = list(map(int, parts[0].split()[1:]))

        x = []    
        for seed in seeds:
            new = seed
            for part in parts[1:]:
                for ranges in part.split("\n")[1:]:
                    nums = list(map(int, ranges.split()))
                    if new in range(nums[1], nums[1]+nums[2]):
                        new = new + (nums[0]-nums[1])
                        break
            
            
            x.append(new)
        print(min(x))
                        


if __name__ == "__main__":
    main()
