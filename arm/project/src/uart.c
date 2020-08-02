#include "uart.h"
#include "led_on.h"
#include "pwm_on.h"
#include "adc.h"
void hal_uart_init(_uint32 sclk_uart,_uint32 bound)//时钟源的频率，波特率
{
	// 1. 设置UARTTXD0::GPIOD18 GPIOxALTFN1[5:4]=01引脚和UARTRXD0::GPIOD14 GPIOxALTFN0[29:28]=01引脚位串口功能
	GPIOD.ALTFN1 &= ~( 0x1 <<5 );
	GPIOD.ALTFN1 |=  ( 0x1 <<4 );
	GPIOD.ALTFN0 &= ~( 0x1 << 29 );
	GPIOD.ALTFN0 |=  ( 0x1 << 28 );

	// 2. 设置串口数据帧的格式：8N1    ULCON
	//ULCON[6]:0 正常模式  ULCON[1:0]:11 8位数据位  ULCON[5:3]:0xx 无校验位   ULCON[2]:0 1个停止位
	UART0.ULCON &= ~( 0x1 << 6 );//Normal Mode
	UART0.ULCON &= ~( 0x1 << 3 );//no parity
	UART0.ULCON &= ~( 0x1 << 2 );//one stop
	UART0.ULCON |=  0x3;//8 bits datas

	//printf("sclk_uart = %d\n",sclk_uart);
	//printf("bound = %d\n",bound);

	// 3. 设置串口的波特率 115200   UBRDIV  UFRACVAL
	float div_val = (float) ( sclk_uart * 1000000 ) /  ( bound * 16 )-1;
	//得到整数部分
	int ubrdivn = (int) div_val;
	//计算小数部分
	int ufracvaln =(int)((div_val  - (float)ubrdivn) * 16);

//	printf("ubrdivn=%d\n",ubrdivn);
//	printf("ufracvaln=%d\n",ufracvaln); 

	//设置UBRDIVn寄存器和UFRACVALn寄存器的数值
	UART0.UBRDIV    = ubrdivn;
	UART0.UFRACVAL = ufracvaln;
	// 4. 设置串口发送和接收模式：轮询模式  
	//UCON Transmit Mode [3:2] 01 = Interrupt request or Polling mode
	//UCON Receive  Mode [1:0] 01 = Interrupt request or Polling mode
	UART0.UCON |=  (0x1 << 2);
	UART0.UCON &= ~(0x1 << 3);
	UART0.UCON |=	0x1;
	UART0.UCON &= ~(0x1 << 1);
//	printf("UART0.UCON=%X",UART0.UCON);
}

int strlen(const char* str)
{   
	int len = 0;
	while(*str!='\0')
	{   
		len++;
		str++;
	}
	return len;
}


// 发送一个字节的函数
void Transmit_Byte(const char ch)
{
	// 循环判断发送缓冲区是否为空  UTRSTAT[1]=1
	//printf("寄存器UTRSTAT[2]::%d\n",r_val_trns);
	//printf("寄存器UTRSTAT[1]::%d\n",r_val_buf);

	while(!((UART0.UTRSTAT >> 1) & (0x1)) );//等待发送缓冲器为空

	// 继续向发送缓冲区内发送数据  发送寄存器 
	//	printf("*****************************************\n");
	UART0.UTXH = ch;


	if(ch == '\n')
		Transmit_Byte('\r');
}

// 接收一个字节的函数
char Receive_Byte(int command_num,int CommandValue,int voltage_low_down_adc,int voltage_low_up_adc,
		int voltage_middle_adc,int voltage_high_down_adc, int voltage_high_up_adc)
{
	//char ch;
	// 判断接收缓冲区是否有有效数据，如果接收缓冲区没有有效数据，
	// 则等待接收缓冲区有有效的数据  UTRSTAT[0]
	//printf("寄存器UTRSTAT[0]::%d\n",r_val);
	while(!((UART0.UTRSTAT >> 0) & (0x1))) //0为空 1为数据准备好了
	{
		//printf("UARTC.c 命令编号::::::%d\n",command_num);
		ExecCommandByUart(command_num,CommandValue,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);
	}

	//接收数据
	//ch = UART0.URXH;
	return UART0.URXH;
}

