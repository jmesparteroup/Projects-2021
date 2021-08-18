.eqv signA $t0
.eqv signB $t1
.eqv expoA $t2
.eqv expoB $t3
.eqv mantA $t4
.eqv mantB $t5
.eqv floatA $t6
.eqv floatB $t7
.eqv expoSum $t8
.eqv signSum $s1
.eqv ANSWER $s2
.eqv TEMP $t9

masks:
	li $s0, 8388607
	
	


init:
	la floatA, f_a
	la floatB, f_b
	
signs:
	bgez floatA, positiveA
	li signA, -1
	
	positiveA: li signA, 1
	
	bgez floatB, positiveB
	li signB, -1
	
	positiveB: li signB, 1
	
exponents:
	nor expoA, floatA, $s0
	nor expoB, floatB, $s0
	
	#smol mantissa manipulation
	xor mantA, floatA, expoA
	xor mantB, floatB, expoB
	
	sll expoA, expoA, 1
	sll expoB, expoB, 1
	
	srl expoA, expoA, 24
	srl expoB, expoB, 24
	
mantissas:
	ori mantA, mantA, 4194304
	ori mantB, mantB, 4194304
	srl mantA, mantA, 1
	srl mantA, mantA, 1
	
step_2:
	move expoSum, expoB
	beq expoA, expoB, step_3
	bgt expoA, expoB, greater_than
	
	sub TEMP, expoB, expoA
	srlv mantA, mantA, TEMP
	
	j step_3
	greater_than:
		move expoSum, expoA
		sub TEMP, expoA, expoB
		srlv mantB, mantB, TEMP
	
	
step_3:
	bgtz signA, check_b
	not mantA, mantA
	addi mantA, mantA, 1
	
	check_b:
	bgtz signB, step_4
	not mantB, mantB
	addi mantB, mantB, 1
	
step_4:
	add mantA, mantA, mantB
	
	bgez mantA, positive
	#if negative flip
	li signSum, -1
	not mantA, mantA
	addi mantA, mantA, 1
	
	positive:
	j step_5
	
step_5:
	li TEMP, 0
	while:
		bge mantA, 4194304, step_6
		
		sll mantA, mantA, 1
		addi TEMP, TEMP, 1
		
		j while
step_6:
	sub expoSum, expoSum, TEMP
	sll expoSum, expoSum, 22
	
	or ANSWER, expoSum, mantA 
	
	bgez signSum, positive1
	
	#else
	ori ANSWER, -2147483648
	
	positive1:
	sw ANSWER, f_c
	
	
		
	
	
	
	
	
	

	
	
	





.data:
f_a: .float 3.75
f_b: .float -5.125
f_c: