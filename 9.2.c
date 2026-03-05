#include <stdio.h>

struct Process {
    int pid, at, bt, pr;
    int wt, tat, ct, done;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct Process p[n];

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        p[i].done=0;
        printf("P%d - Enter AT, BT, Priority: ",i+1);
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].pr);
    }

    int completed=0,time=0;
    float twt=0,ttat=0;

    while(completed<n){

        int idx=-1;
        int best=9999;

        for(int i=0;i<n;i++){
            if(p[i].at<=time && !p[i].done){
                if(p[i].pr<best){
                    best=p[i].pr;
                    idx=i;
                }
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        p[idx].wt=time-p[idx].at;
        time+=p[idx].bt;
        p[idx].ct=time;
        p[idx].tat=p[idx].ct-p[idx].at;
        p[idx].done=1;

        twt+=p[idx].wt;
        ttat+=p[idx].tat;

        completed++;
    }

    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");

    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,p[i].wt,p[i].tat);

    printf("\nAvg WT: %.2f",twt/n);
    printf("\nAvg TAT: %.2f\n",ttat/n);
}