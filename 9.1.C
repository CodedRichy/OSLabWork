#include <stdio.h>

struct process { int pid, at, bt, ct, tat, wt; };

int main() {
    int n, currenttime = 0;
    float totalwt = 0;
    float totaltat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1; // Simplifies input
        printf("P%d - Enter AT and BT: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    for(int i = 0; i < n-1; i++) // Standard Bubble Sort
        for(int j = 0; j < n-i-1; j++)
            if(p[j].at > p[j+1].at) {
                struct process temp = p[j]; p[j] = p[j+1]; p[j+1] = temp;
            }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        if(currenttime < p[i].at) currenttime = p[i].at;
        p[i].ct = currenttime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        currenttime = p[i].ct;
        totalwt += p[i].wt;
        totaltat += p[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time = %.2f\n", totalwt / n);
    printf("\nAverage Turn AroundTime = %.2f\n", totaltat / n);
    return 0;
}