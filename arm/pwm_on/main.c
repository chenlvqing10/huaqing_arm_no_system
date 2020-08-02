#include <s5p6818.h>
// 寄存器的声明
typedef enum{
	PWM_OFF = 0,
	PWM_ON,
}stu_t;

/*set delay time with for cycle*/
void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	//delay time = ms*1800
	for(i = 0; i < ms; i++)
		for(j = 0; j < 1800; j++);
}

void hal_pwm_init()
{
	/*1.将GPIOC14设置成PWM2(Func2)  [29::28] 10功能 - GPIOCALTFN0*/
	GPIOC.ALTFN0 |= (0x1 << 29);
	GPIOC.ALTFN0 &= ~(0x1 << 28);

	/*2.设置PWM2的一级分频 - TCFG0[15:8] = 249 =0xF9 = 1111 1010*/
	PWM.TCFG0 |= (0xF9 << 8);

	/*3.设置PWM2的二级分频 - TCFG1 TCFG1[11:8] = 1/2 =0001 地址=0xC0018004*/
	/*
	PWM.TCFG1 &= ~(0x1 << 11);
	PWM.TCFG1 &= ~(0x1 << 10);
	PWM.TCFG1 &= ~(0x1 << 9);
	PWM.TCFG1 |=  (0x1 << 8);
	*/
	//0010 1/4
	PWM.TCFG1 |= (0x1 << 11);
	PWM.TCFG1 &= ~(0x1 << 10);
	PWM.TCFG1 &= ~(0x1 << 9);
	PWM.TCFG1 &= ~(0x1 << 8);

	/*4.设置PWM2的周期值 - TCNTB2 TCNTB2[31:0] = 299 =0x12B 地址=0xC0018024  1000HZ  T=1ms*/
	PWM.TCNTB2 = 299;
 
	/*5.设置高电平的时间 - TCMPB2  占空比50% TCMPB2[31:0] = 149 =0x95 地址=0xC0018028*/
	PWM.TCMPB2 = 149;
	/*6.打开手动装载将TCNTB2中的值加载到TCNTO2递减计数器 - TCON TCON[13]=1  地址=0xC0018008*/
	PWM.TCON |= (0x1 << 13);
	/*7.关闭手动装载后续的周期使用自动装载 - TCON TCON[13]=0  地址=0xC0018008*/
	PWM.TCON &= ~(0x1 << 13);
	/*8.打开自动装载，使后续产生连续的波形 - TCON TCON[15]=1  地址=0xC0018008*/
	PWM.TCON |= (0x1 << 15);
	/*9.根据需求选择正向/反向输出 - TCON  TCON[14]=1  地址=0xC0018008*/
	PWM.TCON |= (0x1 << 14);
	/*10.开启递减计数器 - TCON TCON[12]=1  地址=0xC0018008*/
	PWM.TCON |= (0x1 << 12);
}
int main()
{
	hal_pwm_init();
	while(1)
	{
	}
	return 0;
}

