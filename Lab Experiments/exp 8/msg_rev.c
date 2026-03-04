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
	msgrcv(msgid,&message,sizeof(message.msg_text),1,0);
	int len=strlen(message.msg_text);
	for(int i=0;i<len;i++){
		original.msg_text[i]=message.msg_text[len-i-1];
		}
	original.msg_text[len]='\0';
	original.msg_type=2;
	msgsnd(msgid,&original,sizeof(original.msg_text),0);
	printf("Message Recived");
	return 0;
	
	}
