def main():
    n = int(input())

    for _ in range(n):
        getnotes = input()
        notes = ['-' if i%2==0 else ' ' for i in range(10)]

        for num in range(len(getnotes)):
            
            for i in range(9):
                j = getnotes[num]
                if i%2 == 0:
                    if (j == 'E' and i == 8) or (j == 'G' and i == 6) or (j == 'B' and i == 4) or (j == 'D' and i == 2) or (j == 'f' and i ==0):
                        notes[i] += 'o-'
                    else:
                        notes[i] += '--'
                else:
                    if (j == 'F' and i == 7) or (j == 'A' and i == 5) or (j == 'C' and i == 3) or (j == 'e' and i == 1):
                        notes[i] += 'o '
                    else:
                        notes[i] += '  '
            if (num != 0 and num % 16 == 15) or num == len(getnotes)-1:

                while notes:
                    print(notes.pop(0))
                notes = ['-' if i%2==0 else ' ' for i in range(10)]
            
                



            



if __name__ == '__main__':
    main()