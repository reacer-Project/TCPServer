#include <string.h>
#include <stdio.h>
#include <unistd.h>

static int eco_str(int);
int worker(int fd)
{
	return(eco_str(fd));
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
