#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int Allocation[n][m], Max[n][m], Need[n][m];
    int Available[m], Finish[n], safe[n];
    int Request[m], p;

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &Available[i]);

    // Calculate Need matrix
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    /* ----------- RESOURCE REQUEST PART ----------- */

    printf("\nEnter process number making request: ");
    scanf("%d", &p);

    printf("Enter Request vector:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &Request[i]);

    // Check Request <= Need
    for(i = 0; i < m; i++) {
        if(Request[i] > Need[p][i]) {
            printf("Error: Request exceeds Need\n");
            return 0;
        }
    }

    // Check Request <= Available
    for(i = 0; i < m; i++) {
        if(Request[i] > Available[i]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }

    // Temporarily allocate
    for(i = 0; i < m; i++) {
        Available[i] -= Request[i];
        Allocation[p][i] += Request[i];
        Need[p][i] -= Request[i];
    }

    /* ----------- SAFETY ALGORITHM ----------- */

    for(i = 0; i < n; i++)
        Finish[i] = 0;

    int count = 0;

    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {
            if(Finish[i] == 0) {

                for(j = 0; j < m; j++)
                    if(Need[i][j] > Available[j])
                        break;

                if(j == m) {
                    for(k = 0; k < m; k++)
                        Available[k] += Allocation[i][k];

                    safe[count++] = i;
                    Finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is NOT in safe state. Request Denied.\n");
            return 0;
        }
    }

    printf("\nRequest Granted.\nSafe Sequence: ");
    for(i = 0; i < n; i++)
        printf("P%d ", safe[i]);

    return 0;
}

