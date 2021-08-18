main:
	li $t1, 7
	xor $t1, $t1, 1
	b some_label
	
some_label:
	li $v0, 10
	syscall
