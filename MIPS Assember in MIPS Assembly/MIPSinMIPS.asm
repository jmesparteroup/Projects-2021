.eqv N 			$t9
.eqv counter 		$t8
.eqv PC 		$t7
.eqv memory		$t6
.eqv offset		$t5
.eqv registers		$t4
.eqv aluOut		$t3
.eqv TEMP		$t2
.eqv startmem		$t1
.eqv instructions	$t0
.eqv opcode		$s0
.eqv rs			$s1
.eqv rt			$s2
.eqv rd			$s3
.eqv imm		$s4
.eqv funct		$s5
.eqv beqRt		$s6
.eqv printX		$s7		
.eqv opcodeMask 	0xFC000000
.eqv rsMask 		0x03E00000
.eqv rtMask 		0x001F0000
.eqv rdMask 		0x0000F800
.eqv functMask 		0x3F
.eqv addressMask 	0x3FFFFFF
.eqv immMask 		0xFFFF

.macro do_syscall(%n)
	li 	$v0, %n
	syscall
.end_macro

.macro allocateMemory(%n, %x)
	li 	$a0, %x
	do_syscall(9)
	move 	%n, $v0
.end_macro

.macro printInt(%d)
	move 	$a0, %d
	do_syscall(1)
.end_macro

.macro printChar(%c)
	move 	$a0, %c
	do_syscall(11)
.end_macro

	########################################################################################
	
	# 				GENERAL FLOW OF MIPS IN MIPS CODE
	#
	# (1) ALLOCATE HEAP FOR REGISTERS ARRAY AND MEMORY OF SIMULATION
	# (2) ACCEPT N ; ACCEPT INSTRUCTIONS J
	# (3) HANDLE READING INSTRUCTIONS
	#	i.	WHILE LOOP READING INSTRUCTIONS (until syscall(10))
	#	ii.	BITMASK TO GRAB PARTS OF THE INSTRUCTION (I.E FUNCT, OPCODE, RS, RT, IMM)
	#	iii. 	CHECK WHICH KIND OF INSTRUCTION (I, R, J, OR JAL)
	#	iv.	FURTHER CHECK WHICH KIND OF INSTRUCTION IF I-TYPE OR R-TYPE
	#	vi. 	HANDLE THE IMPLEMENTED INSTRUCTIONS
	#	vii. 	DO POINTER ARITHMETIC TO MOVE THROUGH THE INSTRUCTIONS ARRAY
	#
	# SOME NOTES FOR ME:
	#	1)POINTER ARITHMETIC TO READ/WRITE TO SIMULATION REGISTERS AND MEMORY
	#	2)SAVE /NOTE THE STARTING ADDRESS OF INSTRUCTIONS/REGISTERS/MEMORY 
	#	3)USE .EQVs TO MAKE CODE MORE INTUITIVE
	#	4)USE BRAIN WELL
	
	########################################################################################

start:	#START OF SIMULATION	
	do_syscall(5)				#ACCEPT INTEGER
	move 	N, $v0
	allocateMemory(registers, 132) 		# allocate heap to registers
	allocateMemory(memory, 0x100000) 	# set starting point of memorry
	move 	startmem, memory 		# store the start of the memory
	li 	TEMP, 0x20000 			# set the offset of SP 
	sw 	TEMP, 116(registers) 		# store into register[31] 116=31*4
	move 	instructions, memory		# initialize instructions array pointer
	
inputRead:
	do_syscall(5) 				# ACCEPT INTEGER
	move 	$a0, $v0			# 
	sw 	$a0, (instructions)		# store integer to instructions[i] where i = [0,1,2,3...]
	
	addiu 	instructions, instructions, 4	# move instructions pointer to next address
	addiu 	counter, counter, 1		# add one to our counter variable
	bne 	counter, N, inputRead		# if counter != N, continue accepting
	move 	instructions, startmem		# reset instructions pointer to the instructions[0]
	
	li 	counter, 0			# reset counter variable

convert: 
	#INSTRUCTION LOADING
	lw 	$a0, (instructions)		# store the i-th instruction in $a0
	andi 	opcode, $a0, opcodeMask		# do bitmasking to retrieve the opcode
	do_syscall(34)
	
	#TYPE CHECKING				# we check what kind of instruction it is 
	beq 	$a0, 0xC, sys			# if $a0 = 12, then go to syscall
	beq 	opcode, 0, rtype		# if opcode = 0, go to R TYPE HANDLING
	beq 	opcode, 0x8000000, jtype 	# if opcode = 0x8000000, go to J PROCEDURE
	beq 	opcode, 0xC000000, j1		# if opcode = 0xC000000, go to JAL PROCEDURE
	j 	itype				# else, it is a j-type instruction 
	
sys:	#SYSCALL PROCEDURE
	lw 	TEMP, 8(registers) 		# load registers[2] ($v0)
	beq 	TEMP, 1, s1			# if $v0 = 1: go to PRINT INTEGER (s1)
	beq 	TEMP, 10, s2			# if $v0 = 10: go to EXIT(0) (s2)
	beq 	TEMP, 11, s3			# if $v0 = 11: go to PRINT CHARACTER (s3)
	j 	while				# else go to while
	
