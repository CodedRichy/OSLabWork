#include <stdio.h>

struct process
{
    int pid, at, bt, rt, ct, tat, wt;
} p[20];

int main()
{
    int n, tq;
    int queue[50], front = 0, rear = 0;
    int vis[20] = {0};

    int time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter time quantum: ");
    scanf("%d",&tq);

    for(int i=0;i<n;i++)
    {
        p[i].pid = i+1;

        printf("Enter AT of P%d: ",i+1);
        scanf("%d",&p[i].at);

        printf("Enter BT of P%d: ",i+1);
        scanf("%d",&p[i].bt);

        p[i].rt = p[i].bt;
    }

    while(completed < n)
    {
        for(int i=0;i<n;i++)
        {
            if(p[i].at <= time && vis[i]==0)
            {
                queue[rear++] = i;
                vis[i] = 1;
            }
        }

        if(front == rear)
        {
            time++;
            continue;
        }

        int idx = queue[front++];

        if(p[idx].rt <= tq)
        {
            time += p[idx].rt;
            p[idx].rt = 0;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;
        }
        else
        {
            p[idx].rt -= tq;
            time += tq;
        }

        for(int i=0;i<n;i++)
        {
            if(p[i].at <= time && vis[i]==0)
            {
                queue[rear++] = i;
                vis[i] = 1;
            }
        }

        if(p[idx].rt > 0)
            queue[rear++] = idx;
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nAverage WT = %.2f",avg_wt/n);
    printf("\nAverage TAT = %.2f\n",avg_tat/n);

    return 0;
}