@ Copyright (C) Tor Brodtkorb 

.syntax unified
.cpu cortex-m7
.thumb


SET_OFFSET = 0x30           @ Offset to set a pin
CLEAR_OFFSET = 0x34         @ Offset to clear a pin

T0H = 1
T1H = 140
T0L = 140
T1L = 1
RESET = 15000


@ void ws2812b_draw(void* addr, u32 leds, void* port, u32 pin)
.global ws2812b_draw
.type ws2812b_draw, %function
ws2812b_draw:                           @ Start the function, Paremeter the function takes get stored in register r0 - r3 
	
	stmdb sp!, {r4 - r9, lr}			@ r4 to stack
	mov r4, r0                          @ r4 holds the address

	mov r5, #1
	lsl r5, r5, r3                      @ r5 holds the pin mask

	
	mov r3, #3
	mul r1, r1, r3                      @ r1 holds the number of bytes to send
1:
	@ send one byte
	ldrb r6, [r4], #1                   @ Holds the byte to send 
	mov r7, #0x80                       @ Bitmask for byte MSB
	mov r8, #8                          @ Holds the inner loop count
2:
	ands r9, r6, r7					


	@ Set pin + delay
	str r5, [r2, #SET_OFFSET]           @ Set the pin
	ite eq
	moveq r0, #T0H
	movne r0, #T1H
	bl delay_cycles

	str r5, [r2, #CLEAR_OFFSET]         @ Clear the pin

	cmp r9, #0
	ite eq
	moveq r0, #T0L
	movne r0, #T1L
	bl delay_cycles

	lsl r6, r6, #1 

	subs r8, r8, #1
	bne 2b                              @ Branch to bit loop
	subs r1, r1, #1
	bne 1b                              @ Branch to byte loop

	@ Send the reset sequence -50us
	ldr r0, =RESET
	bl delay_cycles


	ldmia sp!, {r4 - r9, lr}

	bx lr

@ void delay_cycles(u32 cycles)
.type delay_cycles, %function
delay_cycles:
	subs r0, r0, #1
	bne delay_cycles
	bx lr
