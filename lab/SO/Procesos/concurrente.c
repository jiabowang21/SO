#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error_y_exit(char* msg, int exit_status) {
    perror(msg);
    exit(exit_status);
}

int main(int argc, char *argv[]) {
    int pid;
    char buf[256];
    for (int i = 0; i < 5; ++i) {
        if ((pid = fork()) < 0) {
            error_y_exit("Error fork\n", 1);
        }
        if (pid == 0) {
            sprintf(buf, "Soy el hijo con PID %d\n", getpid());
            write(1, buf, strlen(buf));
            exit(0);
        }
    }

    while (waitpid(-1, NULL, 0) > 1);

    sprintf(buf, "Soy el padre y ya se han terminado todos los procesos concurrentes\n");
    write(1, buf, strlen(buf));
}