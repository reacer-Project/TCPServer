#include "unp.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int tcp_listen(int port)
{
	int listenfd;
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd < 0)
	{
		perror("socket error");
		fprintf(stderr,"socket error  %d line in %s file\n ",__LINE__,__FILE__);
		exit(-1);
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))== -1)
	{
		perror("bind error");
		exit(-1);
	}
	if(listen(listenfd,10)==-1)
	{
		perror("listenfd error");
		exit(-1);
	}
	return listenfd;
}
