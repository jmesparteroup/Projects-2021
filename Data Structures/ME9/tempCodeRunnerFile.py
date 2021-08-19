
from math import sqrt
visited = []
itinerary = []
MST = []


def main():
    numberOfPlaces = int(input())
    data = acceptInput(numberOfPlaces)
    graph = constructGraph(data)
    solve(data, graph)
    return

def acceptInput(n):
    
    data = [input().split() for i in range(n)]
    #format data
    # dataFormatted = [ [x[0], x[1], float(x[2])*1000, float(x[3])*1000] for x in data ]
    dataFormatted = [ [x[0], x[1], float(x[2]), float(x[3])] for x in data ]
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
    return round(sqrt((x[0]-y[0])**2 + (x[1]-y[1])**2),5)

def solve(data, graph):
    global visited, MST, itinerary
    visited = [0 for i in range(len(graph))]
    MST = graph

    DFS(0,data)
    shorter = FW(graph)
    itinerary.append(0)
    routeCost = 0


    for i in range(len(itinerary)-1):
        routeCost += shorter[itinerary[i]][itinerary[i+1]]

    print(round(routeCost,3))

    # if round(routeCost, 3) == 35.938:
    #     for i in data[0]:
    #         print(i)
            
    
    for i in itinerary:
        print(data[i][0])

def FW(graph):
    num = len(graph)
    g = graph

    for k in range(num):
        for i in range(num):
            for j in range(num):
                if g[i][k]+g[k][j] < g[i][j]:
                    print(g[i][k]+g[k][j])
                g[i][j] = min(g[i][j], g[i][k]+g[k][j])

    return g
    
def DFS(node, data):
    global visited, MST, itinerary
    if visited[node]:
        return
    
    visited[node] = True
    itinerary.append(node)
    
    neighbors = [(i, MST[node][i]) for i in range(len(MST[node])) if MST[node][i] != 0]
    neighbors.sort(key=lambda x: (x[1], x[0]) )
    for vertex in neighbors:
        DFS(vertex[0], data)
        
if __name__ == '__main__':
    main()


