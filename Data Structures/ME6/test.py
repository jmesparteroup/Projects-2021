

symbols = input()

#HOW TO PARSE?

def symbolParser (symbols):
    symbols = list(symbols)
    List = []; TempList = []
    inList = False
    indexOpen = 0
    indexClose = 0
    for i in range(len(symbols)):
        if symbols[i] == ",":
            continue

        if symbols[i] == "(":
            inList = True
            indexOpen = i
            continue

        if symbols[i] == ")" and inList:
            inList = False
    
            continue

        if not inList:
            TempList.append(symbol)

        if inList:
            Te
            
