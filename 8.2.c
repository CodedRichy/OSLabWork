#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    
    if (fork() == 0) { // Process 2: Receiver & Reverser
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        
        int n = strlen(message.msg_text);
        for (int i = 0; i < n / 2; i++) {
            char temp = message.msg_text[i];
            message.msg_text[i] = message.msg_text[n - i - 1];
            message.msg_text[n - i - 1] = temp;
        }
        
        message.msg_type = 2; // Send back as type 2
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        exit(0);
    } else { // Process 1: Sender & Checker
        printf("Enter a string: ");
        scanf("%s", message.msg_text);
        char original[100];
        strcpy(original, message.msg_text);

        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);

        msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0);

        if (strcmp(original, message.msg_text) == 0)
            printf("The string is a Palindrome.\n");
        else
            printf("The string is NOT a Palindrome.\n");

        msgctl(msgid, IPC_RMID, NULL); // Cleanup
    }
    return 0;
}