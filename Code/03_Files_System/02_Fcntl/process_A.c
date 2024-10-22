#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char text[16] = {0};
	struct flock fl;

	sprintf(text, "hello world\n");

	if ((fd=open("./text.txt", O_RDWR | O_CREAT, 0666)) == -1)
	{
		printf("can not create file \n");
	}
	else
	{
		printf("create file test.txt\n");
	}
	if(write(fd, text, sizeof(text)-1) == -1)
	{
		printf("Can not write file\n");
		return 0;
	}
	else
	{
		printf("Write file\n");
	}
	fl.l_start =1 ; //offset where the lock begin
	fl.l_len =5;    // number of bytes to lock
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;

	if(fcntl(fd, F_SETLK, &fl)== -1)
	{
		printf("Cannot set write lock byte 1-5\n");
	}
	else
	{
		printf("Set write lock byte 1-5 \n");
	}
	while(1)
	{
		sleep(1);
	}
	close(fd);
	return 0;
}

