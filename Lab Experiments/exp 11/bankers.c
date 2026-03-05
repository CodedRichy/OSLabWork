#include<stdio.h>
#include<stdbool.h>
#define MAX 10
int main(){
	int n,m;
	int allocation[MAX][MAX],max[MAX][MAX],need[MAX][MAX],available[MAX],safeseq[MAX];
	int finish[MAX]={0};
	printf("Enter no of process: ");
	scanf("%d",&n);
	printf("Enter no of resource type : ");
	scanf("%d",&m);
	printf("Enter allocation matrix: ");
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&allocation[i][j]);}}
	printf("Enter max matrix: ");
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&max[i][j]);
			}}
	printf("Enter available resources : ");
	for(int i=0;i<m;i++){
		scanf("%d",&available[i]);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			need[i][j]=max[i][j]-allocation[i][j];}}
	int work[MAX];
	for(int i=0;i<n;i++){
		work[i]=available[i];}
		
	int count=0;
	while(count<n){
		int found=0;
		for(int p=0;p<n;p++){
			if(finish[p]==0){
				int j;
				for(j=0;j<m;j++){
					if(need[p][j]>work[j]){break;}}
				if(j==m){
					for(int k=0;k<m;k++){
						work[k]+=allocation[p][k];}
						safeseq[count++]=p;
						finish[p]=1;
						found=1;}}}
						if(found==0){
							printf("Safe sequence not found\n");
							return 0;}}
	printf("Safe sequence found: ");
	for(int i=0;i<n;i++){
		printf("P%d\n",safeseq[i]);
	}
	return 0;
	}
