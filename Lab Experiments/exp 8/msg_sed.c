#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
struct msg{
	long msg_type;
	char msg_text[100];
	};
int main(){
	struct msg message,original;
	key_t key=ftok("progfile",65);
	int msgid=msgget(key,0666|IPC_CREAT);
	printf("Enter the string");
	scanf("%s",message.msg_text);
	strcpy(original.msg_text,message.msg_text);
	message.msg_type=1;
	msgsnd(msgid,&message,sizeof(message.msg_text),0);
	msgrcv(msgid,&message,sizeof(message.msg_text),2,0);
	printf("reversed string received:%s\n",message.msg_text);
	if(strcmp(original.msg_text,message.msg_text)==0){
		printf("the string is palindrome\n");
		}
	else{
		printf("the string is not palindrome\n");}
		msgctl(msgid,IPC_RMID,NULL);
		return 0;
		}
