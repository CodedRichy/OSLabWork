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
	msgrcv(msgid, &m1, sizeof(m1.text), 1, 0);
	printf("Received string: %s\n", m1.text);
	int len = strlen(m1.text);
	for(int i = 0; i < len; i++)
	{
		m2.text[i] = m1.text[len - i - 1];
	}
	m2.text[len] = '\0';
	m2.type = 2;
	msgsnd(msgid, &m2, sizeof(m2.text), 0);
	printf("Reversed string sent: %s\n", m2.text);
	return 0;
}
