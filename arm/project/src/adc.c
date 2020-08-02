#include "adc.h"
#include "led_on.h"
#include "pwm_on.h"

void hal_adc_init(void)
{
	// IP_RESET_REGISTER1 复位ADC控制器
	unsigned int *ip_reset1 = (unsigned int *)0xC0012004;
	*ip_reset1 = *ip_reset1 & (~(0x1 <<28));
	*ip_reset1 = *ip_reset1 | (0x1 << 28);

	// 设置ADCDAT读取数据的延时时间  ADCCON[13:10]
	ADCCON &= ~(0xF << 10);
	ADCCON |= (ADC_DATA_SEL << 10);//延时周期为5
	// 设置ADC上电延时多少时钟才能开启ADC转换 ADCCON[9:6]
	ADCCON &= ~(0xF << 6);
	ADCCON |= (TOT_ADC_CLK_Cnt << 6);
	// ADC模拟输入通道的选择 ADCCON[5:3]
	ADCCON &= ~(0x7 <<3);
	ADCCON |= (ASEL << 3);
	// 设置ADC分频器的分频值   PRESCALERCON[9:0]
	PRESCALERCON |= _PRESCALERCON;
	// 设置ADC分频器的使能位  PRESCALERCON[15]
	PRESCALERCON |= (0x1 << 15);
	// 开启ADC的电源  ADCCON[2]
	ADCCON &= ~(0x1 <<2);//0:power on
	//中断使能 ADCINTENB[0]=1
	ADCINTENB = 0x1;

//	printf("ADCCON =%ld \n",ADCCON);
//	printf("PRESCALERCON=%ld\n",PRESCALERCON);
}

//开启ADC转换  产生中断信号
void  get_adc_interrupt(void)
{
	// 开启ADC转换  ADCCON[0]
	ADCCON |= 0x1;
	// 等待ADC转换结果  ADCCON[0]
	while((ADCCON & 0x1));//低电平的时候  发生中断信号 高电平的时候 等待转换完成
}

int  get_adc_value(void)
{
	// 开启ADC转换  ADCCON[0]
	ADCCON |= 0x1;
	// 等待ADC转换结果  ADCCON[0]
	if(!(ADCCON & 0x1)) //低电平的时候  触发中断信号
	{
		// 读取转换的数字量  ADCDAT[11:0]
		ADCDAT &= 0xFFF;
	}

//	printf("ADCDAT =%d\n",ADCDAT);

	// 将数字量转换为模拟量进行输出

	int value = (int)(2 * ADCDAT * ((float)1800 / 4096));
	// 直接使用printf函数打印模拟电压值到CRT工具中
	printf("转换后的ADC电压值 = %d\n",value);

	return value;
}

//初始化并得到相应的报警电压阀值
int voltage_control_init(voltageFlg_t voltageFlg)
{
	int vlotage_value = 0;
	switch(voltageFlg)
	{
		case LOWVOLTAGE_DOWN_FLG:
			vlotage_value = LOWVOLTAGE_DOWN_INIT;
			break;
		case LOWVOLTAGE_UP_FLG:
			vlotage_value = LOWVOLTAGE_UP_INIT;
			break;
		case MIDDLEVOLTAGE_FLG:
			vlotage_value = MIDDLEVOLTAGE_INIT;
			break;
		case HIGHVOLTAGE_DOWN_FLG:
			vlotage_value = HIGHVOLTAGE_DOWN_INIT;
			break;
		case HIGHVOLTAGE_UP_FLG:
			vlotage_value = HIGHVOLTAGE_UP_INIT;
			break;
		default:
			break;
	}
	return vlotage_value;
}
//电压检测函数
void voltage_control(int voltage_adc,int lowdown,int lowdup,int middle,int highdown,int highup)
{
	printf("lowdown = %d  lowdup = %d  highdown = %d  highup = %d  \n",lowdown,lowdup,highdown,highup);
	if((voltage_adc>=lowdown)&&(voltage_adc<=lowdup))
	{   
		printf("红灯闪烁\n");
		hal_led_init();//重新初始化
		red_led_on();//红灯闪烁
		hal_pwm2_on(249,299);//打开蜂鸣器 1000HZ
	}
	else if((voltage_adc>lowdup)&&(voltage_adc<=middle))
	{   
		printf("绿灯闪烁\n");
		hal_led_init();//重新初始化
		green_led_on();
		hal_pwm_off();//关掉蜂鸣器
	}
	else if((voltage_adc>middle)&&(voltage_adc<=highdown))
	{   
		printf("蓝灯闪烁\n");
		hal_led_init();//重新初始化
		blue_led_on();
		hal_pwm_off();//关掉蜂鸣器
	}
	else if((voltage_adc>highdown)&&(voltage_adc<=highup))
	{
		printf("白灯闪烁\n");                                               
		hal_led_init();//重新初始化
		white_led_on();
		hal_pwm2_on(249,149);//打开蜂鸣器 2000HZ
	}
	else
	{
		printf("电压过载或者过低,三色灯闪烁\n");
		led_change();
		hal_pwm_off();//关掉蜂鸣器
	}

}


