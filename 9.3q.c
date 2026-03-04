#include <stdio.h>

// -------- STEP 1: Define process structure --------
struct process
{
    int pid, at, bt, rt, ct, tat, wt;
} p[50];

int main()
{
    // -------- STEP 2: Declare variables --------
    int n, tq;
    int queue[100];
    int front = 0, rear = 0;

    int time = 0, completed = 0;
    int i;

    // -------- STEP 3: Input number of processes --------
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // -------- STEP 4: Input time quantum --------
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    // -------- STEP 5: Input arrival time and burst time --------
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        // Remaining time initially equals burst time
        p[i].rt = p[i].bt;
    }

    // -------- STEP 6: Insert processes arriving at time 0 into ready queue --------
    for (i = 0; i < n; i++)
        if (p[i].at == 0)
            queue[rear++] = i;

    // -------- STEP 7: Continue scheduling until all processes finish --------
    while (completed < n)
    {
        // -------- STEP 8: Check if CPU is idle --------
        if (front == rear)
        {
            // No process in ready queue → increase time
            time++;

            // Check if any process arrives at this time
            for (i = 0; i < n; i++)
                if (p[i].at == time)
                    queue[rear++] = i;

            continue;
        }

        // -------- STEP 9: Remove process from ready queue --------
        int idx = queue[front++];

        // -------- STEP 10: Execute process for time quantum --------
        if (p[idx].rt <= tq)
        {
            // Process finishes within time quantum
            time += p[idx].rt;
            p[idx].rt = 0;

            // Calculate completion time
            p[idx].ct = time;

            // Calculate turnaround time
            p[idx].tat = p[idx].ct - p[idx].at;

            // Calculate waiting time
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;
        }
        else
        {
            // Execute only for time quantum
            time += tq;
            p[idx].rt -= tq;
        }

        // -------- STEP 11: Add processes that arrived during execution --------
        for (i = 0; i < n; i++)
            if (p[i].at > time - tq && p[i].at <= time)
                queue[rear++] = i;

        // -------- STEP 12: If process not finished, reinsert into queue --------
        if (p[idx].rt > 0)
            queue[rear++] = idx;
    }

    // -------- STEP 13: Display result table --------
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    float total_wt = 0, total_tat = 0;

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // -------- STEP 14: Print average times --------
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}