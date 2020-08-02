#include <stdio.h>
#include <string.h>
 #define  _PLCK 150              //时钟源的频率
 #define  _PRESCALER 249   //预分频数值
 #define  _DIVFACTOR 128        //分频因子


char* mystrcpy(char* strDest,const char* strSrc)
{
    char* address = strDest;

    while((*strDest++ = *strSrc++)!='\0');
    return address;
}


int mystrlen(const char* str)
{
	int len = 0;
	while(*str!='\0')
	{
		len++;
		str++;
	}
	return len;
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





void Transmit_Byte(const char c)
{
	printf("c=%c  ",c);
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
int StringCmp(char* str,char *dtr)
{
    char *ptr1 = str;
    char *ptr2 = dtr;                                                       
    while((*ptr1 == *ptr2)&&(*ptr1!='\0')&&(*ptr2!='\0'))
    {
        ptr1++;
        ptr2++;
    }
    if((*ptr1=='\0') && (*ptr1=='\0'))
        return 1;
    else
        return 0;
}

int main()
{
	unsigned int sclk_uart = 40;
	unsigned int bound = 115200;

	float div_val = (float) ( sclk_uart * 1000000 ) /  ( bound * 16 )-1;
	printf("div_val=%.6f\n",div_val);
	//得到整数部分
	int ubrdivn = (int) div_val;
	//得到小数部分
	int ufracvaln =(int)((div_val  - (float)ubrdivn) * 16);
	printf("ubrdivn=%d\n",ubrdivn);
	printf("ufracvaln=%d\n",ufracvaln);

	int a = 0x8;
	int b =(a >> (3)) & 0x1;
	printf("b=%d\n",b);

	char *str = "abcddddd";
	Transmit_String(str);
	float temp =  ( (float)_PLCK*1000000 / ( _PRESCALER + 1 )) / (float) _DIVFACTOR;
	printf("temp = %f",temp);
	float t_watchdog = (float) 1 / ( ((float)_PLCK*1000000 / ( _PRESCALER + 1 )) / (float) _DIVFACTOR);
	float time = t_watchdog * 8448 * 2;
	printf("time = %f",time);
	
	char buffer[50] = "changevoltage lowup 888";
	char *ptr = buffer;
	char temp1[50]={0};
	char temp2[50]={0};
	int  voltage_Change=0;
	int i=0;
	int count_blank = 0;
	while(*ptr!='\0')
	{
		if(count_blank>=2)
		{
			temp2[i] = *ptr;
			ptr++;
			i++;
		}
		else
		{
			temp1[i] = *ptr;
			ptr++;
			i++;
		}
		if(*ptr == ' ')
		{
			temp1[i] = *ptr;
			ptr++;
			i++;
			count_blank++;
			if(count_blank>=2)
				i=0;
		}
	}
	
	printf("temp1=%s len = %ld\n",temp1,strlen(temp1));
	printf("temp2=%s len = %ld\n",temp2,strlen(temp2));




	char *commandName = getCommandNameByUart(buffer);
	printf("commandName=%s\n",commandName);

	char *commandValue = getCommandValueByUart(buffer);
	printf("commandValue = %s \n",commandValue);
	const char *ptr1 =commandValue;
	printf("转换带参数的ADC数值:%c\n",*ptr1);  

	char straaa[20] = {0};
	mystrcpy(straaa,"ssssss");
	printf("straaa =%s \n",straaa);

	printf("len = %d\n",mystrlen(commandValue));
	
	
	return 0;
}
