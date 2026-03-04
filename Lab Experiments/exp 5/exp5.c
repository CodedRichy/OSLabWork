#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("fork failed\n");
		exit(1);}
	else if(pid==0){
		printf("Child Process\n");
		printf("PCCSL407\n");
		exit(1);
	return 0;
	}
	else if(pid>0){
	printf("Parent Process\n");
		wait(NULL);
		printf("OS lab\n");
		
		exit(1);
	return 0;}
}
