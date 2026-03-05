#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("fork failed");
	return 0;
	}
	else if(pid==0){
		printf("Child process\n");
		printf("Pid :%d\n",getpid());
		printf("PPid :%d\n",getppid());
	return 0;
	}
	else if(pid>0){
		printf("Parent Process\n");
		printf("pid :%d ppid : %d\n",getpid(),getppid());}
	return 0;
}
	
 

