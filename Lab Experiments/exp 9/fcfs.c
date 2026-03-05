#include<stdio.h>
#include<stdlib.h>
struct process{
	int pid;
	int tat;
	int arrival;
	int burst;
	int wt;
};
int main(){
	int n,current=0;
	float st=0.0,sw=0.0;
	struct process p[100];
	struct process temp;
	printf("Enter no of processes :\n");
	scanf("%d",&n);
	printf("Enter pid,arrival time and burst time:\n");
	for(int i=0;i<n;i++){
		printf("process %d",i);
		scanf("%d %d %d",&p[i].pid,&p[i].arrival,&p[i].burst);
	}
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(p[i].arrival>p[j].arrival){
				temp.pid=p[i].pid;
				temp.arrival=p[i].arrival;
				temp.burst=p[i].burst;
				p[i].pid=p[j].pid;
				p[i].arrival=p[j].arrival;
				p[i].burst=p[j].burst;
				p[j].pid=temp.pid;
				p[j].arrival=temp.arrival;
				p[j].burst=temp.burst;
				}}}
				current=p[0].arrival;
				for(int i=0;i<n;i++){
					p[i].wt=current-p[i].arrival;
					current+=p[i].burst;
					p[i].tat=current-p[i].arrival;
					st+=p[i].tat;
					sw+=p[i].wt;
					}
					float at=st/n;
					float aw=sw/n;
					printf("Average TAT =%.2f\n",at);
					printf("Average WT =%.2f\n",aw);
					printf("|\t---\t---\t---\t---\t---\t|\n");
					printf("|\tpid\tarrival\tburst\tTAT\tWT\t|\n");
					printf("|\t---\t---\t---\t---\t---\t|\n");
					for(int i=0;i<n;i++){
					printf("|\t%d\t%d\t%d\t%d\t%d\t|\n",p[i].pid,p[i].arrival,p[i].burst,p[i].tat,p[i].wt);
					}
					printf("|\t---\t---\t---\t---\t---\t|\n");
					return 0;
					}
					
					
