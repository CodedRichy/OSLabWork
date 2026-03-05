#include <stdio.h>

struct process {
    int pid, at, bt, rt, ct, tat, wt;
};

struct process p[100];
int gantt[1000];   // store process id at each time unit
int gtime = 0;

void print_process(struct process p[100], int n) {
    int i;
    float avg_wt = 0, avg_tat = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
}

void srtf(struct process p[100], int n) {
    int time = 0, completed = 0, i, j;
    struct process temp;

    while (completed < n) {

        // sort by remaining time (only arrived processes)
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                if (p[j].at <= time && p[j + 1].at <= time &&
                    p[j].rt > p[j + 1].rt) {
                    temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }

        // execute one unit
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                p[i].rt--;
                gantt[gtime++] = p[i].pid;  // store for Gantt chart

                if (p[i].rt == 0) {
                    completed++;
                    p[i].ct = time + 1;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
                break;
            }
        }
        time++;
    }
    print_process(p, n);
}

int main() {
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    srtf(p, n);
    return 0;
}
