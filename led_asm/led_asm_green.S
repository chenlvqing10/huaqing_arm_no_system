	.text
	.global _start
_start:

	/* 1. 设置GPIOE13引脚为GPIO功能 */
	@ GPIOxALTFN0[27:26] = 00    0xC001E020[27:26] = 00
	ldr r0, =0xC001E020
	ldr r1, [r0]
	bic r1, r1, #(0x3 << 27)
	@ and r1, r1, #(~(0x3 << 27))
	str r1, [r0]

	/* 2. 设置GPIOE13引脚为输出模式 */
	@ GPIOAOUTENB[13] = 1    0xC001E004[13] = 1
	ldr r0, =0xC001E004
	ldr r1, [r0]
	orr r1, r1,#(0x1 << 13)
	str r1, [r0]

loop:
	/* 3. 设置GPIOE13引脚输出高电平 open the led*/
	@ GPIOAOUT[13] = 1    0xC001E000[13] = 1
	ldr r0, =0xC001E000
	ldr r1, [r0]
	orr r1, r1,#(0x1 << 13)
	str r1, [r0]
	bl delay1s

	/* 4. 设置GPIOE13引脚输出低电平 */
	@ GPIOAOUT[13] = 0    0xC001E000[13] = 0
	ldr r0, =0xC001E000
	ldr r1, [r0]
	bic r1, r1,#(0x1 << 13)
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