// 发送字符串的函数
void Transmit_String(const char *str) 
{
	// 判断是否到字符串的结尾
	const char *ptr = str;
	while(*ptr!='\0')
	{
		// 如果没有到结尾调用Transmit_Byte函数，一个字节一个字节发送。
		Transmit_Byte(*ptr);
		ptr++;
	}

}

//接受字符串的函数
void Receive_String(char *str,int len,int command_num,int CommandValue,int voltage_low_down_adc,
		int voltage_low_up_adc,int voltage_middle_adc,int voltage_high_down_adc, int voltage_high_up_adc)
{
	char ch;//从仿真终端接受字符
	int i;
	for(i=0;i<len-1;i++)
	{
		ch = Receive_Byte(command_num,CommandValue,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);//接收终端的字符
		if(ch != '\r')//如果不是回车
		{
			str[i] = ch;//读取终端的字符串到数组中
			Transmit_Byte(ch);//放到发送寄存器中回显
		}
		else
		{
			break;//如果接收到的是回车则跳出循环
		}
	}
	str[i] = '\0';
}



int StringCmp(char* str,char *dtr)
{
	char *ptr1 = str;
	char *ptr2 = dtr;
	while((*ptr1 == *ptr2)&&(*ptr1!='\0')&&(*ptr2!='\0'))
	{
		ptr1++;
		ptr2++;
	}
	if((*ptr1=='\0') && (*ptr2=='\0'))
		return 1;
	else
		return 0;
}

//根据命令编号来执行命令
void ExecCommandByUart(command_num_t command_num,int CommandValue,int voltage_low_down_adc,int voltage_low_up_adc,
		int voltage_middle_adc,int voltage_high_down_adc, int voltage_high_up_adc)//执行命令
{
	//ADC读取电压初始化
	int voltage_adc = 0;

	switch(command_num)
	{
		//电压 与 命令 有冲突
		case COMMAND_INIT:
			//三色灯闪烁
			led_change();
			break;
		case COMMAND_REDON:
			//红灯闪烁
			red_led_on();
			break;
		case COMMAND_REDOFF:
			//红灯关闭
			hal_red_led_stutes(0);
			break;
		case COMMAND_GREENON:
			//绿灯闪烁
			green_led_on();
			break;
		case COMMAND_GREENOFF:
			//绿灯关闭
			hal_green_led_stutes(0);
			break;
		case COMMAND_BLUEON:
			//蓝灯闪烁
			blue_led_on();
			break;
		case COMMAND_BLUEOFF:
			//蓝灯关闭
			hal_blue_led_stutes(0);
			break;
		case COMMAND_PWMON:
			//蜂鸣器叫
			hal_pwm2_on(249,299);//1000HZ
			break;
		case COMMAND_PWMOFF:
			//蜂鸣器不叫
			hal_pwm_off();
			break;
		case COMMAND_CHANGE_LOWDOWN:
			//修改报警低电压下限阀值
			voltage_low_down_adc = CommandValue;
			break;
		case COMMAND_CHANGE_LOWUP:
			//修改报警低电压上限阀值
			voltage_low_up_adc = CommandValue;
			break;
		case COMMAND_CHANGE_HIGHDOWN:
			//修改报警高电压下限阀值
			voltage_high_down_adc = CommandValue;
			break;
		case COMMAND_CHANGE_HIGHUP:
			//修改报警高电压上限阀值
			voltage_high_up_adc = CommandValue;
			break;
		case COMMAND_NAME_ERROR:
			printf("错误的命令名字\n");
			delay_ms(5000);
			break;
		case COMMAND_VALUE_ERROR:
			printf("错误的命令参数\n");
			delay_ms(5000);
			break;
		default:
			break;
	}

	if((command_num>=COMMAND_CHANGE_LOWDOWN)&&(command_num<=COMMAND_CHANGE_HIGHUP))
	{
		voltage_adc = get_adc_value();
		//调用电压检测函数
		voltage_control(voltage_adc,voltage_low_down_adc,voltage_low_up_adc,voltage_middle_adc,voltage_high_down_adc,voltage_high_up_adc);   
	}


}

