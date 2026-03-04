#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t mutex;
sem_t rw_mutex;
sem_t queue;
int read_count=0;


void *reader(void *arg){
	int id=*(int*)arg;
	sem_wait(&queue);
	sem_wait(&mutex);
	read_count++;
	if(read_count==1)
		sem_wait(&rw_mutex);
	sem_post(&mutex);
	sem_post(&queue);
	printf("reader %d is Reading\n",id);
	sleep(1);
	printf("reader %d has finshed reading\n",id);
	read_count--;
	if(read_count==0)
		sem_post(&rw_mutex);
	sem_post(&mutex);
	return NULL;
}
void *writer(void *arg){
	int id=*(int*)arg;
	sem_wait(&queue);
	sem_wait(&rw_mutex);
	printf("Writer %d is Writing \n",id);
	sleep(2);
	printf("Writer %d has Finished Writing\n",id);
	sem_post(&rw_mutex);
	sem_post(&queue);
	return NULL;
}
int main(){
	pthread_t readers[5],writers[5];
	int id[5];
	sem_init(&mutex,0,1);
	sem_init(&rw_mutex,0,1);
	sem_init(&queue,0,1);
	
	for(int i=0;i<5;i++){
		id[i]=i+1;
		pthread_create(&readers[i],NULL,reader,&id[i]);
		pthread_create(&writers[i],NULL,writer,&id[i]);}
	for(int i=0;i<5;i++){
		pthread_join(readers[i],NULL);
		pthread_join(writers[i],NULL);}
		sem_destroy(&mutex);
		sem_destroy(&rw_mutex);
		sem_destroy(&queue);
		}
	
