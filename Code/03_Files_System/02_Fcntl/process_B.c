#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char text[10] = {0};
	struct flock fl;

	sprintf(text, "TienMT");

	if ((fd = open("./test.txt", O_RDWR)) == -1)
	{
		printf("Can not open file \n");
		return 0;
	}
	else
	{
		printf("Open file test.txt\n");
	}

	fl.l_start = 1;			// offset where the lock begins
	fl.l_len = 5;			// number of bytes to lock
	fl.l_type = F_WRLCK;	// Lock type: F_RDLCK, F_WRLCK, F_UNLCK
	fl.l_whence = SEEK_SET; // SEEK_SET, SEEK_CUR, SEEK_END

	if (fcntl(fd, F_SETLK, &fl) == -1)
	{
		printf("Can not write lock byte 1-5\n");
	}
	else
	{
		printf("Lock byte 0-5\n");
	}
	fl.l_start = 6;			// offset where the lock begins
	fl.l_len = 6;			// number of bytes to lock
	fl.l_type = F_WRLCK;	// Lock type: F_RDLCK, F_WRLCK, F_UNLCK
	fl.l_whence = SEEK_SET; // SEEK_SET, SEEK_CUR, SEEK_END

	if (fcntl(fd, F_SETLK, &fl) == -1)
	{
		printf("Can not set write lock byte 6-11\n");
	}
	else
	{
		printf("Set write lock byte 6-11\n");
		lseek(fd, 6, SEEK_SET);
		if (write(fd, text, sizeof(text) - 1) == -1)
		{
			printf("Can not write file\n");
			return 0;
		}
		else
		{
			printf("Write file\n");
		}
	}
	close(fd);
	return 0;
}

