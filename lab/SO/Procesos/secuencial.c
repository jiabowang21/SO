#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int pid;
    char buf[256];
    for (int i = 0; i < 5; ++i) {
        pid = fork();
        if (pid == 0) {
            sprintf(buf, "Soy el hijo con PID %d\n", getpid());
            write(1, buf, strlen(buf));
            exit(0);
        }
        waitpid(-1, NULL, 0);
    }
    sprintf(buf, "Soy el padre y ya se han terminado todos los procesos secuenciales\n");
    write(1, buf, strlen(buf));
}