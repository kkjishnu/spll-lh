import numpy as np
import graph_

nodes = {}
connection = {}

node = []
batt = []
x = []
y = []
z = []


def connect():
    points = []
    for i in range(len(x)):
        points.append([x[i], y[i], z[i]])
    points = np.array(points)

    for i in range(len(x)):
        dist = []
        point = points[i]
        for k in range(len(x)):
            dist.append([k, np.linalg.norm(point - points[k])])
        print(dist)
        temp_list = []
        final_list = []
        for k in dist:
            if (k[1] <= 250):
                temp_list.append((node[k[0]],k[1]))
        for k in temp_list:
            final_list.append((int(node[i]),k[0],k[1]))
        connection[int(node[i])] = final_list
    graph_.connection = connection
