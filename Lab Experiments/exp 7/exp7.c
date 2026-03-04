#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
double mean=0.0;
double median=0.0;
double stddev=0.0;
double least=0.0;
int *numbers;
int count;
void *compute_mean(void *arg);
void *compute_median(void *arg);
void *compute_stddev(void *arg);
void *compute_mini(void *arg);
int compare(const void *a,const void *b);
int main(int argc,char* argv[]){
	if(argc<2){
		printf("usage:%s<list of integers>\n",argv[0]);
		return(1);
		}
	count=argc-1;
	numbers=(int*)malloc(count *sizeof(int));
	for(int i=0;i<count;i++){
		numbers[i]=atoi(argv[i+1]);
		}
	pthread_t tid1,tid2,tid3,tid4;
	pthread_create(&tid1,NULL,compute_mean,NULL);
	pthread_create(&tid2,NULL,compute_median,NULL);
	pthread_create(&tid3,NULL,compute_stddev,NULL);
	pthread_create(&tid4,NULL,compute_mini,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	printf("Mean  =%.2f\n",mean);
	printf("Median  =%.2f\n",median);
	printf("SD  =%.2f\n",stddev);
	printf("Least =%.2f\n",least);
	free(numbers);
	return 0;
	}
void *compute_mean(void *arg){
	int sum=0;
	for(int i=0;i<count;i++){
		sum+=numbers[i];
		}
	mean=(double)sum/count;
	pthread_exit(NULL);
	}
void *compute_median(void *arg){
	int *temp=(int*)malloc(count*sizeof(int));
	for(int i=0;i<count;i++){
	temp[i]=numbers[i];
	}
	qsort(temp,count,sizeof(int),compare);
	if(count%2==0){
		median=(temp[count/2-1]+temp[count/2])/2.0;
		}
	else{
		median=temp[count/2];
		}
	free(temp);
	pthread_exit(NULL);
	}
	void *compute_stddev(void *arg){
		double sum=0.0;
		for(int i=0;i<count;i++){
			sum+=pow(numbers[i]-mean,2);
			}stddev=sqrt(sum/count);
			pthread_exit(NULL);
			}
	int compare(const void *a,const void *b){
		return(*(int*)a-*(int*)b);
		}
	void *compute_mini(void *arg){
		int *temp=(int*)malloc(count*sizeof(int));
	for(int i=0;i<count;i++){
	temp[i]=numbers[i];
	}
	qsort(temp,count,sizeof(int),compare);
	least=temp[0];}

