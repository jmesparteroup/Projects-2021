.text
main:
	la $t5, arr  #load array to $t5
	subiu $sp, $sp, 12 #initialie stack to be 3 words worth
	li $t0, 1	# initialize $t0 to 1 i = 1
	sw $t0, 0($sp) # store stack [0], stack[0] = i
	li $t0, 8	# initialize $t0 to 8
	sw $t0, 8($sp) # store to stack [2]
L0:
	lw $t0, 0($sp) # $t0 gets stack [0] - 1
	lw $t1, 8($sp) # $t1 gets stack [2] - 8 (length A)
	bge $t0, $t1, L3 # if t0 >= t1 go to L3  | i < length(A)
	lw $t0, 0($sp) # t0 = i
	sw $t0, 4($sp) # stack [1] = stack [0] || j = i
L1:
	lw $t0, 4($sp) # t0 = stack[1]
	blez $t0, L2  # if t0 (stack[1]) <= 0 go to L2
	subiu $t1, $t0, 1 # t1 = t0 (stack[1]) - 1
	mul $t1, $t1, 4 # continues to t1 = 4*(stack[1] -1)
	add $t1, $t1, $t5 # continues to t1 = 4*(stack[1] -1) + *arr
	lw $t3, 0($t1) # t3 = arr[j-1]
	mul $t2, $t0, 4 
	add $t2, $t2, $t5 # t2 = 4*(stack[1]) + *arr
	lw $t4, 0($t2) # t4 = arr[j]
	ble $t3, $t4, L2 # if arr[j-1] <= arr[j] go to L2
	xor $t3, $t3, $t4
	xor $t4, $t3, $t4
	xor $t3, $t3, $t4 # swap arr[j] and arr[j-1] through registers
	sw $t3, 0($t1)
	sw $t4, 0($t2) #saving the values to the .data segment
	lw $t0, 4($sp)
	subiu $t0, $t0, 1 #j = j-1
	sw $t0, 4($sp) #stack[1] = j
	j L1
L2:
	lw $t0, 0($sp) #t0 = i
	addiu $t0, $t0, 1 # t0 ++
	sw $t0, 0($sp) # i goes back to the stack
	j L0
L3:
	addiu $sp, $sp, 12 #deallocate stack
	li $v0, 10 #bye bye
	syscall
	
.data
arr: 	.word 1
	.word -1
	.word -10
	.word 12
	.word 100
	.word -100
	.word 1
	.word 6