s1:	#PRINT INTEGER PROCEDURE	
	lw 	printX, 16(registers)		# load registers[4] ($a0)
	printInt(printX)			# call macro printInt
	j 	while				# go to while
	
s2:	#EXIT(0) PROCEDURE
	do_syscall(10)				# call syscall 10 using do_syscall macro

s3:	#PRINT CHARACTER PROCDEDURE		
	lw 	printX, 16(registers)		# load registers[4] ($a0)
	printChar(printX)			# call macro printChar
	j	while				# go to while

rtype:	# R TYPE HANDLING

	# MASKING AND PREPROCESSING
	andi 	rs, $a0, rsMask			# grab rs using rsMask
	andi 	rt, $a0, rtMask			# grab rt using rtMask
	andi 	rd, $a0, rdMask			# grab rd using rdMask
	andi 	funct, $a0, functMask		# grab funct using functMask
	
	# BIT-SHIFTING WITH *4 LOOK-AHEAD FOR ACCESSING REGISTERS (WORD-ALIGNED)
	srl 	rs, rs, 19 			# 21-2 move 21 to right then move 2 to the left (times 4)
	srl 	rt, rt, 14 			# 16-2 move 16 to right then move 2 to the left (times 4)
	srl 	rd, rd, 9  			# 11-2 move 11 to right then move 2 to the left (times 4)

	# POINTER ARITHMETIC TO SET RS, RT, AND RD AS POINTERS TO THEIR CORRESPONDING REGISTERS
	add 	rs, rs, registers
	add 	rt, rt, registers
	add 	rd, rd, registers

	# DEREFERENCE RS AND RT 		
	lw 	rs, (rs)
	lw 	rt, (rt)
	# NOTE: RD STAYS AS A POINTER		

	# CHECK R-TYPE INSTRUCTION TYPE
	beq 	funct, 0x08, j2			# IF FUNCT = b'001000: go to JR PROCEDURE
	beq 	rd, 0, while			# IF TRYING TO WRITE TO $0 REGISTER, SKIP
	beq 	funct, 0x20, r1			# IF FUNCT = b'100000: go to ADD PROCEDURE
	beq 	funct, 0x22, r2			# IF FUNCT = b'100010: go to SUB PROCEDURE
	beq 	funct, 0x24, r3			# IF FUNCT = b'100100: go to AND PROCEDURE
	beq 	funct, 0x25, r4			# IF FUNCT = b'100101: go to OR PROCEDURE
	beq 	funct, 0x2A, r5			# IF FUNCT = b'101010: go to SLT PROCEDURE
	j 	while				# go to while

	
	
r1: 	# ADD PROCEDURE
	add 	TEMP, rs, rt			# ADD RS AND RT
	sw 	TEMP, (rd)			# STORE SUM INTO ADDRESS OF RD REGISTER
	j 	while				# go to while

r2: 	# SUB PROCUDURE
	sub 	TEMP, rs, rt			# SUBTRACT RT from RS
	sw 	TEMP, (rd)			# STORE DIFFERENCE INTO ADDRESS OF RD REGISTER		
	j 	while				# go to while
	
r3: 	# AND PROCEDURE
	and 	TEMP, rs, rt			# PERFORM BIT-WISE AND ON RS AND RT
	sw 	TEMP, (rd)			# STORE OUTPUT INTO ADDRESS OF RD REGISTER
	j 	while				# go to while

r4: 	# OR PROCEDURE
	or 	TEMP, rs, rt			# PERFORM BIT-WISE OR ON RS AND RT
	sw 	TEMP, (rd)			# STORE OUTPUT INTO ADDRESS OF RD REGISTER
	j 	while				# go to while
	
r5: 	# SLT PROCEDURE
	slt 	TEMP, rs, rt			# IF RS < RT ? 1 : 0
	sw 	TEMP, (rd)			# STORE OUTPUT INTO ADDRESS OF RD REGISTER
	j 	while				# go to while

jtype: 	# J PROCEDURE
	andi 	PC, $a0, addressMask		# GRAB THE ADDRESS FROM THE INSTRUCTION USING addressMask
	j 	setNext				# handle the bit shifting in setNext


j1: 	# JAL PROCEDURE
	addi 	TEMP, PC, 1			# CALCULATE (PC+1)4
	sll	TEMP, TEMP, 2			# 
	sw 	TEMP, 124(registers) 		# THEN STORE AT REGISTERS[31] ($ra)
	andi 	PC, $a0, addressMask		# GRAB ADDRESS OF FUNCTION USING addressMarsk
	j 	setNext				# handle bit shifting in setNext

j2: 	# JR PROCEDURE
	srl	TEMP, rs, 2	
	move 	PC, TEMP			# SET PC TO $rs
	j 	setNext				# handle bit shifting in setNext

