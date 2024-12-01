

def main():
    num_list = []
    with open("day9.txt", "r") as f:
        for line in f:
            num_list.append(list(map(int, line.split())))
    
    # PART 1
    part1_total = 0
    for nums in num_list:
        part1_total += nums[-1]+difference(nums)
    
    # PART 2
    # This was merely reversing the list and adding the first number instead of the last
    part2_total = 0
    for nums in num_list:
        part2_total += nums[0]+difference(nums[::-1])
    
    print("Part 1 solution: "+str(part1_total))
    print("Part 2 solution: "+str(part2_total))


# Simple recursive approach to this problem
def difference(nums: list):
    if nums.count(nums[0]) == len(nums):
        return 0
    else:
        new_nums = [(nums[i+1]-nums[i]) for i in range(len(nums)-1)]
        return (nums[-1]-nums[-2])+difference(new_nums)


if __name__ == "__main__":
    main()

