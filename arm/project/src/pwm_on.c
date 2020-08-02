#include "pwm_on.h"

void hal_pwm0_on(unsigned int prescaler, unsigned int tnctb2)//PWM0用作定时器
{
	//将GPIOD1 FUNCTION1 PWM0[3:2] 01
	GPIOD.ALTFN0 &= ~(0x1 << 3);
	GPIOD.ALTFN0 |=  (0x1 <<2);
	
	// 使用PWM0定时器实现1S定时的功能
	// 1.设置对PCLK时钟的一级分频值,进行250分频  TCFG0[7:0] = 249
	// 150000000 / (249 + 1) = 600000 
	PWM.TCFG0 &= ~(0xFF << 0);
	PWM.TCFG0 |= (prescaler << 0);
	// 2.设置对PCLK时钟的二级分频值，进行2分频  TCFG1[3:0] = 0b0001
	// 600000 / 2 = 300000
	PWM.TCFG1 &= ~(0xF << 0);
	PWM.TCFG1 |= (1 << 0);
	//3.设置TCNTB0的初始值，确定PWM定时器的最终周期
	//设置置TCNTB0 = 300000 - 1   PWM定时器的频率为1Hz
	PWM.TCNTB0 =  tnctb2;
	printf("aaaaa:%d\n",PWM.TCNTB0);
	//4.第一个周期是开启手动加载TCNTB0和TCMPB0到递减计数器中
	//TCON[1] = 0b1 
	PWM.TCON |= (1 << 1);
	//5.开启自动加载  TCON[3] = 0b1  产生连续波形
	PWM.TCON |= (1 << 3);
	//6.关闭手动加载   TCON[1] = 0b0
	PWM.TCON &= ~(1 << 1);
	//根据需求选择正向/反向输出 - TCON  TCON[2]=0
	PWM.TCON &= ~(0x1 << 2);
	//7.使能PWM定时器0  TCON[0] = 0b1 
	PWM.TCON |= (1 << 0);
	//8. 使能PWM定时器中断
	PWM.TINT_CSTAT |= (0x1);
	
	 if(PWM.TCNTB0 == 0)
		 printf("TCNTB等于0,PWM0会产生中断???\n");
}


void hal_pwm1_on(unsigned int prescaler, unsigned int tnctb2)//用作定时器
 {
     /*1.将GPIOC13设置成PWM1(Func2)  [27::26] 10功能 - GPIOCALTFN0*/
     GPIOC.ALTFN0 |= (0x1 << 27);
     GPIOC.ALTFN0 &= ~(0x1 << 26);
 
     /*2.设置PWM1的一级分频 - TCFG0[7:0] = 249 =0xF9 = 1111 1010*/
	 if(prescaler >=255)
		PWM.TCFG0 = 254;//最大254
	 else
		 PWM.TCFG0 = prescaler;
 
     /*3.设置PWM1的二级分频 - TCFG1 TCFG1[7:4] = 1/2 =0001 地址=0xC0018004*/
     PWM.TCFG1 &= ~(0xF << 4); 
     PWM.TCFG1 |=  (0x1 << 4);

     /*4.设置PWM1的周期值 - TCNTB1 TCNTB1[31:0] = 299 =0x12B 地址=0xC0018024  1000HZ  T=1ms*/
     PWM.TCNTB1 = tnctb2;
	 printf("PWM1___TCNTB1:%d\n",PWM.TCNTB1);
  
     /*5.设置高电平的时间 - TCMPB1  占空比50% TCMPB1[31:0] = 149 =0x95 地址=0xC0018028*/
     //PWM.TCMPB1 = tnctb2/2;
     /*6.打开手动装载将TCNTB1中的值加载到TCNTO1递减计数器 - TCON TCON[9]=1  地址=0xC0018008*/
     PWM.TCON |= (0x1 << 9);
     /*7.关闭手动装载后续的周期使用自动装载 - TCON TCON[9]=0  地址=0xC0018008*/
     PWM.TCON &= ~(0x1 << 9);
     /*8.打开自动装载，使后续产生连续的波形 - TCON TCON[11]=1  地址=0xC0018008*/
     PWM.TCON |= (0x1 << 11);
     /*9.根据需求选择正向/反向输出 - TCON  TCON[10]=1  地址=0xC0018008*/
     PWM.TCON &= ~(0x1 << 10);
     /*10.开启递减计数器 - TCON TCON[8]=1  地址=0xC0018008*/
     PWM.TCON |= (0x1 << 8);

	 //开启中断  PWM1 TINT_CSTAT[1] = 1
	 PWM.TINT_CSTAT |= (0x1 << 1);

	 if(PWM.TCNTB1 == 0)
		 printf("TCNTB等于0,PWM1会产生中断?????\n");
 }

