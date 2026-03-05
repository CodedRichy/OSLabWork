#include <stdio.h>

struct Process { int pid, bt, rt, wt, tat; };

int main() {
    int n, quantum, time = 0, done, twt = 0, ttat = 0;
    printf("Enter n and Quantum: ");
    scanf("%d %d", &n, &quantum);
    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d BT: ", i+1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("\nGantt Chart: ");
    do {
        done = 1;
        for(int i = 0; i < n; i++) {
            if(p[i].rt > 0) {
                done = 0;
                int step = (p[i].rt > quantum) ? quantum : p[i].rt;
                printf("P%d(%d-%d) ", p[i].pid, time, time + step);
                time += step;
                p[i].rt -= step;
                if(p[i].rt == 0) {
                    p[i].tat = time;
                    p[i].wt = p[i].tat - p[i].bt;
                    twt += p[i].wt; ttat += p[i].tat;
                }
            }
        }
    } while(!done);

    printf("\n\nPID\tBT\tWT\tTAT\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    printf("\nAvg WT: %.2f, Avg TAT: %.2f\n", (float)twt/n, (float)ttat/n);
    return 0;
}