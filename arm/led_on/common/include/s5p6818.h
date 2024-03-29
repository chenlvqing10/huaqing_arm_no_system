#ifndef      __S5P6818_H__
#define      __S5P6818_H__

#define	__REG(x)	(*(volatile unsigned int *)(x))  
#define	uint32		unsigned int

#include <s5p6818_adc.h>
#include <s5p6818_clk.h>
#include <s5p6818_gpio.h>
#include <s5p6818_iic.h>
#include <s5p6818_int.h>
#include <s5p6818_pwm.h>
#include <s5p6818_rtc.h>
#include <s5p6818_spi.h>
#include <s5p6818_sys.h>
#include <s5p6818_uart.h>
#include <s5p6818_wdt.h>


extern void printf (const char *fmt, ...);

#endif		// __S5P6818_H__
