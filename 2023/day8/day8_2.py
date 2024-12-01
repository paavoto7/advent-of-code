import math


def main():
    graph = {}
    a_nodes = list()
    with open("day8.txt", "r") as f:
        instructions, _, *nodes = f.read().splitlines()
        for node in nodes:
            node = node.replace(" ", "").split("=")
            neighbours = node[1].replace("(", "").replace(")", "").split(",")
            graph[node[0]] = neighbours[0], neighbours[1]
            # Append the ones ending on A to the list
            if node[0][2] == "A":
                a_nodes.append(node[0])

    nums = []
    for a_node in a_nodes:        
        nums.append(loop_steps(graph, instructions, a_node))
    
    # I have to give credit to Reddit community as I didn't think of LCM myself
    # This solution should be pretty general as this makes no assumptions based on the input
    # The loop_steps function hardly is mathematically sound but it is as good for the general case
    # as I was able to come up with
    print(math.lcm(*nums))


# Used to find the steps of a "loop" to reach "Z" for lcm
def loop_steps(graph, instructions, a_node):
    steps = 0
    current = a_node
    new_ins = instructions
    while True:
        if current.endswith("Z"):
            return steps
        else:
            steps += 1
            if new_ins[0] == "L":
                current = graph[current][0]
                new_ins = new_ins[1:]+new_ins[0]
            else:
                current = graph[current][1]
                new_ins = new_ins[1:]+new_ins[0]
    return steps


# Once the problem now became more complicated, this solution is also too slow
# Even though this works, it takes a very long time to run
def find_path_memory(graph, instructions, a_nodes):    
    steps = 0
    currents = a_nodes
    new_ins = instructions
    while True:
        if all(current.endswith("Z") for current in currents):
            return steps
        else:
            steps += 1
            if new_ins[0] == "L":
                currents = {graph[current][0] for current in currents}
                new_ins = new_ins[1:]+new_ins[0]
            else:
                currents = {graph[current][1] for current in currents}
                new_ins = new_ins[1:]+new_ins[0]
                

if __name__ == "__main__":
    main()

