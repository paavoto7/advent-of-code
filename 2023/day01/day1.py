
words = {"one": "1", "two": "2", "three": "3", "four": "4", "five": "5", "six": "6", "seven": "7", "eight": "8", "nine": "9"}

def main():

    sum = 0
    with open("day1.txt", "r") as t:
        for line in t:
            nums = []
            indexes = [None]*len(line)

            for i in range(0, len(line)):
                if line[i].isdigit():
                    indexes[i] = line[i]
                    
                
            for word in words.keys():
                x = list(find_all(line, word))
                        
                for num in x:
                    indexes[num] = words[word]
                  
            nums = [x for x in indexes if x is not None]           
            sum += int(nums[0] + nums[-1])
            
    print(sum)

# Chars is the string and sub is the one we want to find
def find_all(chars, sub):
    start = 0
    while True:
        start = chars.find(sub, start)
        if start == -1: return
        yield start
        start += 1


if __name__ == "__main__":
    main()
