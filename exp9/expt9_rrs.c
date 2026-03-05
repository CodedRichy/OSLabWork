#include <stdio.h>
int q[100];
int f = -1, r = -1, n, tq;
struct process{
	int pid, at, bt, rt, ct, tat, wt;
	};
struct process p[100];
	int isEmpty(){
	return (f == -1);
          }
int isFull()
	{
	return ((r + 1) % n == f);
	}
void enqueue(int item)
	{
	if (isFull())
	return;
	if (f == -1)
		f = r = 0;
	else
		r = (r + 1) % n;
		q[r] = item;
}
	int dequeue()
{
	int item;
	if (isEmpty())
	return -1;
	item = q[f];if (f == r)
	f = r = -1;
	else
	f = (f + 1) % n;
	return item;
}
void print_process(){
	int i, total_wt = 0, total_tat = 0;
	float avg_wt, avg_tat;
	printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
	for (i = 0; i < n; i++){
	printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
	p[i].pid, p[i].at, p[i].bt,
	p[i].ct, p[i].tat, p[i].wt);
	total_wt += p[i].wt;
	total_tat += p[i].tat;
}
	avg_wt = (float)total_wt / n;
	avg_tat = (float)total_tat / n;
	printf("\n\nAverage Waiting Time = %.2f", avg_wt);
	printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
	}
void rr(){
	int time = 0, completed = 0, i, j;
	int visited[100], current;
	int last_pid = -1, start_time = 0;
	for (i = 0; i < n; i++)
		visited[i] = 0;
	printf("\nGANTT CHART DATA");
	printf("\nPID\tSTART\tEND\n");
	while (completed < n){
	for (i = 0; i < n; i++){
		if (p[i].at <= time && visited[i] == 0){
		enqueue(i);
		visited[i] = 1;
		}
}
	current = dequeue();
	if (current == -1){
	time++;
	continue;
}
	if (last_pid != current){
		if (last_pid != -1)
		printf("P%d\t%d\t%d\n", last_pid, start_time, time);
		start_time = time;
		last_pid = current;
	}
	if (p[current].rt < tq){
		int old_time = time;
		time += p[current].rt;
		p[current].rt = 0;
		for (j = 0; j < n; j++){
			if (p[j].at > old_time && p[j].at <= time && visited[j] == 0){
				enqueue(j);
				visited[j] = 1;
        }
}
	p[current].ct = time;
	p[current].tat = p[current].ct - p[current].at;p[current].wt = p[current].tat - p[current].bt;
	completed++;
	}
	else
	{
	int old_time = time;
	time += tq;
	p[current].rt -= tq;
	for (j = 0; j < n; j++){
		if (p[j].at > old_time && p[j].at <= time && visited[j] == 0)
		{
		enqueue(j);
		visited[j] = 1;
      }
}
		enqueue(current);
      }
}
	if (last_pid != -1)
	printf("P%d\t%d\t%d\n", last_pid, start_time, time);
	print_process();
}
int main(){
	int i;
	printf("Enter number of processes: ");
	scanf("%d", &n);
	printf("Enter time quantum: ");
	scanf("%d", &tq);
	for (i = 0; i < n; i++){
	p[i].pid = i + 1;
	printf("Enter arrival time of P%d: ", i + 1);
	scanf("%d", &p[i].at);
	printf("Enter burst time of P%d: ", i + 1);scanf("%d", &p[i].bt);
	p[i].rt = p[i].bt;
}
rr();
return 0;
}
