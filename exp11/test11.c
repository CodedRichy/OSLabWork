#include <stdio.h>

int main(){
    int a,b,p;
    printf(" Enter number of processes and resource types : ");
    scanf("%d%d",&a,&b);
    int allocation[a][b], max[a][b], need[a][b], available[b], finish[a], safe[a], request[b];

    printf(" Allocation Matrix\n");
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            scanf("%d",&allocation[i][j]); 
        }
    }

    printf(" Max Matrix\n");
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            scanf("%d",&max[i][j]); 
        }
    }

    printf(" Available Matrix\n");
    for(int i=0;i<b;i++){
        scanf("%d",&available[i]);
    }

    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    printf(" Enter the process number making a request : ");
    scanf("%d",&p);
    printf(" Enter request vector : ");
    for(int i=0;i<b;i++){
        scanf("%d",&request[i]);
    }


}
