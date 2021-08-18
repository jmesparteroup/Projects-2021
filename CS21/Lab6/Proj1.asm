.eqv COUNTER $t3
.eqv INPUT $t1
.eqv ANSWER $t2


.eqv TEMP $t4
.eqv TEMP1 $t5
.eqv TEMP2 $t6
.eqv bits $t7
.eqv INPUT2 $t8

.macro do_syscall(%n)
li $v0, %n
syscall
.end_macro

start:
	do_syscall(5)
	move INPUT, $v0
	move INPUT2, INPUT
	beqz INPUT, end
	bltz INPUT, negative
	
init:	
	li COUNTER, 1
	li ANSWER, 1
	j cond
negative:
	li ANSWER, 4294967295
	j print

cond:
	beq INPUT, 1, end
	beqz INPUT, end

body:
	srl INPUT,INPUT,1
	addi COUNTER,COUNTER,1
	j cond

end:
	sllv ANSWER, ANSWER, COUNTER
	subi ANSWER, ANSWER, 1
print:
	move $a0, ANSWER
	do_syscall(1)
	
	
	la $a0, newline
	do_syscall(4)
	
#output 2
	li bits, 32
	li $s0, 15
	li TEMP1, 1
	
	and TEMP, INPUT2, $s0
	beqz TEMP, end
	li ANSWER, 4294967295
	
	sub TEMP2, bits, TEMP
	sllv TEMP1, TEMP1, TEMP2
	
	subiu TEMP1, TEMP1, 1
	xor ANSWER, ANSWER, TEMP1
	or ANSWER, ANSWER, TEMP
	
	move $a0, ANSWER
	do_syscall(1)
	
	do_syscall(10)
	
.data
newline: .asciiz "\n"

