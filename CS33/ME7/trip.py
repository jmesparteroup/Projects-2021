def s32(value):
    return -(value & 0x80000000) | (value & 0x7fffffff)

table = list()
for i in range(int(input())):
    no = input()
    no = '0x' + no
    table.append(s32(int(no, 16)))

for i in table:
    print(i)


