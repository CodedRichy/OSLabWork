#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
int main() 
{
	int a,b,c;
	printf("enter a,b,c\n");
	scanf("%d %d %d",&a,&b,&c);
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0) 
	{
		close(fd[0]); 
		int four_ac = 4 * a * c;
		write(fd[1], &four_ac, sizeof(four_ac));
		close(fd[1]);
	}
	else 
	{
		close(fd[1]);
		int four_ac;
		read(fd[0], &four_ac, sizeof(four_ac));
		close(fd[0]);
		wait(NULL);
		int b2 = b * b;
		int discriminant = b2 - four_ac;
		float result = sqrt(discriminant);
		printf("The discriminant is = %d\n",discriminant);
		printf("The result is = %f\n", result);
	}
	return 0;
}

