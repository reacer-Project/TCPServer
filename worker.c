#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "unp.h"
#define MAX_TASK_NUM 32
static int eco_str(int);
static task_function task[MAX_TASK_NUM];
static int task_num=0;
static void echo_str(int fd,void *data);
void add_task();
int worker(int fd)
{
	int index;
	int status=0;
	add_task();
	for(index=0;index<task_num && status==0;index++)
		task[index](fd,&status);
	return status;
}
void add_task()
{
	int index = 0;
	task[index++] = echo_str;
	task_num = index;
	return;
}
static void echo_str(int fd,void *data)
{
	char buf[1024];
	int *status = (int *)data;
	memset(buf,'\0',sizeof(buf)-1);
	int n = read(fd,buf,sizeof(buf)-1);
	if(n == 0)
	{
		*status = -1;
		return;
	}
	else if(n < 0)
	{
		*status = -2;
	}
	else{
		printf("receved messgae by child process %d\nmessage:%s\n",getpid(),buf);
		if(n != write(fd,buf,n))
		{
			*status = -1;
			return;
		}
	}
	*status = 0;
	return;
}
static int eco_str(int fd)
{
	char buf[1024];
	memset(buf,'\0',sizeof(buf)-1);
	int n = read(fd,buf,sizeof(buf)-1);
	if(n == 0)
	{
		return -1;
	}
	else if(n < 0)
		return -2;
	else{
		printf("receved messgae by child process %d\nmessage:%s\n",getpid(),buf);
		if(n !=write(fd,buf,n))
			return -1;
	}
	return 0;
	
}