void hal_pwm2_on(unsigned int prescaler, unsigned int tnctb2)
 {
     /*1.将GPIOC14设置成PWM2(Func2)  [29::28] 10功能 - GPIOCALTFN0*/
     GPIOC.ALTFN0 |= (0x1 << 29);
     GPIOC.ALTFN0 &= ~(0x1 << 28);
 
     /*2.设置PWM2的一级分频 - TCFG0[15:8] = 249 =0xF9 = 1111 1010*/
     PWM.TCFG0 |= (prescaler << 8);
 
     /*3.设置PWM2的二级分频 - TCFG1 TCFG1[11:8] = 1/2 =0001 地址=0xC0018004*/
     PWM.TCFG1 &= ~(0x1 << 11);
     PWM.TCFG1 &= ~(0x1 << 10);
     PWM.TCFG1 &= ~(0x1 << 9);
     PWM.TCFG1 |=  (0x1 << 8);
     /*
     //0010 1/4
     PWM.TCFG1 |= (0x1 << 11);
     PWM.TCFG1 &= ~(0x1 << 10);
     PWM.TCFG1 &= ~(0x1 << 9);
     PWM.TCFG1 &= ~(0x1 << 8);
	*/

     /*4.设置PWM2的周期值 - TCNTB2 TCNTB2[31:0] = 299 =0x12B 地址=0xC0018024  1000HZ  T=1ms*/
     PWM.TCNTB2 = tnctb2;
	 printf("TCNTB2 = %d\n",PWM.TCNTB2);
     /*5.设置高电平的时间 - TCMPB2  占空比50% TCMPB2[31:0] = 149 =0x95 地址=0xC0018028*/
     PWM.TCMPB2 = tnctb2 / 2;
     /*6.打开手动装载将TCNTB2中的值加载到TCNTO2递减计数器 - TCON TCON[13]=1  地址=0xC0018008*/
     PWM.TCON |= (0x1 << 13);
     /*7.关闭手动装载后续的周期使用自动装载 - TCON TCON[13]=0  地址=0xC0018008*/
     PWM.TCON &= ~(0x1 << 13);
     /*8.打开自动装载，使后续产生连续的波形 - TCON TCON[15]=1  地址=0xC0018008*/
     PWM.TCON |= (0x1 << 15);
     /*9.根据需求选择正向/反向输出 - TCON  TCON[14]=0  地址=0xC0018008*/
     PWM.TCON &= ~(0x1 << 14);
     /*10.开启递减计数器 - TCON TCON[12]=1  地址=0xC0018008*/
     PWM.TCON |= (0x1 << 12);

	 //开启中断  PWM2 TINT_CSTAT[2] = 1
	 //PWM.TINT_CSTAT |= (0x1 << 2);

 }
void hal_pwm_off()
{
    /*1.将GPIOC14设置成00  关闭蜂鸣器*/       
    GPIOC.ALTFN0 &= ~(0x1 << 29);                                          
    GPIOC.ALTFN0 &= ~(0x1 << 28);                                         
}
