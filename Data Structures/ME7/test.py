from itertools import permutations

def main():
    routes = [x for x in range(5)]
    allroutes = permutations(routes)
    
    print(list(allroutes))


if __name__ == '__main__':
    main()


addi $7, $0, 5
addi $8, $0, 10
add $4, $7, $8
addi $2, $2, 1

5
604438533
604504074
15212576
608305153
12

5
addiu $7, $7, 69
j 0x2 08000003
addiu $7, $7, 70
sw $7, 4($0)
lw $4, 4($0)
addiu $2, $2, 1
syscall

6
619118661
619118662
-1408827388
-1945894908
608305153
12

