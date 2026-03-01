#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <ctype.h>

struct shared_data {
    int status; // 0: P1 writing, 1: P2 processing, 2: P1 reading result
    char s1[50], s2[50], s3[50];
    char result[150];
};

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(struct shared_data), 0666 | IPC_CREAT);
    struct shared_data *data = (struct shared_data*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) { // Process 2: Concatenator
        while (data->status != 1); // Wait for P1
        
        sprintf(data->result, "%s %s %s", data->s1, data->s2, data->s3);
        
        data->status = 2; // Signal P1
        shmdt(data);
        exit(0);
    } else { // Process 1: Manager
        data->status = 0;
        printf("Enter three strings:\n");
        scanf("%s %s %s", data->s1, data->s2, data->s3);
        
        data->status = 1; // Signal P2
        
        while (data->status != 2); // Wait for P2
        
        for (int i = 0; data->result[i] != '\0'; i++) {
            if (isupper(data->result[i])) data->result[i] = tolower(data->result[i]);
            else if (islower(data->result[i])) data->result[i] = toupper(data->result[i]);
        }
        
        printf("Final Concatenated and Flipped String: %s\n", data->result);
        
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}