#ifndef __LEDON__
#define __LEDON__

#include <s5p6818.h>
#include "delay.h"

typedef enum{
    LED_OFF = 0,
    LED_ON,
}stu_t;


void hal_led_init(void);
void hal_red_led_stutes(stu_t stu);
void hal_green_led_stutes(stu_t stu);
void hal_blue_led_stutes(stu_t stu);
void led_change(void);//三色灯光交替闪烁
void red_led_on(void);//红灯闪烁
void green_led_on(void);//绿灯闪烁
void blue_led_on(void);//蓝灯闪烁
void white_led_on(void);//白灯闪烁


#endif

