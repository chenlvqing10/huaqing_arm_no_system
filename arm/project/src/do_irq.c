// irq类型中断处理程序的入口
#include "s5p6818.h"
#include "delay.h"
#include "adc.h"
void do_irq(void) 
{
	int irq_num;
	// 获取中断号 GICC_IAR[9:0]
	irq_num = GICC_IAR & 0x3FF;	
	switch(irq_num) 
	{
		case 59:
			printf("1s PWM Timer Interrupt!\n");
			PWM.TINT_CSTAT |= (1 << 5);
			GICD_ICPENDER.ICPENDER1 |= (0x1 << 27);
			break;
		case 60://PWM1中断源
			printf("2s PWM Timer Interrupt!\n");
			//清除PWM1层中断挂起标志位  PWM.TINT_CSTAT[6] = 1
			PWM.TINT_CSTAT |= (0x1 << 6);   
			// 清除GICD层中断挂起标志位 GICD_ICPENDER1[28]
			GICD_ICPENDER.ICPENDER1 |= (0x1 << 28);
			break;
		case 61://PWM2中断源
			printf("KEY Interrupt Number = %d\n",irq_num);
			//清除PWM2层中断挂起标志位  PWM.TINT_CSTAT[7] = 1
			PWM.TINT_CSTAT |= (0x1 << 7);   
			// 清除GICD层中断挂起标志位 GICD_ICPENDER1[28]
			GICD_ICPENDER.ICPENDER1 |= (0x1 << 29);
			break;
		case 73://ADC中断源
			printf("KEY Interrupt Number = %d\n",irq_num);
			get_adc_value();//进行ADC转换
			//清除ADC层中断挂起标志位  ADCINTCLR[0]
			ADCINTCLR = 0x1;
			// 清除GICD层中断挂起标志位 GICD_ICPENDER2[9]
			GICD_ICPENDER.ICPENDER2 |= (0x1 << 9);
			break;
		case 86:
			//86号中断处理程序
			//获取终端之后的行为
			printf("KEY Interrupt Number = %d\n",irq_num);

			if (GPIOB.DET & (0x1 << 8)) //如果是key -按键
			{
				//去除按键的抖动
				while(!(GPIOB.PAD & (1 << 8))) 
				{
					delay_ms(10);  // 去抖动
					// 松手检测  
					while(!(GPIOB.PAD & (1 << 8))); //按键没有松开之前一直循环  按下的时候产生下降沿 
					printf("KEY VOL-\n");
				}

				// 清除GPIO层中断挂起标志位 GPIOBDET
				GPIOB.DET |= (0x1 << 8);

			} 
			else if (GPIOB.DET & (0x1 << 16)) //如果是key +按键
			{
				//去除按键的抖动
				while(!(GPIOB.PAD & (1 << 16))) 
				{
					delay_ms(10);
					while(!(GPIOB.PAD & (1 << 16)));//按键没有松开之前一直循环  按下的时候产生下降沿 
					printf("KEY VOL+\n");
				}
				// 清除GPIO层中断挂起标志位 GPIOBDET
				GPIOB.DET |= (0x1 << 16);
			}
			// 清除GICD层中断挂起标志位 GICD_ICPENDER2[22]
			GICD_ICPENDER.ICPENDER2 |= (0x1 << 22);
			break;
		case 87:		
			//87号中断处理程序
			break;
			// ....
	}
	// 清除GICC层中断号  GICC_EOIR[9:0]
	GICC_EOIR = (GICC_EOIR & (~0x3FF)) | irq_num;
}

