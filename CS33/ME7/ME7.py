from math import sqrt, floor
from itertools import permutations


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
    return sqrt((x[0]-y[0])**2 + (x[1]-y[1])**2)

def solve(data, graph):
    
    minimum = 0xFFFFFFFFFFF
    shortest = []
    num = len(graph)

    for i in range(1):
        tempRoutes = list(permutations([j for j in range(num) if i!= j]))
        where = floor(len(tempRoutes)*(num+1//2)/num)
        tempRoutes = tempRoutes[0:where]

        while tempRoutes:
            route = [i] + list(tempRoutes.pop()) + [i]
            routeCost = 0

            for j in range(len(route)-1):
                routeCost += graph[route[j]][route[j+1]]
            
            if routeCost < minimum:
                minimum = routeCost
                shortest = route

    print(round(minimum, 3))

    for i in shortest:
        print(data[i][0])

    return

if __name__ == '__main__':
    main()