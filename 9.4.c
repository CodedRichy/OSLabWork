#include <stdio.h>
#include <limits.h>

struct Process { int pid, at, bt, rt, ct, tat, wt; };

int main() {
    int n, comp = 0, cur = 0, twt = 0, ttat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d AT & BT: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    while(comp != n) {
        int min = -1, min_rt = INT_MAX;
        for(int i = 0; i < n; i++)
            if(p[i].at <= cur && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt; min = i;
            }

        if(min == -1) { cur++; continue; }

        p[min].rt--;
        cur++;
        if(p[min].rt == 0) {
            comp++;
            p[min].ct = cur;
            p[min].tat = p[min].ct - p[min].at;
            p[min].wt = p[min].tat - p[min].bt;
            twt += p[min].wt; ttat += p[min].tat;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    printf("\nAvg WT: %.2f, Avg TAT: %.2f\n", (float)twt/n, (float)ttat/n);
    return 0;
}