int voltage_changeByUart(const char* CommandValue,int command_num,int voltage_Change_value)//将命令参数转换为整形ADC电压数值
{
	const char *ptr =CommandValue;
	//printf("转换带参数的ADC数值:%c\n",*ptr);

    int  num = 0;
    if((*ptr >= '0')&&(*ptr <= '9'))//如果是数字
    {
        while(*ptr != '\0')
        {
            num = num * 10 + ( *ptr - '0');
            ptr++;
        }
    }
    else
    {
        printf("改变的电压阀值不是数字,请重新输入命令\n");
		//voltage_error = VLOTAGE_ERRORVALUE;//非法的电压阀值
		num = VLOTAGE_ERRORVALUE;//非法的电压阀值
		printf("电压阀值参数是:%d\n",num);
		return num;
    }


    if(num>3300)//大于最高范围的电压阀值
    {
        printf("改变的电压阀值不能超过3.3V,请重新输入命令\n");
        num = VOLTAGE_OVERFLOW;                            
    }

	if(command_num == COMMAND_CHANGE_LOWDOWN)//如果修改的是低电压报警下限阀值  则 修改的数值不能高于1000 不能低于0   0v~ 1v
	{
		if((num<0) || (num>=1000))
		{
			printf("改变的低电压报警下限阀值错误，不能低于0 不能高于1000\n");
			num = VOLTAGE_CHANGELOWDOWN_ERROR;
		}
	}

    if(command_num == COMMAND_CHANGE_LOWUP)//如果修改的是低电压报警上限阀值  则 修改的数值不能高于2000  不能低于1000   1v~2v
    {
        if((num<=1000) || (num>=2000))
        {
            printf("改变的低电压报警上限阀值错误，不能低于1000 不能高于2000\n");
            num = VOLTAGE_CHANGELOWUP_ERROR;
        }
    }

    if(command_num == COMMAND_CHANGE_HIGHDOWN)//如果修改的是高电压报警下限阀值  则 修改的数值不能高于3000V  不能高于2000  2v~3v
    {
        if((num<=2000) || (num>=3000))
        {
            printf("改变的高电压报警下限阀值错误，不能低于2000  不能高于3000\n");
            num = VOLTAGE_CHANGEHIGHDOWN_ERROR;
        }
    }

    if(command_num == COMMAND_CHANGE_HIGHUP)//如果修改的是高电压报警上限阀值  则 修改的数值不能高于3300V  不能低于3000  3v~3.3v
    {
        if((num<=3000) || (num>=3300))
        {
            printf("改变的高电压报警上限阀值错误，不能低于3000 不能高于3300\n");
            num = VOLTAGE_CHANGEHIGHUP_ERROR;
        }
    }

	//printf("电压阀值参数是:%d\n",num);
    return num;
}

