#include <stdio.h>
#include <stdlib.h>
struct process
{
	int pid;
	int arrival;
	int burst;
	int tat;
	int wt;
};
int main()
{
	int n,current=0;
	float stat=0.0,swt=0.0;
	struct process p[100];
	struct process temp;
	printf("enter the no. of process\n");
	scanf("%d",&n);
	printf("enter the pid,arrival time and burst time respectively\n");
	for(int i=0;i<n;i++)
	{
		printf("process %d: ",i+1);
		scanf("%d %d %d",&p[i].pid,&p[i].arrival,&p[i].burst);
	}
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(p[i].arrival>p[j].arrival)
			{
				temp.pid=p[i].pid;
				temp.arrival=p[i].arrival;
				temp.burst=p[i].burst;
				p[i].pid=p[j].pid;
				p[i].arrival=p[j].arrival;
				p[i].burst=p[j].burst;
				p[j].pid=temp.pid;
				p[j].arrival=temp.arrival;
				p[j].burst=temp.burst;
			}
		}
	}
	current=p[0].arrival;
	for(int i=0;i<n;i++)
	{
		p[i].wt=current-p[i].arrival;
		current+=p[i].burst;
		p[i].tat=current-p[i].arrival;
		stat+=p[i].tat;
		swt+=p[i].wt;
	}
	float avg_tat=stat/n;
	float avg_wt=swt/n;
	printf("|\tpid\tarrival\tburst\ttat\twt\t|\n");
	for(int i=0;i<n;i++)
	{
		printf("|\t%d\t%d\t%d\t%d\t%d\t|\n",p[i].pid,p[i].arrival,p[i].burst,p[i].tat,p[i].wt);
	}
	printf("\n");
	printf("average TAT is %f\n",avg_tat);
	printf("average WT is %f\n",avg_wt);
	return 0;
}
