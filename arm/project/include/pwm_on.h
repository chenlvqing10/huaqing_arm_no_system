#ifndef __PWMON__
#define __PWMON_
#include <s5p6818.h>   

void hal_pwm2_on(unsigned int prescaler, unsigned int tnctb2);//一级分频，PWM2的周期值 蜂鸣器开启
void hal_pwm_off();//蜂鸣器关闭
void hal_pwm1_on(unsigned int prescaler, unsigned int tnctb2);//用作定时器
void hal_pwm0_on(unsigned int prescaler, unsigned int tnctb2);//用作定时器

                               
#endif

