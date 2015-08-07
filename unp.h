#ifndef UNP_H_
#define UNP_H_
#include <stdlib.h>
#include <unistd.h>
int tcp_connect(const char *host,int port);
int tcp_listen(int port);

int send_fd(int fd,int sendfd);
int recv_fd(int fd);
ssize_t read_fd(int fd,void *ptr,size_t nbytes,int *recvfd);
ssize_t write_fd(int fd,void *ptr,size_t nbytes,int sendfd);

struct child_process_information{
	int pid;
	int unix_fd;
};
void child_process_function();
int worker(int fd);


#endif
