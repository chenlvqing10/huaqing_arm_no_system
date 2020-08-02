#include "delay.h"

 /*set delay time with for cycle*/
 void delay_ms(unsigned int ms)
 {
     unsigned int i,j;
     //delay time = ms*1800
     for(i = 0; i < ms; i++)
         for(j = 0; j < 1800; j++);
 }

