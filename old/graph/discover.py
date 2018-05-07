import socket
import graph_
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import nodes as nodes_file
from nodes import connect
from nodes import connection
from graph_ import create_graph
from graph_ import get_shortest_distance
nodes = {}
node=[]
batt=[]
x=[]
y=[]
z=[]

for i in range(0, 100):
    s = socket.socket()
    try:
        s.connect(("127.0.0.1", 54320 + i))
        s.send(b"NDSCRCCMMDDATA")
        recv = s.recv(40)
        recv = recv.decode("utf-8")
        recv = recv.split(":")
        #print(recv)
        if (recv[0] == "available"):
            nodes[str(54320 + i)] = str("%s,%s,%s,%s" %
                                        (recv[2], recv[3].rstrip('\x00'),
                                         recv[4].rstrip('\x00'),
                                         recv[5].rstrip('\x00')))
        s.close()
    except:
        print("node at %s not available\n" % str(54320 + i))

print("Nodes available: ")
print(nodes)
print("Number of nodes: %d" % len(nodes))

for i in nodes:
    data=nodes[str(i)].split(",")
    node.append(int(str(i)))
    batt.append(int(data[0]))
    x.append(int(data[1]))
    y.append(int(data[2]))
    z.append(int(data[3]))

nodes_file.nodes = nodes
nodes_file.node = node
nodes_file.batt = batt
nodes_file.x = x
nodes_file.y = y
nodes_file.z = z

fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')
ax.scatter(x,z,y)
ax.set_zlabel("height")
plt.show()

