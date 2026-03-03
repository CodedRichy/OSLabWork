// 1. Include necessary libraries for I/O, Threads, and Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// while using semaphores we should always pass as & not as copy as the original resource must be blocked;

// 2. Define macro for number of philosophers
#define N 5 //#define does NOT use a semicolon.

// 3. Declare global semaphores for room, chopsticks, and mutex
sem_t room; 
sem_t chopstick[N]; //1 means its on table , 0 means its not on table
sem_t mutex; //used to protect the printf

// 4. Define the philosopher thread function
void* philosopher(void* arg)
{
    // 5. Extract the unique ID from the passed argument
    int id = *(int*)arg;

    // 6. Enter infinite loop of Thinking and Eating
    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // 7. Wait for permission to enter the room (Limit N-1)
        sem_wait(&room);

        // 8. Acquire left and right chopsticks
        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);

        // 9. Protect the critical section (printing) with mutex
        sem_wait(&mutex);
        printf("Philosopher %d is eating\n", id);
        sem_post(&mutex);

        sleep(2);

        // 10. Release both chopsticks after eating
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        // 11. Leave the room to allow others in
        sem_post(&room);
    }

    return NULL;
}

// 12. Main function to initialize and start threads
int main()
{
    // 13. Declare thread IDs and philosopher ID array
    pthread_t tid[N];
    int phil[N];

    // 14. Initialize room (value 4) and mutex (value 1) semaphores
    sem_init(&room, 0, N - 1);
    sem_init(&mutex, 0, 1);

    // 15. Initialize each chopstick semaphore to 1 (available)
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1); // 0 to indicate all these threads are for one program and 1 is the intial value 

    // 16. Create philosopher threads and pass their IDs
    for (int i = 0; i < N; i++)
    {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]); // 1st argument : a pointer to a pthread variable , NULL means gimme basic ass thread , phiosopher here means the function the thread should run at the time its born ,&phil[i] a pointer to the variable u should pass to the function
    }

    // 17. Join threads to keep the main process alive
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL); //tells to hit return 0 if every thread finsihes its job

    return 0;
}