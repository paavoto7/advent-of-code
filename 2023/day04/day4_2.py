
def main():
    carlist = []
    with open("day4.txt", "r") as f:
        for line in f:
            parts = line.replace(":", "||").strip("\n").split("|")
            matches = 0

            ind = int(parts[0].split()[1])

            if len(carlist) < ind:
                carlist.append(1)
            else:
                carlist[ind-1] += 1
            
            win = set(parts[2].split(" "))
            if "" in win: win.remove("")

            for num in parts[3].split():
                if num in win:

                    if len(carlist) > ind + matches:
                        carlist[ind+matches] += carlist[ind-1]
                    else:
                        carlist.append(carlist[ind-1])
                    
                    matches += 1                

    print(sum(carlist))


if __name__ == "__main__":
    main()