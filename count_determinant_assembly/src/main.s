.text
.global count_det


count_det:
	ldr r1, [r0, #16]
	ldr r2, [r0, #32]
	mul r1, r2, r1
	ldr r2, [r0, #28]
	ldr r3, [r0, #20]
	mul r2, r3, r2
	subs r1, r1, r2
	ldr r2, [r0, #0]
	mul r1, r2, r1
	ldr r2, [r0, #12]
	ldr r3, [r0, #32]
	mul r2, r3, r2
	ldr r3, [r0, #20]
	ldr r4, [r0, #24]
	mul r3, r4, r3
	subs r2, r2, r3
	ldr r3, [r0, #4]
	mul r2, r3, r2
	subs r1, r1, r2
	ldr r2, [r0, #12]
	ldr r3, [r0, #28]
	mul r2, r3, r2
	ldr r3, [r0, #16]
	ldr r4, [r0, #24]
	mul r3, r4, r3
	subs r2, r2, r3
	ldr r3, [r0, #8]
	mul r2, r3, r2
	add r1, r2, r1	
	mov r0, r1
	bx lr

