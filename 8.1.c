#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main() {
    int fd[2];
    pid_t pid;
    double a, b, c, b_squared, four_ac, result;

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    printf("Enter values for a, b, and c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child Process
        close(fd[0]); // Close read end
        four_ac = 4 * a * c;
        write(fd[1], &four_ac, sizeof(four_ac));
        close(fd[1]);
        exit(0);
    } else { // Parent Process
        close(fd[1]); // Close write end
        b_squared = b * b;
        read(fd[0], &four_ac, sizeof(four_ac));
        
        double discriminant = b_squared - four_ac;
        if (discriminant < 0) {
            printf("Result: Imaginary roots (Discriminant < 0)\n");
        } else {
            result = sqrt(discriminant);
            printf("The value of sqrt(b^2 - 4ac) is: %.2lf\n", result);
        }
        close(fd[0]);
    }

    return 0;
}