char* getCommandNameByUart(char *buffer_uart)//分离命令 得到命令名
{
	char *ptr = buffer_uart;                                              
	char CommandName[50]={0};
	int i=0;
	int count_blank = 0;
	while(*ptr!='\0')
	{
		if(count_blank>=2)
		{
			break;
		}
		else
		{
			CommandName[i] = *ptr;
			ptr++;
			i++;
		}
		if(*ptr == ' ')
		{
			CommandName[i] = *ptr;
			ptr++;
			i++;
			count_blank++;
		}
	}

	char *ptr_CommandName = CommandName;

	return ptr_CommandName;
}

char* getCommandValueByUart(char *buffer_uart)//分离命令 得到参数数值
{
	char *ptr = buffer_uart;                                              
	char CommandValue[20]={0};
	int i=0;
	int count_blank = 0;

	while(*ptr!='\0')
	{
		if(count_blank>=2)
		{
			CommandValue[i] = *ptr;
			ptr++;
			i++;
		}
		else
		{
			ptr++;
			i++;
		}
		if(*ptr == ' ')
		{
			ptr++;
			i++;
			count_blank++;
			if(count_blank>=2)
				i=0;
		}
	}

	char *ptr_CommandValue = CommandValue;

	return ptr_CommandValue;
}

//根据命令名字得到命令编号
int  getCommandNumByUart(char *CommandName,int command_num)
{
	if((StringCmp(CommandName,"REDON")) || (StringCmp(CommandName,"redon")) )
	{
		command_num = 1;
	}
	else if((StringCmp(CommandName,"REDOFF")) || (StringCmp(CommandName,"redoff")) )
	{
		if((command_num == 1))//红灯亮
			command_num = 2;
	}
	else if((StringCmp(CommandName,"GREENON")) || (StringCmp(CommandName,"greenon")) )
	{
		command_num = 3;
	}
	else if((StringCmp(CommandName,"GREENOFF")) || (StringCmp(CommandName,"greenoff")) )
	{
		if(command_num == 3)//绿灯亮
			command_num = 4;
	}
	else if((StringCmp(CommandName,"BLUEON")) || (StringCmp(CommandName,"blueon")) )
	{
		command_num = 5;
	}
	else if((StringCmp(CommandName,"BLUEOFF")) || (StringCmp(CommandName,"blueoff")) )
	{
		if(command_num == 5)//蓝灯亮
			command_num = 6;
	}
	else if((StringCmp(CommandName,"PWMON")) || (StringCmp(CommandName,"pwmon")))
	{
		command_num = 7;
	}
	else if((StringCmp(CommandName,"PWMOFF")) || (StringCmp(CommandName,"pwmoff")))
	{
		command_num = 8;
	}
	else if((StringCmp(CommandName,"CHANGEVOLTAGE LOWDOWN ")) || (StringCmp(CommandName,"changevoltage lowdown ")))
	{
		command_num = 9;
	}
	else if((StringCmp(CommandName,"CHANGEVOLTAGE LOWUP ")) || (StringCmp(CommandName,"changevoltage lowup ")))
	{
		command_num = 10;
	}
	else if((StringCmp(CommandName,"CHANGEVOLTAGE HIGHDOWN ")) || (StringCmp(CommandName,"changevoltage highdown ")))
	{
		command_num = 11;
	}
	else if((StringCmp(CommandName,"CHANGEVOLTAGE HIGHUP ")) || (StringCmp(CommandName,"changevoltage highup ")))
	{
		command_num = 12;
	}
	else//命令错误
	{
		command_num = 13;
	}

	return command_num;

}


char* mystrcpy(char* strDest,const char* strSrc)
{
	char* address = strDest;
	while((*strDest++ = *strSrc++)!='\0');
	return address;
}
