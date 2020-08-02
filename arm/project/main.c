#include <s5p6818.h>
#include "delay.h"
#include "led_on.h"
#include "pwm_on.h"
#include "uart.h"
#include "watchdog.h"
#include "adc.h"
#include "key.h"

int main()
{
	hal_led_init();//led灯初始化
	/*
	//shell命令变量初始化
	int  command_num = 0;//初始化命令编号
	char command_Name[50] = {0};//初始化命令名字
	char command_Value[20] = {0};//初始化命令参数数值
	*/

	hal_uart_init(50,115200);//UART初始化 50MHZ 115200bps
	//char buffer_uart[100];//用于存放终端的字串
	//const char* string = "nihao hello test\nhello UART";
	//Transmit_String(string);//发送字符串

	//初始化看门狗
	//hal_watchdog_init();

	//初始化adc
	hal_adc_init();

	//调用中断程序
	hal_gpio_interrupt_init();//按键中断
	hal_gic_init();//设置中断源
	hal_pwm0_on(249,599999);//1sPWM中断一次
	hal_pwm1_on(249,299999);//2sPWM中断一次

	//蜂鸣器
	//hal_pwm2_on(249,299);//0.1ms
/*
	//报警电压初始化
	int voltage_Change_value = 0;//要修改的报警电压阀值
	int voltage_low_down_adc  = voltage_control_init(1);//低电压报警下限
	int voltage_low_up_adc    = voltage_control_init(2);//低电压报警上限
	int voltage_middle_adc    = voltage_control_init(3);//中间电压阀值
	int voltage_high_down_adc = voltage_control_init(4);//高电压报警下限
	int voltage_high_up_adc   = voltage_control_init(5);//高电压报警上限
*/
	while(1)
	{
		//产生ADC中断信号
		//get_adc_interrupt();





		/*
		   int tempCommandNum = command_num;
		//UART功能
		printf("-------------------------------------------------\n");
		//接受字符串 传入电压阀值
		Receive_String(buffer_uart,100,command_num,voltage_Change_value,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);
		printf("\n");
		Transmit_String(buffer_uart);//回显
		printf("\n");
		printf("BUFFER_UART = %s\n",buffer_uart);

		//按分隔符" "分离命令名和参数数值
		char *commandName  = getCommandNameByUart(buffer_uart);
		char *commandValue = getCommandValueByUart(buffer_uart);
		mystrcpy(command_Name,commandName);
		mystrcpy(command_Value,commandValue);

		//printf("串口命令名字:%s\n",commandName);
		//printf("串口命令参数:%s\n",commandValue);

		if(strlen(commandValue)==0)//空字符串 命令无参数
		{
		//printf("前一个串口命令编号aaaaaaaaaaaa::::%d\n",command_num);
		printf("没有参数的命令\n");
		command_num = getCommandNumByUart(command_Name,command_num);//通过命令函数产生一个命令编号
		//printf("无参数shell命令编号::::%d\n",command_num);
		if(command_num==COMMAND_NAME_ERROR)
		{
		printf("错误的命令名字\n");
		command_num = tempCommandNum;//如果错误 保留命令编号的前值
		}
		//执行串口命令	
		ExecCommandByUart(command_num,voltage_Change_value,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);
		}
		else
		{
		//printf("前一个串口命令编号aaaaaaaaaaaa::::%d\n",command_num);
		//printf("带参数的命令\n");
		command_num = getCommandNumByUart(command_Name,command_num);//通过命令函数产生一个命令编号
		if(command_num == COMMAND_NAME_ERROR)
		{
		//不去改变报警电压数值 直接调用电压执行函数
		//printf("带参数的shell命令编号::::%d\n",command_num);
		ExecCommandByUart(command_num,voltage_Change_value,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);
		}
		else
		{
		//转换ADC电压(从字符串到整形)
		voltage_Change_value = voltage_changeByUart(command_Value,command_num,voltage_Change_value);

		if(voltage_Change_value>HIGHVOLTAGE_UP_INIT)//命令参数错误
		{
		command_num = COMMAND_VALUE_ERROR;
		//printf("带参数的shell命令编号::::%d\n",command_num);
		//不去改变报警电压数值 直接调用电压执行函数
		ExecCommandByUart(command_num,voltage_Change_value,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);
		}
		else
		{
		//printf("带参数的shell命令编号::::%d\n",command_num);
		//重新设置新的报警电压阀值
		if(command_num == COMMAND_CHANGE_LOWDOWN)
		{
		voltage_low_down_adc = voltage_Change_value;
		}
		else if(command_num == COMMAND_CHANGE_LOWUP)
		{
		voltage_low_up_adc = voltage_Change_value;
		}
		else if(command_num == COMMAND_CHANGE_HIGHDOWN)
		{
		voltage_high_down_adc = voltage_Change_value;
	}
		else if(command_num == COMMAND_CHANGE_HIGHUP)
		{
			voltage_high_up_adc = voltage_Change_value;
		}

		//printf("带参数的串口命令------修改后的报警电压阀值:::::%d\n",voltage_Change_value);
		ExecCommandByUart(command_num,voltage_Change_value,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);
	}
	}
	}

	// 看门狗喂狗
	//WDT_Feed();

	//ADC读取电压
	//int voltage_adc = get_adc_value();
	//调用电压检测函数
	//voltage_control(voltage_adc,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);
	*/
		//设置延迟时间
		delay_ms(300);
	}
	return 0;
}
