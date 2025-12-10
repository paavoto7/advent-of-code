from collections import defaultdict
# Will not work on Python versions under 3.7


def main():
    hands = defaultdict(list)
    powers = {"A": 14, "K": 13, "Q": 12, "J": 1, "T": 10}
    with open("day7.txt", "r") as f:
        for line in f:
            hand, bid = line.split()
            di = defaultdict(int)
            # Make it so that determining the strength is easy
            for val in hand:
                di[val] += 1
            # Make it easier to compare the same strength hands
            hand = [int(x) if x.isnumeric() else int(powers[x]) for x in hand]
            # Use strength as the key and append to a list a tuple of bid and hand
            hands[strength(di)].append((bid, hand))
    
    # Dictionaries are ordered as of Python 3.7
    hands = {key: value for key, value in sorted(hands.items())[::-1]}
    total = 0
    items = 1
    
    for bucket in hands.items():
        for bid, _ in sorted(bucket[1], key=lambda x: x[1]):
            total += items * int(bid)
            items += 1
    
    print("Answer: "+str(total))
            
            
def strength(hand):
    if "J" in hand:
        val = hand["J"]
        del hand["J"]
        if len(hand) == 0:
            hand["1"] = 0 # Just a placeholder for the case of all being J
        highest = max(hand, key=hand.get)
        hand[highest] += val
               
    length = len(hand)
    # Five of a kind
    if length == 1:
        return 1
    # Four of a kind or full house
    elif length == 2:
        if max(hand.values()) == 4:
            return 2
        else:
            return 3
    # Three of a kind or two pair
    elif length == 3:
        if max(hand.values()) == 3:
            return 4
        else:
            return 5
    # One pair
    elif length == 4:
        return 6
    # High card
    else:
        return 7
        
    
if __name__ == "__main__":
    main()

