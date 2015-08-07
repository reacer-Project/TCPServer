#include "unp.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
static int listenfd;
int unix_fd=-1;
struct child_process_information child_process[4];
static int rand_digit=0;
int main(int argc,char **argv)
{
	listenfd = tcp_listen(8080);
	if(listenfd < 0)
	{
		fprintf(stderr,"tcp_listen error\n");
		exit(-1);
	}
	printf("listenfd=%d\n",listenfd);	
	int i=0;
	int pid;
	for(i=0;i<4;i++)
	{
		int fd[2];
		if(socketpair(AF_LOCAL,SOCK_STREAM,0,fd)!=0)
		{
			perror("socketpair error");
			exit(-1);
		}
		pid = fork();
		if(pid>0)
		{
			child_process[i].pid=pid;
			child_process[i].unix_fd=fd[0];
			close(fd[1]);
		}
		else if(pid == 0){
			unix_fd = fd[1];
			close(fd[0]);
			break;
		}
		else{
			perror("fork error");
			exit(-1);
		}
	}
	
	if(pid == 0)
	{
		close(listenfd);
		child_process_function();	
	}
	else if(pid>0)
	{
		while(1)
		{
			int fd = accept(listenfd,NULL,NULL);
			if(fd < 0)
			{
				perror("accept failed");
				continue;
			}
			else{
				printf("recved a new client by parent %d\n",getpid());
				int i= rand_digit++%4;
				if(-1==send_fd(child_process[i].unix_fd,fd))
				{
					perror("send_fd error");
					fprintf(stderr,"send_fd error");
				}
				printf("send a new client to child process %d\n",child_process[i].pid);
				close(fd);
			}
		}
	}	
	return 0;	
}
