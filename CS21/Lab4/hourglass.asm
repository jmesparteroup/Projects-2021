.eqv N $s0
.eqv size $t0
.eqv row $t1
.eqv col $t2
.eqv TEMP $t3
.eqv TEMP1 $t4
.eqv CondCheck1 $t5
.eqv CondCheck2 $t6
.eqv CondCheck3 $t7
.eqv TEMP2 $s1

.macro do_syscall(%n)
li $v0, %n
syscall
.end_macro



main:
	do_syscall(5)
	move N, $v0
	

outerInit:
	move TEMP, N 
	sll TEMP, TEMP, 1
	addiu TEMP, TEMP, 2
	move size, TEMP
	
	li row, 0
    
outerCond:
	bgt row, size, outerEnd

outerBody:

    innerInit:
    	li col, 0

    innerCond:
    	bgt col, size, innerEnd

    innerBody:
    	
    	beqz row, if
    	beq size, row, if
    	j elseIfOneCond
    	
    	if:
    		beq size, col, innerIf
    		beqz col, innerIf
    		
    		innerElse:
    			la $a0, dash
    			do_syscall(4)
    			j innerIncr	
    				    		
    		innerIf:
    			la $a0, O
    			do_syscall(4)
    			j innerIncr
   	
   	elseIfOneCond:
   		beq col, row, elseIfOne
   		j elseIfTwoCond
   		
    	elseIfOne:
    		move TEMP2, N
    		addiu TEMP2,TEMP2, 1
    		bne TEMP2, row, miniElse
    		
    		miniIf:
    			la $a0, X
    			do_syscall(4)
    			j innerIncr
    		miniElse:
    			la $a0, backslash
    			do_syscall(4)
    			j innerIncr
    		
    	
    	elseIfTwoCond:
    		move TEMP, size
    		sub TEMP, TEMP, row
    		beq TEMP, col, elseIfTwo
    		j elseIfThreeCond
    		
    	elseIfTwo:
    		la $a0, frontslash
    		do_syscall(4)
    		j innerIncr	
    	
    	elseIfThreeCond:
    		slt CondCheck1, col, row
    		slt CondCheck2, TEMP, col
    		
    		and CondCheck1, CondCheck1, CondCheck2
    		move TEMP2, N
    		addiu TEMP2,TEMP2, 1
    		sgt CondCheck2, row, TEMP2
    		
    		and TEMP1, CondCheck1, CondCheck2
    		bgtz TEMP1, elseIfThree
    		 
    		j elseIfFourCond
    	elseIfThree:
    		la $a0, period
    		do_syscall(4)
    		j innerIncr	
    	
    	elseIfFourCond:
    		blt col, TEMP, elseIfFour
    		j innerIncr
    		
    	elseIfFour:
    		la $a0, space
    		do_syscall(4)
    		j innerIncr

    innerIncr:
	addi col, col, 1
	j innerCond
    innerEnd:
    	la $a0, newline
    	do_syscall(4)	

outerIncr:
	addiu row, row, 1
	j outerCond

outerEnd:
	do_syscall(10)


.data

data:
X: .asciiz "X"
backslash: .asciiz "\\"
frontslash: .asciiz "/"
O: .asciiz "o"
period: .asciiz	"."
space: .asciiz " "
dash: .asciiz  "-"
newline: .asciiz "\n"
