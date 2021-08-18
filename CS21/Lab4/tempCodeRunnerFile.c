
for k from 1 to N:
    for i from 1 to N:
        for j from 1 to N:
            MATRIX[I][J] = min(MATRIX[I][J], MATRIX[I][K] + MATRIX[K][J])
