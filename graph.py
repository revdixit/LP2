def is_safe(graph, hall_colors, hall, color):
    """Check if color can be assigned to hall."""
    for adjacent_hall in range(len(graph)):
        if graph[hall][adjacent_hall] == 1 and hall_colors[adjacent_hall] == color:
            return False
    return True

def branch_and_bound(graph, hall_colors, hall=0, bound=float('inf'), color_names=None):
    """Branch and Bound approach to solve hall coloring."""
    if hall == len(graph):
        return True
    
    available_colors = set(color_names) if color_names else set()
    if color_names:
        for adjacent_hall in range(len(graph)):
            if graph[hall][adjacent_hall] == 1 and hall_colors[adjacent_hall] in available_colors:
                available_colors.remove(hall_colors[adjacent_hall])
                
        if len(available_colors) >= bound:
            return False

    for color in available_colors if color_names else [1]: #If color names are not provided, just return true, as we dont color.
        hall_colors[hall] = color
        if branch_and_bound(graph, hall_colors, hall + 1, bound, color_names):
            return True
        hall_colors[hall] = None  # Backtrack
    
    return False

def backtracking(graph, hall_colors, hall=0, color_names=None):
    """Recursive function to solve the hall coloring problem using backtracking."""
    if hall == len(graph):  # All halls are assigned a color
        return True

    if color_names:
        for color in color_names:
            if is_safe(graph, hall_colors, hall, color):
                hall_colors[hall] = color
                if backtracking(graph, hall_colors, hall + 1, color_names):
                    return True
                hall_colors[hall] = None  # Backtrack
    
    return False

def solve(graph, method, color_names=None):
    """Solves the hall coloring problem using backtracking or branch and bound."""
    hall_colors = [None] * len(graph)
    if method == 1:
        success = backtracking(graph, hall_colors, color_names=color_names)
    elif method == 2:
        success = branch_and_bound(graph, hall_colors, color_names=color_names)
    else:
        print("Invalid choice. Please enter 1 or 2.")
        return False

    if not success:
        print("No solution exists")
        return False
    print("Solution exists: ", hall_colors)
    return True

def create_adjacency_matrix(edges, num_halls):
    """Creates an adjacency matrix from edge list."""
    graph = [[0] * num_halls for _ in range(num_halls)]
    for edge in edges:
        hall1, hall2 = edge
        graph[hall1][hall2] = 1
        graph[hall2][hall1] = 1
    return graph

# Menu-driven program
num_halls = int(input("Enter number of halls: "))
num_edges = int(input("Enter number of edges: "))
edges = []
print("Enter edges as (hall1 hall2):")
for _ in range(num_edges):
    hall1, hall2 = map(int, input().split())
    edges.append((hall1, hall2))

graph = create_adjacency_matrix(edges, num_halls)

color_names = input("Enter color names separated by spaces : ").split()

while True:
    print("\nHall Coloring Problem")
    print("1. Solve using Backtracking")
    print("2. Solve using Branch and Bound")
    print("3. Exit")
    choice = int(input("Enter your choice: "))
    if choice == 3:
        break
    solve(graph, choice, color_names)