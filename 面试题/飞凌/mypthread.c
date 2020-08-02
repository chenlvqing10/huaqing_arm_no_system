#include "mypthread.h"
void set_get_pthread_attr(pthread_attr_t pattr)
{

	//线程属性变量的定义
	int detachstate;//线程的分离状态   ××××× 重要
	int schedpolicy;//线程的调度策略
	struct sched_param  schedparam;//线程的调度参数
	int inheritsched;//线程的继承性
	int scope;//线程的作用域
	size_t guardsize;//线程缓冲区大小  ××××× 重要
	int stackaddrset;//线程的栈设置
	size_t stacksize,stacksize1; //typedef  size_t  unsigned int  线程栈带下
	void *stackaddr;//线程栈的大小 ×××××重要
	//size_t cpusetsize;//cpu亲缘性设置大小
	//cpu_set_t  cpuset;//cpu亲缘性设置
	printf("aaaaaa\n");
	//线程属性变量的定义

	//初始化线程属性
	pthread_attr_init(&pattr);
	printf("aaaaaa\n");
	//线程属性变量的定义
	pthread_attr_getdetachstate(&pattr,&detachstate);
	pthread_attr_getguardsize(&pattr,&guardsize);
	pthread_attr_getschedparam(&pattr,&schedparam);
	pthread_attr_getschedpolicy(&pattr,&schedpolicy);
	pthread_attr_getinheritsched(&pattr,&inheritsched);
	pthread_attr_getscope(&pattr,&scope);
	pthread_attr_getstacksize(&pattr,&stacksize);
	pthread_attr_getstack(&pattr,&stackaddr,&stacksize1);
	//pthread_attr_getaffinity_np(&pattr,&cpusetsize,&cpuset);

	//打印线程属性信息
	printf("detachstate = %d\n",detachstate);//默认0=PTHREAD_CREATE_JOINABLE
	printf("guardsize = %ld\n",guardsize);//默认4M
	printf("schedparam = %d\n",schedparam.__sched_priority);//调度参数=0  优先级
	printf("schedpolicy = %d\n",schedpolicy);//调度策略==SCHED_OTHER
	printf("inheritsched =%d\n",inheritsched);//继承性==0
	printf("scope =%d\n",scope);//作用域=0
	printf("stacksize =%ld\n",stacksize);//线程栈大小=8388608
	printf("stackaddr = %p,stacksize1 = %ld\n",stackaddr,stacksize1);//

	//设置线程属性
	pthread_attr_setdetachstate(&pattr,PTHREAD_CREATE_DETACHED);//设置线程分离属性
	pthread_attr_getdetachstate(&pattr,&detachstate);
	printf("detachstate = %d\n",detachstate);//默认0=PTHREAD_CREATE_JOINABLE
	
	pthread_attr_setguardsize(&pattr,8192);
	pthread_attr_getguardsize(&pattr,&guardsize);
	printf("guardsize = %ld\n",guardsize);//默认4M

	struct sched_param  set_schedparam;
	set_schedparam.__sched_priority  = 88;
	pthread_attr_setschedparam(&pattr,&set_schedparam);
	pthread_attr_getschedparam(&pattr,&schedparam);
	printf("schedparam = %d\n",schedparam.__sched_priority);//调度参数=0  优先级????????

	pthread_attr_setschedpolicy(&pattr,SCHED_FIFO);
	pthread_attr_getschedpolicy(&pattr,&schedpolicy);
	printf("schedpolicy = %d\n",schedpolicy);//调度策略==SCHED_OTHER

	pthread_attr_setinheritsched(&pattr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_getinheritsched(&pattr,&inheritsched);
	printf("inheritsched =%d\n",inheritsched);//继承性==0
	
	pthread_attr_setscope(&pattr,PTHREAD_SCOPE_PROCESS);
	pthread_attr_getscope(&pattr,&scope);
	printf("scope =%d\n",scope);//作用域=0?????????????????

	pthread_attr_setstacksize(&pattr,9999999);
	pthread_attr_getstacksize(&pattr,&stacksize);
	printf("stacksize =%ld\n",stacksize);//线程栈大小=8388608

}

//定义一个功能函数 用于资源的读写
void readfile(const char* filename)
{
	int fd = open(filename,O_RDONLY,S_IRWXU|S_IRWXG|S_IRWXO);//file description for read
	if(fd<0)
	{
		perror("open file");
	}
	else
	{
		perror("open file");
	}

	char Buffer_read[300] =  {0};//read bufferd
	size_t BUffer_size = strlen(Buffer_read);
	printf("size:%ld\n",BUffer_size);
	int ret = read(fd,Buffer_read,BUffer_size);
	if(ret<0)
	{
		perror("read file");
	}
	else
	{
		perror("read file");
		printf("Buffer content:%s\n",Buffer_read);
	}

	close(fd);

}

void writefile(const char* filename)
{

	int fd = open(filename,O_RDWR | O_CREAT | O_APPEND,S_IRWXU|S_IRWXG|S_IRWXO);//file description for write
	if(fd<0)
	{
		perror("open file");
	}
	else
	{
		perror("open file");
	}

	char Buffer_w[300000] =  "\nnininninin\njjjjjjjjjjjjjjjjjjj\nsdsfjskdfsdlkfsdkfl\niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n\
		1sdlfjkldsffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n\
		2sdlfjkldsffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n\
		3sdlfjkldsffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n\
		4sdlfjkldsffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n\
		5sdlfjkldsffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n\
		6kkkkkkkkkkkkkkkddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkd\n\
		7kkkkkkkkkkkkkkkddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkd\n\
		8kkkkkkkkkkkkkkkddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkd\n\
		9kkkkkkkkkkkkkkkddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkd\n\
		10kkkkkkkkkkkkkkkddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkd\n\
		11kkkkkkkkkkkkkkkddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkd\n\
		12kkkkkkkkkkkkkkkddddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkd\n\
		13dddddddddddddddddddddddddddddddddddddddddkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkd";//read bufferd
	size_t BUffer_size = strlen(Buffer_w);
	printf("size:%ld\n",BUffer_size);
	int ret = write(fd,Buffer_w,BUffer_size);
	if(ret<0)
	{
		perror("write file");
	}
	else
	{
		perror("write file");
		//printf("Buffer content:%s\n",Buffer_w);
	}
	close(fd);
}


//线程执行函数  读文件内容
void* pthread_handle(void* arg)
{
	pthread_mutex_init(&mutex_lock,NULL);//互斥锁的初始化

	printf("执行线程0的函数\n");
	printf("the arg is %s\n",(char*)arg);
	//调用功能函数
	const char *filename = "./test.txt";
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	//临界区的加锁和解锁
	pthread_mutex_lock(&mutex_lock);
	readfile(filename);
	pthread_mutex_unlock(&mutex_lock);


	printf("********************************************************************************************************************************************************\n");
	return (void*)0;
}


//线程执行函数  写文件
void* pthread_handle1(void* arg)
{
	//初始化互斥锁
	pthread_mutex_init(&mutex_lock,NULL);//互斥锁的初始化

	printf("执行线程1的函数\n");
	printf("the arg is %s\n",(char*)arg);
	
	//调用功能函数
	const char *filename = "./test.txt";
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	
	//临界区的加锁和解锁
	pthread_mutex_lock(&mutex_lock);
	writefile(filename);
	pthread_mutex_unlock(&mutex_lock);
	
	
	
	printf("********************************************************************************************************************************************************\n");
	return (void*)0;
}


//线程执行函数   死锁线程1  
void* pthread1_deadlock(void* arg)
{
	printf("执行死锁线程1\n");

	//申请锁BA
	pthread_mutex_lock(&mutex_lock_B);
	printf("have lock B\n");
	sleep(5);

	pthread_mutex_lock(&mutex_lock_A);
	printf("have lock A\n");

	
	//释放锁AB
	pthread_mutex_unlock(&mutex_lock_A);
	printf("release lock A\n");
	pthread_mutex_unlock(&mutex_lock_B);
	printf("release lock B\n");

	return (void*)0;
}

//线程执行函数   死锁线程2
void* pthread2_deadlock(void* arg)
{
	printf("执行死锁线程2\n");

	//申请锁AB
	pthread_mutex_lock(&mutex_lock_A);
	printf("have lock A\n");
	sleep(5);

	pthread_mutex_lock(&mutex_lock_B);
	printf("have lock B\n");

	//释放锁BA
	pthread_mutex_unlock(&mutex_lock_B);
	printf("release lock B\n");
	pthread_mutex_unlock(&mutex_lock_A);
	printf("release lock A\n");

	return (void*)0;
}




int main(int argc,char* argv[])
{
	//初始化互斥锁
	pthread_mutex_init(&mutex_lock_A,NULL);//互斥锁的初始化
	pthread_mutex_init(&mutex_lock_B,NULL);//互斥锁的初始化
	//线程属性控制代码
//	pthread_t            pid_0;//线程0ID
//	pthread_t            pid_1;//线程1ID
	pthread_t            pid_dead_1;//死锁线程1
	pthread_t            pid_dead_2;//死锁线程2


	//pthread_attr_t       pattr;//线程属性
	//创建线程前设置一些线程的属性    依据什么设置？？？
	//set_get_pthread_attr(pattr);
	
	//创建子线程
//	printf("argv[0]:%s\n",argv[0]);
//	printf("argv[1]:%s\n",argv[1]);
//	printf("argv[2]:%s\n",argv[2]);


	//静态模拟  同步机制一:互斥锁
/*	int ret = pthread_create(&pid_0,NULL,pthread_handle,(void*)argv[1]);
	if(ret == 0)
	{
		perror("create pthread one");
		printf("pid = %ld\n",pid_0);
	}
	else
	{
		perror("create pthread one");
	}
	printf("********************************************************************************************************\n");
	
	ret = pthread_create(&pid_1,NULL,pthread_handle1,(void*)argv[2]);
	if(ret == 0)
	{
		perror("create pthread two");
		printf("pid = %ld\n",pid_1);
	}
	else
	{
		perror("create pthread two");
	}
*/	
	//死锁
	int ret;
	ret = pthread_create(&pid_dead_1,NULL,pthread1_deadlock,NULL);
	if(ret == 0)
	{
		perror("create pthread one for dead lock");
		printf("pid for dead lock = %ld\n",pid_dead_1);
	}
	else
	{
		perror("create pthread one for dead lock");
		
	}

	ret = pthread_create(&pid_dead_2,NULL,pthread2_deadlock,NULL);
	if(ret == 0)
	{
		perror("create pthread two for dead lock");
		printf("pid for dead lock = %ld\n",pid_dead_2);
	}
	else
	{
		perror("create pthread two for dead lock");
		
	}

	
	sleep(5);
	//线程的销毁
//	pthread_exit((void*)&pid_0);
//	pthread_exit((void*)&pid_1);
	pthread_exit((void*)&pid_dead_1);
	pthread_exit((void*)&pid_dead_2);

	return 0;
}
