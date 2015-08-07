#include "unp.h"
#include <string.h>

int recv_fd(int fd)
{
	char buf[2];
	memset(buf,'\0',sizeof(buf));
	int recvfd = -1;
	if(0 > read_fd(fd,buf,sizeof(buf),&recvfd))
	{
		return -1;
	}
	return recvfd;
}
