#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void usage() {
    char buff[256];
    sprintf(buff, "Usage: ./exit_status arg1\nCrea un hijo que terminará con exit status 'arg1'\n");
    write(1, buff, strlen(buff));
    exit(0);
}

void error_y_exit(char *msg, int status) {
    perror(msg);
    exit(status);
}

void tratar_exit_code(int status, int pid_hijo) {
    char buff[256];
    if (WIFEXITED(status)) { // Termina con exit
        int exit_status = WEXITSTATUS(status);
        sprintf(buff, "El proceso %d ha terminado con exit status %d\n", pid_hijo, exit_status);
    }
    else {
        int signal_status = WTERMSIG(status);
        sprintf(buff, "El proceso %d ha terminado por el signal %d\n", pid_hijo, signal_status);
    }
    write(1, buff, strlen(buff));
}

int main(int argc, char *argv[]) {
    if (argc < 2) usage();

    int pid = fork();
    if (pid < 0) error_y_exit("Error fork", 1);
    if (pid == 0) {
        char buff[256];
        sprintf(buff, "Soy el proceso hijo de %d con PID %d y voy a proceder a mutar al programa execlp\n", getppid(), getpid());
        write(1, buff, strlen(buff));
        execlp("./execlp", "./execlp", argv[1], (char*) NULL);
    }

    int status, pid_hijo;
    if ((pid_hijo = waitpid(-1, &status, 0)) < 0) error_y_exit("Error waitpid", 1);
    tratar_exit_code(status, pid_hijo);
}