#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void signals_function(int s) {
    if (s == SIGINT) {
        char buff[256];
        sprintf(buff, "Soy el proceso %d y he recibido un SIGINT\nVoy a matarme en 5 segundos con una alarma\n", getpid());
        write(1, buff, strlen(buff));
        alarm(5);
    }
}

int main(int argc, char* argv[]) {
    struct sigaction sa;
    sa.sa_handler = signals_function;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    while(1);
}