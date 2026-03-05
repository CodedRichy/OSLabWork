#include <stdio.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	if(argc<3)
	{
		printf("enter 3 arguments\n");
		return 1;
	}
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	printf("sum:%d\n",a+b);
	return 0;
}

