import networkx as nx
import matplotlib.pyplot as plt

connection = {}
g = nx.Graph()

def create_graph():
    for i in connection:
        g.add_weighted_edges_from(connection[i])
    nx.draw(g)
    plt.show()

def get_shortest_distance(src_node,dest_node):
    print("Shortest Distance Length: %f" % nx.shortest_path_length(g,src_node,dest_node,weight='weight'))
    print(nx.shortest_path(g,src_node,dest_node,weight='weight'))
