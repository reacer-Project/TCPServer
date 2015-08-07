#include "unp.h"
#include <string.h>
int send_fd(int fd,int sendfd)
{
	char c;
	return write_fd(fd,&c,1,sendfd);
}
