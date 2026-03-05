#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	pid_t pid=fork();
	if(pid<0)
	{
		printf("process failed");
		exit(0);
	}
	else if(pid==0)
	{
		printf("child process executing myadder.....\n");
		char* args[]={"./myadder","10","20",NULL};
		execvp(args[0],args);
		printf("\n");
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("child completed execution\n");
		exit(0);
	}
	sleep(10);
	return(0);
}
