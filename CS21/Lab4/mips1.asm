.eqv CONST_ARR1_LEN 16
.eqv CONST_ARR2_LEN 4
.eqv CONST_ELEM_SIZE 1
.eqv TEMP $t0
.eqv P $t1
.eqv ELEM1 $t2
.eqv ELEM2 $t3
.eqv ARR1 $t4
.eqv ARR2 $t5
.eqv I $t6
.eqv K $t7
.eqv LEN $t8
.eqv FOUND $t9
.macro do_syscall(%n)
li $v0, %n
syscall
.end_macro
.data
arr1: .asciiz "bababacabaatest!"
arr2: .asciiz "abcd"
