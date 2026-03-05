#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct msg
{
	long type;
	char text[100];
};
int main()
{
	key_t key = ftok("msgfile", 65);
	int msgid = msgget(key, 0666 | IPC_CREAT);
	struct msg m1, m2;
	printf("Enter a string: ");
	scanf("%s", m1.text);
	m1.type = 1;
	msgsnd(msgid, &m1, sizeof(m1.text), 0);
	msgrcv(msgid, &m2, sizeof(m2.text), 2, 0);
	if(strcmp(m1.text, m2.text) == 0)
	{
		printf("string is a palindrome\n");
	}
	else
	{
		printf("Not a palindrome\n");
	}
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
