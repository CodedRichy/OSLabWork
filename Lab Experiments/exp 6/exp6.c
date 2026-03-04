#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
void main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("fork failed");
		exit(1);
	}
	else if(pid==0){
		printf("Child process Executing my adder\n");
		char *arg[]={"./myadder","10","20",NULL};
		execvp(arg[0],arg);
		exit(1);
	}
	else if(pid>0){
		printf("child completed execution\n");
		wait(NULL);
		exit(1);
	
}}
	
 

