


def main():
    with open("day5.txt", "r") as f:
        parts = f.read().split("\n\n")
        seeds = list(map(int, parts[0].split()[1:]))
        locations = list(map(int, parts[-1].split()[2:]))

        maps = []
        
        for part in parts[1:]:
            kartta = []
            for ranges in part.split("\n")[1:]:
                
                nums = list(map(int, ranges.split()))
                   
                kartta.append(nums)
                
            maps.append(kartta)


        locations = []
        
        for i in range(0, len(seeds), 2):
            ranges = [[seeds[i], seeds[i]+seeds[i+1]]]
            results = []
            for _map in maps:
                while ranges:
                    start_range, end_range = ranges.pop()
                    for target, start_map, r in _map:
                        end_map = start_map + r
                        offset = target-start_map
                        if end_map <= start_range or end_range <=start_map:
                            continue
                        if start_range < start_map:
                            ranges.append([start_range, start_map])
                            start_range = start_map
                        if end_map < end_range:
                            ranges.append([end_map, end_range])
                            end_range = end_map
                        results.append([start_range+offset, end_range+offset])
                        break
                    else:
                        results.append([start_range, end_range])
                ranges = results
                results = []
            locations += ranges

        print(min(loc[0] for loc in locations))


if __name__ == "__main__":
    main()