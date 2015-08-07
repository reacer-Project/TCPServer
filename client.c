#include "unp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int fd = tcp_connect("127.0.0.1",8080);
	char buf[1024];
	while(1)
	{
		memset(buf,'\0',sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		write(fd,buf,strlen(buf));
		memset(buf,'\0',1024);
		read(fd,buf,1024);
		printf("%s\n",buf);
	}
	return 0;
}
