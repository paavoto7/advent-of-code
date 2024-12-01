

def main():
    graph = {}
    with open("day8.txt", "r") as f:
        instructions, _, *nodes = f.read().splitlines()
        for node in nodes:
            node = node.replace(" ", "").split("=")
            neighbours = node[1].replace("(", "").replace(")", "").split(",")
            graph[node[0]] = neighbours[0], neighbours[1]

    #print(find_path(graph, instructions, "AAA", "ZZZ"))
    print(find_path_memory(graph, instructions))
        

# This is the solution that works for the big problem input
def find_path_memory(graph, instructions):    
    steps = 0
    current = "AAA"
    new_ins = instructions
    while True:
        if current == "ZZZ":
            return steps
        else:
            steps += 1
            if new_ins[0] == "L":
                current = graph[current][0]
                new_ins = new_ins[1:]+new_ins[0]
            else:
                current = graph[current][1]
                new_ins = new_ins[1:]+new_ins[0]
                
           
# This recursive solution works for small inputs
# but a big one will exceed recursion depth or run out of memory
def find_path(graph, instructions, current, goal):
    if current == goal:
        return 0
    else:
        new_ins = instructions[1:]+instructions[0]
        if instructions[0] == "L":
            return 1 + find_path(graph, new_ins, graph[current][0], goal)
        else:
            return 1 + find_path(graph, new_ins, graph[current][1], goal)



if __name__ == "__main__":
    main()

