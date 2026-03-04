#include<stdio.h>
#include<time.h>
#include<unistd.h>
int main(){
time_t now;
time(&now);
printf("Current suystem time: %s",ctime(&now));
//for(long long i=0;i<10000;i++)
sleep(60);
return 0;
}
