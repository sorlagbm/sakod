import sys

class Graph:
    def __init__(self, nodes, init_graph):
        self.nodes = nodes
        self.graph = self.construct_graph(nodes, init_graph)

    def get_nodes(self) -> []:
        return self.nodes

    def get_outgoing_edges(self, node) -> []:
        connections = []
        for out_node in self.nodes:
            if self.graph[node].get(out_node, False) != False:
                connections.append(out_node)
        return connections

    def value(self, node1, node2) -> int:
        return self.graph[node1][node2]

    def construct_graph(self, nodes, init_graph) -> None:
        graph = {}
        for node in nodes:
            graph[node] = {}

        graph.update(init_graph)

        for node, edges in graph.items():
            for adjacent_node, value in edges.items():
                if graph[adjacent_node].get(node, False) == False:
                    graph[adjacent_node][node] = value

        return graph


def dijkstra_algorithm(graph, start_node) -> {}:
    unvisited_nodes = list(graph.get_nodes())

    shortest_path = {}

    previous_nodes = {}

    max_value = sys.maxsize
    for node in unvisited_nodes:
        shortest_path[node] = max_value
    shortest_path[start_node] = 0

    while unvisited_nodes:
        current_min_node = None
        for node in unvisited_nodes:
            if current_min_node == None:
                current_min_node = node
            elif shortest_path[node] < shortest_path[current_min_node]:
                current_min_node = node

        neighbors = graph.get_outgoing_edges(current_min_node)
        for neighbor in neighbors:
            tentative_value = shortest_path[current_min_node] + graph.value(current_min_node, neighbor)
            if tentative_value < shortest_path[neighbor]:
                shortest_path[neighbor] = tentative_value
                previous_nodes[neighbor] = current_min_node

        unvisited_nodes.remove(current_min_node)

    return previous_nodes, shortest_path

def print_result(previous_nodes : [], shortest_path : int, start_node : str, target_node : str) -> None:
    path = []
    node = target_node

    while node != start_node:
        path.append(node)
        node = previous_nodes[node]

    path.append(start_node)

    print("We found the following best path with a value of {}.".format(shortest_path[target_node]))
    print(" -> ".join(reversed(path)))

def main() -> None:
    nodes = ["A", "B", "C", "D", "E"]

    init_graph = {}
    for node in nodes:
        init_graph[node] = {}

    init_graph["A"]["B"] = 5
    init_graph["A"]["C"] = 4
    init_graph["C"]["E"] = 1
    init_graph["D"]["A"] = 3
    init_graph["B"]["E"] = 5

    graph = Graph(nodes, init_graph)

    previous_nodes, shortest_path = dijkstra_algorithm(graph, "A")

    print_result(previous_nodes, shortest_path, "A", "C")

if __name__ == "__main__":
    main()
