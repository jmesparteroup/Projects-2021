inf = 99999999
matrix = [[0,3,inf,5],[2,0,inf,4],[inf,1,0,inf],[inf,inf,2,0]]
N = 4

for K in range(0,N):
    for I in range(0,N):
        for J in range(0,N):
            if matrix[I][K] == inf or matrix[K][J] == inf:
                continue
            else:
                matrix[I][J] = min(matrix[I][J], matrix[I][K] + matrix[K][J])

for item in matrix:
    print(item)

def factorial(n):
    if n==0: 
        return 1

    return n * factorial(n)
    
