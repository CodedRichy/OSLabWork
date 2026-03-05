#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define N 5 // Number of philosophers and chopsticks
sem_t room; // Semaphore to limit the number of philosophers in the dining room
sem_t chopstick[N]; // Semaphores representing each chopstick
sem_t mutex; // Semaphore to provide mutual exclusion for printing

// Function executed by each philosopher thread
void* philosopher(void* num) {
    int id = *(int*)num; // Get the philosopher's ID
    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", id);
        sleep(1); // Simulate thinking time
        
        sem_wait(&room);  // Wait to enter dining room (max N-1 can enter to prevent deadlock)
        sem_wait(&chopstick[id]);              // Wait to pick up the left chopstick
        sem_wait(&chopstick[(id + 1) % N]);    // Wait to pick up the right chopstick
        
        // Critical section to print eating status without being interrupted
        sem_wait(&mutex);
        printf("Philosopher %d is eating\n", id);
        sem_post(&mutex);
        
        sleep(2); // Simulate eating time
        
        sem_post(&chopstick[id]); // Put down the left chopstick
        sem_post(&chopstick[(id + 1) % N]); // Put down the right chopstick
        sem_post(&room);  // Leave dining room
    }
}

int main() {
    pthread_t tid[N]; // Array to hold thread IDs
    int phil[N]; // Array to hold philosopher IDs
    
    // Initialize the room semaphore to N - 1 (allow only 4 philosophers) to prevent deadlock
    sem_init(&room, 0, N - 1);   
    // Initialize the mutex semaphore to 1
    sem_init(&mutex, 0, 1);
    
    // Initialize each chopstick semaphore to 1 (available)
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);
        
    // Create a thread for each philosopher
    for (int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }
    
    // Wait for all philosopher threads to finish (they run infinitely in this code)
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);
        
    return 0;
}
