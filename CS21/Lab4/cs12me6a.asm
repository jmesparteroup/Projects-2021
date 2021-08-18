# CS 21 A-2 -- S2 AY 2020-2021
# JoshuaA Allyn Marck M. Espartero -- 11/04/21
# cs21me6a.asm -- Lab 5 Factorial Recursion Algorithm


.macro do_syscall(%n)
li $v0, %n
syscall
.end_macro


.text
main: 	do_syscall(5)
	move $a3, $v0	#set N to the argument of the function
	li $v1, 1 # v1 base case return value
	jal fact
	
	move $a0, $v1
	do_syscall(1)
	do_syscall(10)

fact:	#preamble#
	subu $sp, $sp, 32
	sw $ra, 0($sp)
	#preamble#
	
	beqz $a3, end_fact
	
	move $a0, $a3 
	move $a1, $v1 
	li $v0, 0 
	jal mul_alt 
	move $v1, $v0
	subi $a3, $a3, 1
	
fact_rec: jal fact

end_fact:
	lw $ra, 0($sp)
	addu $sp, $sp, 32
	
	jr $ra
	
mul_alt: #####preamble######
	subu $sp, $sp, 32
	sw $ra, 0($sp)
	#####preamble######
	
	beqz $a1, bc 
	add $v0, $a0, $v0
	subi $a1, $a1, 1
	j recurse

recurse: jal mul_alt
bc:	 #####end######
	lw $ra, 0($sp)
	addu $sp, $sp, 32
	#####end######
	jr $ra
