#ifndef     __MYPTHREAD__
#define     __MYPTHREAD__

//头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <features.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//变量,常量，结构体定义

void set_get_pthread_attr(pthread_attr_t pattr);
void readfile(const char* filename);
void writefile(const char* filename);

//多线程的同步机制
pthread_mutex_t mutex_lock;//声明一个互斥锁

pthread_cond_t  //条件变量

//死锁的实现
pthread_mutex_t mutex_lock_A;//锁A
pthread_mutex_t mutex_lock_B;//锁B


void* pthread2_deadlock(void* arg);
void* pthread1_deadlock(void* arg);

#endif
