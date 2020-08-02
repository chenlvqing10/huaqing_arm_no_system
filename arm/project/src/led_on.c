#include "led_on.h"

/*gpio */
void hal_led_init(void)
{
	// GPIO引脚为GPIO功能
	//for red led A28 -------------Register ALTFN1[25:24] :: 00
	GPIOA.ALTFN1 &= ~(0x3 << 24);
	//for green len E13----------Register AlTFN0[27:26] :: 00
	GPIOE.ALTFN0 &= ~(0x3 << 26);
	//for blue led B12------------Register AlTFN0[25:24] :: 10
	GPIOB.ALTFN0 |= (0x1 << 25);
	GPIOB.ALTFN0 &= ~(0x1 << 24);
	// GPIO引脚为输出功能
	//for red led A28 Register OUTENB[28]:1
	GPIOA.OUTENB |= (0X1 << 28);
	//for green led E13 Register OUTENB[13]:1
	GPIOE.OUTENB |= (0x1 << 13);
	//for blue led B12 Register OUTENB[13]:1
	GPIOB.OUTENB |= (0x1 << 12);
	//设置灯为熄灭状态
	GPIOA.OUT &= ~(0x1 << 28);
	GPIOE.OUT &= ~(0x1 << 13);
	GPIOB.OUT &= ~(0x1 << 12);
}

void hal_red_led_stutes(stu_t stu)
{
	if (stu == LED_ON){
		//点亮  A28 Register OUT[28]:1
		GPIOA.OUT |= (0x1 << 28);
	}
	else {
		// 熄灭  A28 Register OUT[28]:1
		GPIOA.OUT &= ~(0x1 << 28);
	}
}
void hal_green_led_stutes(stu_t stu)
{
	if (stu == LED_ON){
		//点亮  E13 Register OUT[13]:1
		GPIOE.OUT |= (0x1 << 13);
	}
	else {
		// 熄灭  E13 Register OUT[13]:1
		GPIOE.OUT &= ~(0x1 << 13);
	}
}
void hal_blue_led_stutes(stu_t stu)
{
	if (stu == LED_ON){
		//点亮  B12 Register OUT[12]:1
		GPIOB.OUT |= (0x1 << 12);
	}
	else {
		// 熄灭  B12 Register OUT[12]:1
		GPIOB.OUT &= ~(0x1 << 12);
	}
}

void red_led_on(void)//红灯闪烁
{
	hal_red_led_stutes(1);
	delay_ms(300);
	hal_red_led_stutes(0);
	delay_ms(300);

}

void green_led_on(void)//绿灯闪烁
{
	hal_green_led_stutes(1);
	delay_ms(300);
	hal_green_led_stutes(0);
	delay_ms(300);

}
void blue_led_on(void)//蓝灯闪烁
{
	hal_blue_led_stutes(1);
	delay_ms(300);
	hal_blue_led_stutes(0);
	delay_ms(300);

}
void led_change(void)
{
	// 三色LED灯交替闪烁
	hal_red_led_stutes(1);
	delay_ms(300);
	hal_red_led_stutes(0);
	hal_green_led_stutes(1);
	delay_ms(300);
	hal_green_led_stutes(0);
	hal_blue_led_stutes(1);
	delay_ms(300);
	hal_blue_led_stutes(0);

}

void white_led_on(void)//白灯闪烁   
{
	hal_red_led_stutes(1);
	hal_green_led_stutes(1);
	hal_blue_led_stutes(1);
	delay_ms(300);
	hal_red_led_stutes(0);
	hal_green_led_stutes(0);
	hal_blue_led_stutes(0);
	delay_ms(300);

}
