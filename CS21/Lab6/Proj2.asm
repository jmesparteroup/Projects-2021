.eqv INPUT $t1
.eqv ANSWER $t2
.eqv TEMP $t3
.eqv TEMP1 $t4
.eqv TEMP2 $t5
.eqv bits $t6

.macro do_syscall(%n)
li $v0, %n
syscall
.end_macro

main:
	do_syscall(5)
	move INPUT, $v0
	
	li bits, 32
	li $t8, 15
	li TEMP1, 1
	
	and TEMP, INPUT, $t8
	beqz TEMP, end
	li ANSWER, 4294967295
	
	sub TEMP2, bits, TEMP
	sllv TEMP1, TEMP1, TEMP2
	
	subiu TEMP1, TEMP1, 1
	xor ANSWER, ANSWER, TEMP1
	or ANSWER, ANSWER, TEMP
	
	
	
end:
	move $a0, ANSWER
	do_syscall(1)
	do_syscall(10)
	