def derangement(n):
    if n == 0 or n == 1:
        return 0
    if n == 2:
        return 1
    
    return (n-1)*(derangement(n-1)+derangement(n-2))

print(derangement(1))
print(derangement(2))
print(derangement(3))
print(derangement(4))
print(derangement(5))