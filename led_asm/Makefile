# 定义一些变量
NAME=led_asm_red_green_blue
CROSS_COMPILE = arm-none-linux-gnueabi-
# 编译
CC = $(CROSS_COMPILE)gcc
# 链接 将.o文件链接生成.elf文件
LD = $(CROSS_COMPILE)ld

# 将.elf文件生成.bin 
# .bin 是纯粹的二进制文件
# .elf 包含符号
OBJCOPY = $(CROSS_COMPILE)objcopy

# 规则
all:
	 $(CC) -O0 -g -c $(NAME).S -o $(NAME).o
	@ # -O0:对代码的优化等级
	@ #  -g：添加调试信息
	@ #  -c：只编译不链接
	 $(LD) -Ttext=0x43c00000 $(NAME).o -o $(NAME).elf 
	@ # -Ttext=0x43c00000:指定代码的起始位置
	 $(OBJCOPY) -O binary $(NAME).elf  $(NAME).bin 
	@ # -O binary ： 输出二进制文件

clean:
	rm -rf *.elf *.bin *.o

install:
	@ # 修改为自己的贡献文件夹路径
	cp $(NAME).bin  /mnt/hgfs/share/






