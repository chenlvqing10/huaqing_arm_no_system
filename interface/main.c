#include <s5p6818.h>

void delay_ms(unsigned int ms)
{
	unsigned int i,j;
	for(i = 0; i < ms; i++)
		for(j = 0; j < 1800; j++);
}

int main()
{
	while(1)
	{
		printf("hello world!\n");
	}
	return 0;
}
