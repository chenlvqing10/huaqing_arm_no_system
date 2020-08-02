	.text
	.global _start
_start:

	/* 1. 设置GPIOA28引脚为GPIO功能 */
	@ GPIOAALTFN[25:24] = 00    0xC001A024[25:24] = 00
	ldr r0, =0xC001A024
	ldr r1, [r0]
	bic r1, r1, #(0x3 << 24)
	@ and r1, r1, #(~(0x3 << 24))
	str r1, [r0]

	/* 2. 设置GPIOA28引脚为输出模式 */
	@ GPIOAOUTENB[28] = 1    0xC001A004[28] = 1
	ldr r0, =0xC001A004
	ldr r1, [r0]
	orr r1, r1,#(0x1 << 28)
	str r1, [r0]

loop:
	/* 3. 设置GPIOA28引脚输出高电平 open the led*/
	@ GPIOAOUT[28] = 1    0xC001A000[28] = 1
	ldr r0, =0xC001A000
	ldr r1, [r0]
	orr r1, r1,#(0x1 << 28)
	str r1, [r0]
	bl delay1s

	/* 4. 设置GPIOA28引脚输出低电平 */
	@ GPIOAOUT[28] = 0    0xC001A000[28] = 0
	ldr r0, =0xC001A000
	ldr r1, [r0]
	bic r1, r1,#(0x1 << 28)
	str r1, [r0]
	bl delay1s
	b loop




@ 1s的延时函数
delay1s:
	ldr r3, =0x10000000
	mm:
	cmp r3, #0
	subne r3, r3, #1
	bne mm
	mov pc, lr

	.end
