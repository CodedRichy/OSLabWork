#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[]){
int sum=0;
if (argc<3){
	printf("Min 2 arguments needed");
	return 1;
	}
	int a =atoi(argv[1]);
	int b =atoi(argv[2]);
	sum=a+b;
	printf("The Sum is %d",sum);
	return 0;
}
