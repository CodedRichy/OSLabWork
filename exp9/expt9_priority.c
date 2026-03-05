#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, arrival, burst, priority;
    int start, end, TAT, WT;
    int done;
};

int main() {
    int n, i, time = 0, completed = 0;
    float ST = 0, SW = 0;
    struct process p[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter pid, arrival time, burst time, priority respectively\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d %d",
              &p[i].pid,
              &p[i].arrival,
              &p[i].burst,
              &p[i].priority);
        p[i].done = 0;
    }

    while (completed < n) {
        int idx = -1;
        int best_pr = -1;

        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time) {
                if (p[i].priority > best_pr) {
                    best_pr = p[i].priority;
                    idx = i;
                }
            }
        }


        p[idx].start = time;
        time += p[idx].burst;
        p[idx].end = time;
        p[idx].TAT = p[idx].end - p[idx].arrival;
        p[idx].WT = p[idx].TAT - p[idx].burst;
        p[idx].done = 1;

        ST += p[idx].TAT;
        SW += p[idx].WT;
        completed++;
    }

    printf("\nAverage Turnaround Time: %.2f\n", ST / n);
    printf("Average Waiting Time: %.2f\n", SW / n);

    for ( int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].start > p[j + 1].start) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    printf("\nPID\tArrival\tBurst\tPriority\tStart\tEnd\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].priority,
               p[i].start,
               p[i].end,
               p[i].TAT,
               p[i].WT);
    }

    return 0;
}

