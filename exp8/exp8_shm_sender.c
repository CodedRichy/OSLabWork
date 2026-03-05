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
	int shmid=shmget(key,sizeof(struct shared_data),0666 | IPC_CREAT);
	struct shared_data *data=(struct shared_data*)shmat(shmid,NULL,0);
	data->ready=0;
	printf("enter 1st string\n");
	scanf("%s",data->s1);
	printf("enter 2nd string\n");
	scanf("%s",data->s2);
	printf("enter 3rd string\n");
	scanf("%s",data->s3);
	data->ready=1;
	while(data->ready!=2)
		sleep(1);
	for(int i=0;data->result[i];i++)
	{
		if(islower(data->result[i]))
		{
			data->result[i]=toupper(data->result[i]);
		}
		else if(isupper(data->result[i]))
		{
			data->result[i]=tolower(data->result[i]);
		}
	}
	printf("string flipped \n%s\n",data->result);
	shmdt(data);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
