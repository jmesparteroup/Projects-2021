from math import sqrt
import numpy as np

def main ():
    numberOfPlaces = int(input())
    data = acceptInput(numberOfPlaces)
    graph = constructGraph(data)
    solve(data, graph)
    return

def acceptInput(n):
    data = [input().split() for i in range(n)]
    #format data
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
    return sqrt((x[0]-y[0])**2 + (x[1]-y[1])**2)

def solve(data, graph):
    shortest = leastCost(graph)
    print(shortest[0])
    print(shortest)
    for i in range(len(graph)):
        print(data[shortest[i+1]])


def leastCost(graph, itinerary = [0], selected = 0, cost=0):

    if len(itinerary) == len(graph)+1:
        return []
    minimum = np.sum(np.array(graph))
    
    path = []
    num = len(graph)
    for i in range(num): #rows
        if i in itinerary:
            continue
        for j in range(num): #columns

            if j in itinerary:
                continue
            temp = leastCost(graph, itinerary + [i], j, cost+graph[i][j])
            if temp[0] < minimum:
                minimum = temp[0]
                path = temp[1:len(graph)]

    return itinerary + path

if __name__ == '__main__':
    main()