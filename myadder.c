#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    if(argc < 3) {
        printf("Minimum 2 arguments needed\n");
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("The Sum is %d\n", a + b);

    return 0;
}