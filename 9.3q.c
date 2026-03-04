#include<stdio.h>

// -------- Structure Definition --------
struct process
{
    int at;   // Arrival Time
    int bt;   // Burst Time
    int rt;   // Remaining Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
};

struct process p[20];

int main()
{
    // -------- Step 1: Declare variables --------
    int n,tq,time=0;
    int queue[50],front=0,rear=0;
    int vis[20]={0};
    float total_wt=0,total_tat=0;

    // -------- Step 2: Read number of processes --------
    printf("Enter number of processes: ");
    scanf("%d",&n);

    // -------- Step 3: Read time quantum --------
    printf("Enter time quantum: ");
    scanf("%d",&tq);

    // -------- Step 4: Input arrival and burst time --------
    for(int i=0;i<n;i++)
    {
        printf("AT BT of P%d: ",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);

        p[i].rt=p[i].bt;   // remaining time = burst time
    }

    // -------- Step 5: Insert processes that arrive at time 0 --------
    for(int i=0;i<n;i++)
        if(p[i].at==0){
            queue[rear++]=i;
            vis[i]=1;
        }

    // -------- Step 6: Round Robin Execution --------
    while(front<rear)
    {
        int i=queue[front];
        front++;

        // Case 1: Process needs more than quantum
        if(p[i].rt>tq){
            time = time + tq;
            p[i].rt = p[i].rt - tq;
        }

        // Case 2: Process finishes
        else{
            time = time + p[i].rt;
            p[i].rt = 0;

            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }

        // -------- Step 7: Add newly arrived processes --------
        for(int j=0;j<n;j++)
            if(p[j].at<=time && !vis[j]){
                queue[rear++]=j;
                vis[j]=1;
            }

        // -------- Step 8: Reinsert process if not finished --------
        if(p[i].rt>0)
            queue[rear++]=i;
    }

    // -------- Step 9: Print results --------
    printf("\nPID AT BT CT TAT WT\n");

    for(int i=0;i<n;i++)
    {
        printf("P%d %d %d %d %d %d\n",
        i+1,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // -------- Step 10: Calculate averages --------
    printf("\nAverage Waiting Time = %.2f", total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat/n);

    return 0;
}