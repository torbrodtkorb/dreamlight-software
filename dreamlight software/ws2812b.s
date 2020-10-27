@ Copyright (C) Tor Brodtkorb 

.syntax unified
.cpu cortex-m7
.thumb


PIOD_START = 0x400E1400
SET_OFFSET = 0x30
CLEAR_OFFSET = 0x34



// void ws2812b_draw(void* addr, u32 leds, void* port, u32 pin)
.global ws2812b_draw
.type ws2812b_draw, %function
ws2812b_draw:
	
	stmdb sp!, {r4 - r6}

	mov r4, #1
	lsl r4, r4, r3
loop:
	str r4, [r2, #SET_OFFSET]

	ldr r5, = 50000
1:
	subs r5, r5, #1
	bne 1b

	str r4, [r2, #CLEAR_OFFSET]
		ldr r5, = 50000
1:
	subs r5, r5, #1
	bne 1b
	b loop

	ldmia sp!,  {r4 - r6}
	bx lr