itype: 	# I TYPE HANDLING

	# MASKING AND PREPROCESSING
	andi 	rs, $a0, rsMask			# GRAB RS USING rsMask
	andi 	rt, $a0, rtMask			# GRAB RT USING rtMask
	andi 	imm, $a0, immMask		# GRAB IMM USING immMask
	
	# CHECKING FOR NEGATIVE IMMs
	bge 	imm, 0x00008000, immNeg		# IF LEADING BIT OF IMM = 'b1
	j 	iB				# ELSE PROCEED
	
immNeg:	# SIGNEXTENDING NEGATIVE IMMs
	ori 	imm, imm, 0xFFFF0000		# PERFORMING BITWISE OR TO EXTEND NEGATIVE IMM
	j 	iB				# PROCEED

iB:	
	# BIT-SHIFTING WITH *4 LOOK-AHEAD FOR ACCESSING REGISTERS (WORD-ALIGNED)
	srl 	rs, rs, 19 			# 21-2	SHIFT RIGHT 21 TIMES AND 2 TIMES TO THE LEFT (TIMES 4)	
	srl 	rt, rt, 14 			# 16-2  SHIFT RIGHT 14 TIMES AND 2 TIMES TO THE LEFT (TIMES 4)	

	# POINTER ARITHMETIC FOR RS AND RT
	add 	rs, rs, registers		# SETS RS TO BE THE POINTER TO REGISTERS[RS]			
	add 	rt, rt, registers		# SETS RT TO BE THE POINTER TO REGISTERS[RT]

	# DERERENCING POINTERS TO ACCESS VALUES
	lw 	rs, (rs)			# SETS RS TO BE THE DEREFERENCED RS
	lw 	beqRt, (rt)			# SETS BEQRT TO BE THE DEREFERENCED RT (TO BE USED IN BEQ)
						# NOTE: BEQRT != RT; RT IS STILL NOT DEREFERENCED
	
	# I-TYPE INSTRUCTION TYPE CHECKING
	beq 	rt, 0, while			# IF TRYING TO EDIT $0 THEN PASS
	beq 	opcode, 0x24000000, i1		# IF OPCODE = 0x24000000: PROCEED TO ADDIU PROCEDURE
	beq 	opcode, 0x10000000, i2		# IF OPCODE = 0x10000000: PROCEED TO BEQ PROCEDURE
	beq 	opcode, 0x8c000000, i3		# IF OPCODE = 0x8c000000: PROCEED TO LW PROCEDURE
	beq 	opcode, 0xac000000, i4		# IF OPCODE = 0x8c000000: PROCEED TO SW PROCEDURE
	beq	opcode, 0x14000000, i5		# IF OPCODE		: PROCEED TO BNE PROCEDURE
	j 	while				# else go to while

i1: 	# ADDIU PROCEDURE
	addu	TEMP, rs, imm			# ADD RS AND SIGNEDIMM
	sw	TEMP, 0(rt)			# STORE SUM INTO REGISTERS[RT]
	j 	while				# go to while

i2: 	# BEQ PROCEDURE
	bne 	rs, beqRt, while		# IF RS != BEQRT, NO BRANCHING WILL BE DONE
	add 	PC, PC, imm			# ELSE: ADD IMM TO PC (+1 will handled in while)
	j 	while				# GO TO WHILE
	
i3: 	# LW PROCEDURE
	add 	rs, rs, imm			# ADDING OFFSET TO THE ADDRESS IN RS
	add 	rs, rs, memory			# SETTING RELATIVE OFFSET
	lw 	TEMP, (rs)			# LOADING THE ADDRESS WE'VE CALCULATED
	sw 	TEMP, (rt)			# STORING DATA INTO REGISTERS[RT]
	j	while				# go to while
	
i4: 	# SW PROCEDURE
	add 	rs, rs, imm			# ADDING OFFSET TO THE ADDRESS IN RS
	add 	rs, rs, memory			# SETTING RELATIVE OFFSET
	lw 	TEMP, (rt)			# LOADING DATA FROM REGISTER[RT]
	sw	TEMP, (rs)			# STORING DATA IN TO THE ADDRESS WE'VE CALCULATED
	j 	while				# go to while
	
i5: 	# BNE PROCEDURE
	beq 	rs, beqRt, while		# IF RS != BEQRT, NO BRANCHING WILL BE DONE
	add 	PC, PC, imm			# ELSE: ADD IMM TO PC (+1 will handled in while)
	j 	while				# GO TO WHILE
	

while:
	addiu 	PC, PC, 1			# PC = PC + 1
setNext:
	la $a0, newline
	do_syscall(4)
	
	move 	instructions, startmem			# *INSTRUCTIONS = INSTRUCTIONS[0]
	sll	offset, PC, 2				# PC = PC*4 (SINCE WORD ALIGNED INSTRUCTIONS ARRAY)
	add	instructions, instructions, offset	# *INSTRUCTIONS = INSTRUCTIONS[PC]
	j convert				# WHILE PC in TEXT SEGMENT KEEP ON CONVERTING


.data
data:
newline: .asciiz "\n"	
