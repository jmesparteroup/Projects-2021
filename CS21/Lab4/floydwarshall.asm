.eqv INF 0x7fffffff
.eqv i $s0
.eqv jay $s1
.eqv k $s2
.eqv check1 $s3
.eqv check2 $s4
.eqv N 4
.eqv TEMP1 $t0
.eqv TEMP2 $t1
.eqv ELEM1 $t2
.eqv ELEM2 $t3
.eqv ELEM3 $t4
.eqv SWITCH $t5
.eqv arr $t6
.eqv SIZE 4



outer_init:
	li k, 0
	
outer_cond:
	bge k, N, outer_end
	
outer_body:
	
	out_init:
		li i, 0
		
	out_cond:
		bge i, N, out_end
		
	out_body:
	
		inner_init:
			li jay,0
			
		inner_cond:
			bge jay, N, inner_end 
			
		inner_body:
		
			#i,jay
			la SWITCH, matrix
			li TEMP2, 16
			mul TEMP2, i, TEMP2
			mul TEMP1, jay, SIZE
			add TEMP1, TEMP1, TEMP2
			add SWITCH, SWITCH, TEMP1
			lw ELEM1, 0(SWITCH)
			
			#i,k
			la arr, matrix
			li TEMP2, 16
			mul TEMP2, i, TEMP2
			mul TEMP1, k, SIZE
			add TEMP1, TEMP1, TEMP2
			add arr, arr, TEMP1
			lw ELEM2, 0(arr)
			
			#jay,k
			la arr, matrix
			li TEMP2, 16
			mul TEMP2, k, TEMP2
			mul TEMP1, jay, SIZE
			add TEMP1, TEMP1, TEMP2
			add arr, arr, TEMP1
			lw ELEM3, 0(arr)
			
			infinity_check:
				
				seq check1, ELEM2, INF
				seq check2, ELEM3, INF
				
				bgtz check1, mini_else
				bgtz check2, mini_else
			
			
			#no infinities
			add TEMP1, ELEM2, ELEM3
			blt ELEM1, TEMP1, mini_if
			
			mini_else:
				sw TEMP1, 0(SWITCH)
				j inner_incr
			mini_if:
				j inner_incr
			
			
		inner_incr:
			addiu jay, jay,1
			j inner_cond
			
		inner_end:
	out_incr:
		addiu i, i, 1
		j out_cond
		
	out_end:
outer_incr:
	addiu k, k , 1
	j outer_cond
	
outer_end:
	li $v0, 10
	syscall


.data
matrix: .word 0
	.word 3
	.word INF
	.word 5
	.word 2
	.word 0
	.word INF
	.word 4
	.word INF
	.word 1
	.word 0
	.word INF
	.word INF
	.word INF
	.word 2	
	.word 0
