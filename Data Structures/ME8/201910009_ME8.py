
def parseInput():
    capacity = int(input())
    numItems = int(input())
    acceptitems = [input().split() for i in range(numItems)]
    items = [[int(x[0]), int(x[1]), int(x[2])] for x in acceptitems]
    items.insert(0, [0,0,0])

    return capacity, items

def solve(capacity, data):
    v = [[0 for j in range(capacity+1)] for i in range(len(data))]

    for i in range(len(data)):
        for j in range(capacity+1):
            if i == 0 or j == 0:
                v[i][j] = 0
            else:
                if j - data[i][1] >= 0:
                    v[i][j] = max(v[i-1][j], data[i][2] + v[i-1][j-data[i][1]])
                else:
                    v[i][j] = v[i-1][j]
    
    i = len(data)-1; j = capacity

    #backtracking
    print(v[i][j])

    while i!=0:
        if v[i][j] != v[i-1][j]:
            print(data[i][0])
            j += -(data[i][1])
            i += -1
        else:
            i += -1

    return



if __name__ == '__main__':
    capacity,data = parseInput()
    solve(capacity, data)

