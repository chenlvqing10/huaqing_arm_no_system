#ifndef __ADC__         
#define __ADC__
//包含芯片的头文件
#include <s5p6818.h>
//定义命令编号标志
#define    COMMAND_CHANGE_LOWDOWN     9//修改低电压报警下限阀值
#define	   COMMAND_CHANGE_LOWUP       10//修改低电压报警上限阀值
#define    COMMAND_CHANGE_HIGHDOWN    11//修改高电压报警下限阀值
#define    COMMAND_CHANGE_HIGHUP      12//修改高电压报警上限阀值
#define    COMMAND_NAME_ERROR         13//错误命令名
#define    COMMAND_VALUE_ERROR        14//错误命令参数
//设置报警电压标志  枚举类型
typedef enum
{
 LOWVOLTAGE_DOWN_FLG  =  1,     //ADC低电压下限阀值标志
 LOWVOLTAGE_UP_FLG,				//ADC低电压上限阀值标志
 MIDDLEVOLTAGE_FLG,				//ADC中间电压阀值标志
 HIGHVOLTAGE_DOWN_FLG,			//ADC高电压下限阀值标志
 HIGHVOLTAGE_UP_FLG				//ADC高电压上限阀值标志
}voltageFlg_t;

#define VLOTAGE_ERRORVALUE				8888 //非法电压阀值
#define VOLTAGE_OVERFLOW				9999  //电压超载
#define VOLTAGE_CHANGELOWDOWN_ERROR		7777//改变低电压下限阀值错误
#define VOLTAGE_CHANGELOWUP_ERROR		7776//改变低电压上限阀值错误
#define VOLTAGE_CHANGEHIGHDOWN_ERROR	7775//改变高电压下限阀值错误
#define VOLTAGE_CHANGEHIGHUP_ERROR		7774//改变高电压上限阀值错误


#define LOWVOLTAGE_DOWN_INIT    0      //ADC低电压下限阀值
#define	LOWVOLTAGE_UP_INIT		1000   //ADC低电压上限阀值
#define MIDDLEVOLTAGE_INIT		2000   //ADC中间电压阀值
#define HIGHVOLTAGE_DOWN_INIT   3000   //ADC高电压下限阀值
#define HIGHVOLTAGE_UP_INIT		3300   //ADC高电压上限阀值


#define  ADC_DATA_SEL		0		//DCDAT读取数据的延时时间 0000 延时5个周期
#define  TOT_ADC_CLK_Cnt	6		//设置ADC上电延时多少时钟才能开启ADC转换  至少6个周期之后才开始转换
#define  ASEL				0		//ADC模拟输入通道0
#define  _PRESCALERCON		199		//分频数值 >=25  25---254

void hal_adc_init(void);//ADC初始化
int get_adc_value(void);//进行模数转换
void voltage_control(int voltage_adc,int lowdown,int lowdup,int middle,int highdown,int highup);//电压检测函数
int voltage_control_init(voltageFlg_t voltageFlg);//设置ADC电压阀值
int voltage_changeByUart(const char* CommandValue,int command_num,int voltage_Change_value);//将命令参数转换为整形ADC电压数值
void get_adc_interrupt(void);//产生中断信号

#endif

