#include<stdio.h>
#include<ctype.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
	struct data{
		char s1[100];
		char s2[100];
		char s3[100];
		char result[400];
		};
	int main(){
		int shmid;
		creat("shared_key.txt",0666);
		key_t key =ftok("shared_key.txt",65);
		shmid=shmget(key,sizeof(struct data),IPC_CREAT|0666);
		if(shmid<0){
			perror("shmget failed\n");
			return 1;}
			struct data *shm=(struct data*)shmat(shmid,NULL,0);
			printf("Enter the First String:");
			scanf("%s",shm->s1);
			printf("Enter the 2nd String:");
			scanf("%s",shm->s2);
			printf("Enter the 3rd String:");
			scanf("%s",shm->s3);
			printf("Waiting...");
			fflush(stdout);
			sleep(15);
			flipcase(shm->result);
			printf("flipped result: %s \n",shm->result);
			shmdt(shm);
			shmctl(shmid,IPC_RMID,NULL);
			return 0;
			}
			
	void flipcase(char* str){
		for(int i=0;i<strlen(str);i++){
			if(isupper(str[i])){
				str[i]=tolower(str[i]);
				}
				else if (islower(str[i])){
					str[i]=toupper(str[i]);
					}
					}}
			
