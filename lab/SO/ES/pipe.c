#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("Error pipe\n");
        exit(1);
    }
    dup2(pipefd[0], 30); close(pipefd[0]);
    int pid;
    if ((pid = fork()) < 0) {
        perror("Error fork\n");
        exit(1);
    }
    if (pid == 0) {
        execlp("./readpipe", "./readpipe", (char*)NULL);
    }
    char buff[256];
    sprintf(buff, "Este mensaje ha sido enviado por el pipe asignado al proceso %d\n", getpid());
    write(pipefd[1], buff, strlen(buff)); // Aunque no haya ningún proceso hijo que esté leyendo este pipe sin nombre
                                          // el proceso no se bloquea -> Escribir/leer pipe sin nombre NO es bloqueante

    sprintf(buff, "Mensaje enviado\n");
    write(1, buff, strlen(buff));
}
