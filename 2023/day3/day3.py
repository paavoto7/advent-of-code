import re
from collections import defaultdict
import math

def solution():
    with open("day3.txt", "r") as source:
        data = []
        syms = []
        gears = []
        syms.append([])
        gears.append([])
        sumnum = 0
        
        for line in source:
            level = []
            sym_level = []
            gear_level = []
            for char in re.finditer("[0-9]+|[^\.]",line.strip("\n")):                
                if char[0].isnumeric():
                    level.append((int(char[0]),char.span()[0],char.span()[1]))
                else:
                    if char[0] == "*":
                        gear_level.append((char[0], char.span()[0]))
                    sym_level.append((char[0], char.span()[0]))
            data.append(level)
            syms.append(sym_level)
            gears.append(gear_level)

        syms.append([])
        gears.append([])
        gears_nums = defaultdict(lambda: list())
       
        for i in range(0, len(data)):
            for j in range(0, len(data[i])):
                num = data[i][j]                
                
                # PART 1
                for k in range(0, len(max(syms, key=len))):

                    symbols = [get_symbol(syms, i+x, k)[1] for x in range(3)]

                    if any(num[1]-1 <= sym <= num[2] for sym in symbols):                    
                        sumnum += num[0]
                
                # PART 2
                for k in range(0, len(max(gears, key=len))):

                    symbol_above = get_symbol(gears, i, k)
                    symbol_current = get_symbol(gears, i+1, k)
                    symbol_below = get_symbol(gears, i+2, k)

                    if num[1]-1 <= symbol_above[1] <= num[2]:
                        gears_nums[int(f"{i}{symbol_above[1]}")].append(num)
                    
                    if num[1]-1 <= symbol_current[1] <= num[2]:
                        gears_nums[int(f"{i+1}{symbol_current[1]}")].append(num)
                    
                    if num[1]-1 <= symbol_below[1] <= num[2]:
                        gears_nums[int(f"{i+2}{symbol_below[1]}")].append(num)
                    
        product = 0
        for gear, amount in gears_nums.items():
            if len(amount) >= 2:
                product += math.prod(x[0] for x in amount)
        print("Sum: "+str(sumnum))
        print("Product: "+str(product))


def get_symbol(syms, i, k):
    return syms[i][k] if len(syms[i]) >= k+1 else (0, -10)    


if __name__ == "__main__":
    solution()

