#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
struct shared_data
{
	char s1[50];
	char s2[50];
	char s3[50];
	char result[200];
	int ready;
};
int main()
{
	key_t key=ftok("shmfile",65);
	int shmid=shmget(key,sizeof(struct shared_data),0666);
	struct shared_data* data=(struct shared_data*)shmat(shmid,NULL,0);
	while(data->ready!=1)
		sleep(1);
	sprintf(data->result,"%s%s%s",data->s1,data->s2,data->s3);
	data->ready=2;
	shmdt(data);
	printf("string concatenated and sent\n");
	return 0;
}
