 #ifndef __WATCHDOG__                                              
 #define __WATCHDOG__
 //包含芯片的头文件
 #include <s5p6818.h>
 
 #define  _PLCK 150              //时钟源的频率
 #define  _PRESCALER 249    //预分频数值
 #define  _DIVFACTOR 128        //分频因子
 #define  _WATCNT    8448*2     //Down 计数器数字
 
 void hal_watchdog_init(void);//看门狗的初始化
 void WDT_Feed(void);//喂狗函数                                    
 
 
 #endif

