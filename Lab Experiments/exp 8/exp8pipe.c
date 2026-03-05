#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<math.h>
int main(){
	int a,b,c;
	int fd[2];
	printf("Enter values of a b and c");
	scanf("%d %d %d",&a,&b,&c);
	pipe(fd);
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("fork failed\n");}
	else if(pid==0){
		close(fd[0]);
		int ac=4*a*c;
		write(fd[1],&ac,sizeof(ac));
		close(fd[1]);
	}
	else if(pid>0){
	close(fd[1]);
	int ac;
	int bsq=b*b;
	read(fd[0],&ac,sizeof(ac));
	int disc=bsq-ac;
	if(disc<0){
		printf("imaginary roots");
		}
		else{
		printf("square root of discriminent is %.2f",sqrt(disc));
		close(fd[0]);}
		wait(NULL);}
	return 0;}


