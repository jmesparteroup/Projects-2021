addi $1, $1, 1
addi $2, $2, 2
addi $3, $3, 3
addi $4, $4, 4
addi $5, $5, 5
addi $6, $6, 6
addi $7, $7, 7
addi $8, $8, 8
addi $9, $9, 9
addi $10, $10, 10
addi $11, $11, 11
addi $12, $12, 12
addi $13, $13, 13
addi $14, $14, 14
addi $15, $15, 15
addi $16, $16, 16
addi $17, $17, 17
addi $18, $18, 18
addi $19, $19, 19
addi $20, $20, 20
addi $21, $21, 21
addi $22, $22, 22
addi $23, $23, 23
addi $24, $24, 24
addi $25, $25, 25
addi $26, $26, 26
addi $27, $27, 27
addi $28, $28, 28
addi $29, $29, 29
addi $30, $30, 30
addi $31, $31, 31
add $1, $2, $8
sub $2, $1, $10
sw $1, 12($0)
sw $2, 16($0)

addi $1, $0, 0x069
addi $2, $0, 0x420
add $3, $2, $1
add $4, $2, $1
or $5, $2, $1
and $6, $2, $1
slt $7, $2, $1
slt $8, $2, $1
beq $7, $8, 1
addi $9, $0, 0x068
addi $9, $0, 0x069
beq $7, $6, 1
addi $10, $0, 0x41F
addi $10, $0, 0x420

li $3, 15

li $5, 0xBABE
lui $5, $5, 0xC0DE

li $10, 0x1
sll $10, $10, 3
li $11, 0x10
nor $12, $10, $11
sll $12, $12, 0

    li $3, BABE
    li $4, BEEF
    sll $3, $3, 0
    sll $4, $4, 0
    lui $5, $5, 0xC0DE
    lui $6, $6, 0xDEAD
    sll $5, $5, 0
    sll $6, $6, 0
    or $5, $5, $3
    or $6, $6, $4
    mix 
    sll $7, $7, 0

4403BABE
4404BEEF
00031800
00042000
3c05c0de
3c06dead
00052800
00063000
00a32825
00c43025
00A63833
00073800

440a0001
000a50c0
440b0010
014b6027
000c6000


014b6027
0000 00 01 0100 1011 0110 0000 0010 0101

0001 0001 
0111 1101 -> 7D

0111 1100 0010 0010


li $1, 0xBEEF
lui $2, 0xC0DE
blt $1, $2, 2
li $3, 69
li $4, 69
li $1, 69
li $2, 69

4401BEEF
3c02c0de
7C220002
44030069
44040069
44010069
44020069

440a0001
000a50c0
440b0010
014b6027
000c6000
7D4D0002
440a0001
000a50c0
440b0010



4403BABE
4404BEEF
3c05c0de
3c06dead
00a32825
00c43025
00052800
00063000
00A63833
00073000

0000 0000 1010 0110 0011 1000 0011 0011
0000 0000 000

440300B0
440400AB
3c0500B0
3c0600AB
00a32825
00c43025
00052800
00063000
00A63833
00073000






20020005
2003000c
2067fff7
00e22025
00642824
00a42820
10a7000a
0064202a
10800001
20050000
00e2202a
00853820
00e23822
ac670044
8c020050
08000011
20020001
ac020054