#include "watchdog.h"

/*看门狗的初始化*/
void hal_watchdog_init(void)
{
	unsigned int *ip_reset1 = (unsigned int *)0xC0012004;
	*ip_reset1 = *ip_reset1 & (~(0x3 <<26));
	*ip_reset1 = *ip_reset1 | (0x3 << 26);
	//设置分频数值
	WTCON &= (~(0xFF << 8));//先清零
	WTCON |= (_PRESCALER << 8);  //再设置成249
	//设置分频因子
	WTCON |= (0x3 << 3);         //128
	//设置WTCNT寄存器的初始值
	WTCNT = _WATCNT;             //8448 * 2
	//WTDAT = _WATCNT;			//在看门狗启动后该数值不能加载到WTCNT寄存器中
	//计算看门狗定时器时钟周期
	float t_watchdog = (float) 1 / ( ((float)_PLCK*1000000 / ( _PRESCALER + 1 )) / (float) _DIVFACTOR);
	//计算超时时间
	float time = t_watchdog * _WATCNT;
	int  _time = (int) time;
	printf("_time = %d \n",_time);
	//启动看门狗
	WTCON |= (0x1 << 2); //Reset signal enable
	WTCON |= (0x1 << 5);//wdt enable
}
void WDT_Feed(void)//喂狗函数
{
	WTCNT = _WATCNT;//重置计数器
}






