#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

# define N 5

//1, define macro N
//2 define semaphores

sem_t room;
sem_t chopstick[N];
sem_t mutex;


//3define function

void* philosopher(void * arg){

    //4,extract id
    int id =  *(int*)arg;
    
    while(1){
        printf("Thinking : %d \n" ,id );
        sleep(1);

        sem_wait(&room);

        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id +1) % N]);

        sem_wait(&mutex);
        printf("Im eating : %d \n" , id);
        sem_post(&mutex);

        sleep(2);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);
        sem_post(room);
    }

    return NULL;
}

int main(void){

    pthread_t tid[N];
    int phil[N];
 
//Initialize semaphores in main

    sem_init(&mutex,0,1);
    sem_init(&room,0,N-1);


      for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

        


}
