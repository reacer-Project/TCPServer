#include "unp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int fd = tcp_connect("127.0.0.1",8080);
	char *buf[1];
	*buf = NULL;
	char buf1[1024];
	while(1)
	{
		size_t n = 1024;
		getline(buf,NULL,stdin);
		write(fd,buf,n);
		memset(buf1,'\0',1024);
		read(fd,buf1,1024);
		printf("%s\n",buf1);
	}
	return 0;
}
