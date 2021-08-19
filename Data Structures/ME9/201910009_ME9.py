from random import randint
from math import sqrt
visited = []
MST = []
path = []


def main ():
    numberOfPlaces = int(input())

    data = acceptInput(numberOfPlaces)
    graph = constructGraph(data)
    solve(data, graph)
    return

def acceptInput(n):
    
    data = [input().split() for i in range(n)]
    #format data
    dataFormatted = [ [x[0], x[1], float(x[2])*1000, float(x[3])*1000] for x in data ]
    return dataFormatted

def constructGraph(data):
    graph = list()
    num = len(data)

    for i in range(num):
        temp = list()
        for j in range(num):
            temp.append(getDistance(data[i][2:4], data[j][2:4]))
        graph.append(temp)

    return graph

def getDistance(x,y):
    return round(sqrt((x[0]-y[0])**2 + (x[1]-y[1])**2),6)

def solve(data, graph):
    global visited, MST,path
    visited = [0 for i in range(len(graph))]
    MST = Prims(graph)
    DFS(0, data)
    path.append(0)

    routeCost = 0
    for i in range(len(path)-1):
        routeCost += graph[path[i]][path[i+1]]
    
    print(round(routeCost,3))

    for vertex in path:
        print(data[vertex][0]) 

def Prims(graph):
    num = len(graph)
    selected = [0 for i in range(num)]
    MST =  [[0 for j in range(num)] for i in range(num)]
    count = 0
    selected[0] = True

    while count < num-1:
        minimum = 0xFFFFFFFFF
        lucky = 0
        start = 0

        for i in range(num):
            if selected[i]:
                for j in range(num):
                    if not selected[j] and graph[i][j]:
                        if minimum > graph[i][j]:
                            minimum = graph[i][j]
                            lucky = j
                            start = i
        count += 1

        selected[lucky] = True
        MST[start][lucky] = graph[start][lucky]
        MST[lucky][start] = graph[start][lucky]
        
        if count == num-1:
            selected[0] = False  

    return MST
    
def DFS(node, data):
    global visited, MST, path
    if visited[node]:
        return
    path.append(node)
    visited[node] = True
    
    neighbors = [(i, MST[node][i]) for i in range(len(MST[node])) if MST[node][i] != 0]
    neighbors.sort(key=lambda x: x[1])
    for vertex in neighbors:
        DFS(vertex[0], data)

if __name__ == '__main__':
    main()


