n = int(input())
listahan = []

for _ in range(n):
    i,j = input().split()
    if i=="0" and j=="0":
        break
    listahan.append((i,j))
    
for i in range(n):    
    print(listahan[i][0], listahan[i][1])