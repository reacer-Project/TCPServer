#include "unp.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
int tcp_connect(const char *host,int port)
{
	struct sockaddr_in servaddr;
	int fd;
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == fd)
	{
		printf("errno=%d\n",errno);
		perror("socket error");
		fprintf(stderr,"create socket error %d line in %s file\n",__LINE__,__FILE__);
		exit(-1);
	}
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	if(inet_pton(AF_INET,host,&servaddr.sin_addr)!=1)
	{
		perror("inet_pton error");
		fprintf(stderr,"inet_pton error %d line in %s file\n",__LINE__,__FILE__);
		exit(-1);
	}
	if(0!=connect(fd,(struct sockaddr *)&servaddr,sizeof(servaddr)))
	{
		perror("connect error");
		fprintf(stderr,"connect error %d line in %s file\n",__LINE__,__FILE__);
		exit(-1);
	}	
	
	return fd;
}
