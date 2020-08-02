#include <stdio.h>
#define BYTE		unsigned char
#define u32_short	unsigned short
#define u32_int		unsigned int

#define GETBIT(b,i) ( ( b >> i) & 0x1 )
#define MIN(a,b)    ((a<b)?a:b)

//将字符串转换为数字
int StringtoInt(char* string)
{
	u32_int num = 0;
	char* ptr = string;
	while(*ptr != '\0')
	{
		num = (num * 10) + *ptr - '0';
		ptr++;
	}
	return num;
}

int is_Byte(char* string)
{
	u32_int num = 0;//整形
	
	printf("请输入一个字节的数:");
	scanf("%s",string);
	
	//将字符串转换为整形
	num = StringtoInt(string);
	while((num < 0) || (num > 255))//超出范围
	{
		printf("输入的数非法,不是一个字节的，请输入0~255之间的数字\n");
		scanf("%s",string);
		num = StringtoInt(string);
	}
	
	return num;
}

int get_count_bit1(u32_int num)
{
	u32_short  count			 = 0;//bit1计数
	for(int i=0;i<=7;i++)
	{
		printf("i::%d  bit位::%d\n",i,GETBIT(num,i));
		if(GETBIT(num,i))
			count ++;
	}

	return count;
}

int main()
{
	char       string[10]	= {0};//从标准键盘输入  字符串
	u32_int    num			= 0;//转为整形后的字节数

	num = is_Byte(string);//判断是否为字节数，并将合法的字节数转换为整形返回
	printf("num =%d\n",num);

	//打印bit的位数
	printf("字节数%d中含有%d个bit1\n",num,get_count_bit1(num));

	//最小值
	printf("min value = %d\n",MIN(87,99));

	float a = 2;
	int   b = 360;
	int   c = 8;
	a  = c / b * 18.0;
	printf("a=%f\n",a);

	return 0;
}


