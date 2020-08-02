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

        /* 1. 设置GPIOB12引脚为GPIO功能 */
        @ GPIOxALTFN0[25:24] = 10    0xC001B020[25:24] = 10
        ldr r0, =0xC001B020
        ldr r1, [r0]
        bic r1, r1, #(0x1 << 24)
        orr r1, r1, #(0x1 << 25)
        @ and r1, r1, #(~(0x1 << 25))
        str r1, [r0]

        /* 2. 设置GPIOB12引脚为输出模式 */
        @ GPIOAOUTENB[12] = 1    0xC001B004[12] = 1
        ldr r0, =0xC001B004
        ldr r1, [r0]
        orr r1, r1,#(0x1 << 12)
        str r1, [r0]


loop:
	/* 3. 设置GPIOA28引脚输出高电平 open the red led*/
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
	@bl delay1s

	/* 3. 设置GPIOE13引脚输出高电平 open the green led*/
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
        @bl delay1s

        /* 3. 设置GPIOB12引脚输出高电平 open the blue  led*/
        @ GPIOAOUT[12] = 1    0xC001B000[12] = 1
        ldr r0, =0xC001B000
        ldr r1, [r0]
        orr r1, r1,#(0x1 << 12)
        str r1, [r0]
        bl delay1s

        /* 4. 设置GPIOB12引脚输出低电平 */
        @ GPIOAOUT[12] = 0    0xC001B000[12] = 0
        ldr r0, =0xC001B000
        ldr r1, [r0]
        bic r1, r1,#(0x1 << 12)
        str r1, [r0]
        @bl delay1s
	b loop


@ 1s的延时函数
delay1s:
	ldr r3, =0x005F0000
	mm:
	cmp r3, #0
	subne r3, r3, #1
	bne mm
	mov pc, lr

	.end
