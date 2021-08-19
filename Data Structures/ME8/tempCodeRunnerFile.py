    while i!=0:
        if v[i][j] != v[i-1][j]:
            print(v[i][j])
            j += -(data[i][1])
            i += -1
        else:
            i += -1