#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	pid_t pid=fork();
	if(pid<0)
	{
		printf("fork failed\n");
	}
	else if(pid==0)
	{
		printf("child process:\n");
		printf("process id of child:%d\n",getpid());
		printf("parent process id of child:%d\n",getppid());
	}
	else
	{
		printf("parent process:\n");
		printf("process id of parent:%d\n",getpid());
		printf("shell id:%d\n",getppid());
	}
	sleep(10);
	return 0;
}
