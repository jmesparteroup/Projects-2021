# CS 21 A-2 -- S2 AY 2020-2021
# JoshuaA Allyn Marck M. Espartero -- 11/04/21
# cs21me6a.asm -- Lab 5 Factorial Recursion Algorithm

.eqv ARG	$a0
.eqv RESULT	$v0


.text


.macro do_syscall(%n)
	li $v0, %n
	syscall
.end_macro


main:
	do_syscall(5)
	move ARG, $v0
	jal Derange
	move ARG, $v0
	do_syscall(1)
	do_syscall(10)


Derange: #####preamble######
	subu $sp, $sp, 32
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $s0, 8($sp)
	#####preamble######
	
	beqz ARG, base_case1
	beq ARG, 1, base_case2
	beq ARG, 2, base_case3
	j else
	
	
	base_case1:
		li RESULT, 0
		j  End
	base_case2:
		li RESULT, 0
		j  End
	base_case3:
		li RESULT, 1
		j  End
	else:
	
	subu ARG, ARG, 1
	jal Derange
	move $s0, RESULT
	
	subu ARG, ARG, 1
	jal Derange
	add RESULT, RESULT, $s0
	
	addu ARG, ARG, 1
	mul RESULT, RESULT, ARG
	
	
End:	 #####end######
	lw $ra, 0($sp)
	lw $a0, 4($sp)
	lw $s0, 8($sp)
	addu $sp, $sp, 32
	#####end######
	jr $ra
