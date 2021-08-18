# CS 21 A-2 -- S2 AY 2020-2021
# Joshua Allyn Marck M. Espartero -- 05/05/21
# BinaryTree.asm -- Lab 7 

.eqv a $t0
.eqv be $t1
.eqv c $t2
.eqv d $t3
.eqv e $t4 
.eqv f $t5
.eqv g $t6
.eqv h $t7
.eqv i $t8
.eqv ja $t9
.eqv NULL $zero



.macro do_syscall(%n)
	li $v0, %n
	syscall
.end_macro

.macro NewNode(%r, %d)
	li	$a0, %d
	jal	new_node
	move	%r, $v0
.end_macro 

.macro Linked(%a, %b, %c)
	move	$a0, %a
	move	$a1, %b
	move	$a2, %c
	jal	link
.end_macro


main:

	NewNode($t0, 5)
	NewNode($t1, 10)
	NewNode($t2, 17)
	NewNode($t3, 1)
	NewNode($t4, 0)
	NewNode($t5, 10)
	NewNode($t6, 12)
	NewNode($t7, 1)
	NewNode($t8, 2)
	NewNode($t9, 15)
	
	
	Linked(a, be, c)
	Linked(be, d, e)
	Linked(c, f, g)
	Linked(d, NULL, NULL)
	Linked(e, NULL, NULL)
	Linked(f, h, i)	
	Linked(g, ja, NULL)
	Linked(h, NULL, NULL)
	Linked(i, NULL, NULL)
	Linked(ja, NULL, NULL)	
	
	move	$a0, a
	jal	depth
	move	$a0, $v0
	do_syscall(1)
	
	li	$a0, 45
	do_syscall(11)
	
	move	$a0, a
	li	$a1, 0
	jal	even_level_max
	move	$a0, $v0
	do_syscall(1)

	do_syscall(10)

new_node: 
	subi $sp, $sp, 8
	sw $a0, 0($sp)
	sw $s0, 4($sp)
	
	move $s0, $a0
	li $a0, 12
	do_syscall(9)
	sw $s0, 0($v0)
	
	lw $a0, 0($sp)
	lw $s0, 4($sp)
	addiu $sp, $sp, 8
	jr $ra

link: 	sw $a1, 4($a0)
	sw $a2, 8($a0)
	jr $ra
	
depth: 	subiu $sp, $sp, 16
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $ra, 12($sp)

	bnez $a0, C0
	li $v0, -1
	j C2
C0: 
	move $s0, $a0
	lw $a0, 4($s0)
	jal depth
	move $s1, $v0
	lw $a0, 8($s0)
	jal depth
	move $s2, $v0
	li $v0, 1
	bgt $s1, $s2, C1
	add $v0, $v0, $s2
	j C2
C1:	add $v0, $v0, $s1
	j C2
C2:
	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $ra, 12($sp)
	addi $sp, $sp, 16
	jr $ra
	

even_level_max: #a0 = *root, a1 = level

	subiu $sp, $sp, 32
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $s3, 12($sp)
	sw $s4, 16($sp)
	sw $s5, 20($sp)
	sw $ra, 24($sp)
	sw $a1, 28($sp)
	
	li $s6, 2
	
	bnez $a0, E0		#if root == null:
	li $v0,  0x80000000
	j E5 
	
E0:	move $s0, $a0		#save copy of root
	move $s1, $a1		#save copy of level
	addi $a1, $a1, 1	#level ++
	lw $a0, 4($s0)		# root-> left
	jal even_level_max	
	move $s2, $v0		#s2 = left
	lw $a0, 8($s0)		# root -> right
	jal even_level_max	
	move $s3, $v0		#s3 = right
	bgt $s2, $s3, E1	# left > right? greater  == left
	move $s4, $s3		# else: greater == right
	j E2
E1:	move $s4, $s2		
E2:	
	div $s1, $s6		
	mfhi $s7		
	bnez $s7, E4		# level % 2 == 0? return greater
	lw $s5, 0($s0)		# s5 = root.data
	bgt $s4, $s5, E3	# greater > root.data? return greater
	move $v0, $s5		# else: return root.data
	j E5
E3:	move $v0, $s4
	j E5
E4:	move $v0, $s4
E5:	
	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $s3, 12($sp)
	lw $s4, 16($sp)
	lw $s5, 20($sp)
	lw $ra, 24($sp)
	lw $a1, 28($sp)
	addi $sp, $sp, 32
	jr $ra	
	
