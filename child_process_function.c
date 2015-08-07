#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "unp.h"
extern int unix_fd;
int epfd;
#define MAX_EVENT_NUMBER 1024
struct epoll_event evlist[MAX_EVENT_NUMBER];
void child_process_function()
{
	int event_number=0;
	epfd = epoll_create(MAX_EVENT_NUMBER);
	if(epfd < 0)
	{
		perror("epoll_create error");
		exit(-1);
	}
	struct epoll_event ev;
	ev.data.fd = unix_fd;
	ev.events = EPOLLIN;
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,unix_fd,&ev)==-1)
	{
		perror("epoll_ctl error");
		exit(-1);
	}
	event_number++;
	while(event_number>0)
	{
		printf("child process %d epoll_wait start\n",getpid());
		int ready = epoll_wait(epfd,evlist,MAX_EVENT_NUMBER,-1);
		printf("child process %d wake up,get a event\n",getpid());
		if(ready == -1)
		{
			if(errno == EINTR)
				continue;
			else
			{
				perror("epoll_wait error");	
				exit(-1);
			}
		}
		int i;
		for(i=0;i<ready;i++)
		{
			if(evlist[i].events & EPOLLIN && evlist[i].data.fd == unix_fd)
			{//接收新的链接 
				int fd = recv_fd(unix_fd);
				if(fd < 0)
				{
					perror("recv_fd error");
					close(unix_fd);
					continue;
				}
				ev.data.fd = fd;
				ev.events = EPOLLIN;
				if(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev)==-1)
				{
					perror("add event error");
					close(fd);
					continue;
				}
				event_number++;
			}
			else if(evlist[i].events & EPOLLIN)
			{//处理可读事件
				int ret = worker(evlist[i].data.fd);
				if(ret != 0)
				{
					close(evlist[i].data.fd);
					event_number--;
				}	
			}
			else if(evlist[i].events & (EPOLLHUP | EPOLLERR))
			{//处理错误事件,关闭链接
				close(evlist[i].data.fd);
				event_number--;	
			}
		}
	}
	return;
	
}
