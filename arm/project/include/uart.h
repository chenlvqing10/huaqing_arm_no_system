#ifndef __UART__
#define __UART__
//包含芯片的头文件
#include <s5p6818.h>

//定义命令编号标志
typedef enum
{
	COMMAND_INIT =0,  //三色灯闪烁
	COMMAND_REDON = 1,//红灯闪烁
	COMMAND_REDOFF,//红灯灭
	COMMAND_GREENON,//绿灯闪烁
	COMMAND_GREENOFF,//绿灯灭
	COMMAND_BLUEON,//蓝灯闪烁
	COMMAND_BLUEOFF,//蓝灯灭
	COMMAND_PWMON,//蜂鸣器响
	COMMAND_PWMOFF,//蜂鸣器关闭
	COMMAND_CHANGE_LOWDOWN,//修改低电压报警下限阀值
	COMMAND_CHANGE_LOWUP,//修改低电压报警上限阀值
	COMMAND_CHANGE_HIGHDOWN,//修改高电压报警下限阀值
	COMMAND_CHANGE_HIGHUP,//修改高电压报警上限阀值
	COMMAND_NAME_ERROR,//错误命令名
	COMMAND_VALUE_ERROR//错误命令参数
}command_num_t;

typedef unsigned int _uint32;

//定义串口初始化函数  使用串口0
void hal_uart_init(_uint32 sclk_uart,_uint32 bound);//时钟源的频率，波特率
void Transmit_Byte(const char ch);//发送函数 按字节发送
char Receive_Byte( int command_num,int CommandValue,int voltage_low_down_adc,
		int voltage_low_up_adc,int voltage_middle_adc,int voltage_high_down_adc, int voltage_high_up_adc);//接收函数 按字节接收
void Receive_String(char *str,int len, int command_num,int CommandValue,int voltage_low_down_adc,
        int voltage_low_up_adc,int voltage_middle_adc,int voltage_high_down_adc, int voltage_high_up_adc);
void Transmit_String(const char* str);//发送函数 按字符串发送
int StringCmp(char* str,char *dtr);
int  getCommandNumByUart(char *CommandName,int command_num);//得到命令编号       
void ExecCommandByUart(command_num_t command_num,int CommandValue,int voltage_low_down_adc,int voltage_low_up_adc,
		int voltage_middle_adc,int voltage_high_down_adc, int voltage_high_up_adc);//执行命令
char* getCommandNameByUart(char *buffer_uart);//分离命令 得到命令名
char* getCommandValueByUart(char *buffer_uart);//分离命令 得到参数数值
int strlen(const char* str);    
char* mystrcpy(char* strDest,const char* strSrc);

#endif
