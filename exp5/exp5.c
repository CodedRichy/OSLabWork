#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	pid_t pid=fork();
	if(pid<0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if(pid==0)
	{
		printf("PCCSL407\n");
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("OPERATING SYSTEMS LAB\n");
		exit(0);
	}
	sleep(10);
	return 0;
}
