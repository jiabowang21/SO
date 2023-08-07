#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void signals_function(int s) {
    if (s == SIGALRM) {
        char buff[256];
        sprintf(buff, "Soy el proceso %d y he recibido un SIGALRM\n", getpid());
        write(1, buff, strlen(buff));
    }
}

int main(int argc, char* argv[]) {
    sigset_t mask;

    // MODIFICACIÓN DE LA MÁSCARA DE SIGNALS BLOQUEADOS DE UN PROCESO
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL); // <- Aquí el proceso bloquea todos los signals (que se pueden bloquear)
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_UNBLOCK, &mask, NULL); // <- Aquí el proceso sigue con los mismos signals bloqueados menos el SIGINT y SIGALRM
    
    // MODIFICACION DEL TRATAMIENTO DE UN SIGNAL (voy a modificar el tratamiento de SIGALRM)
    struct sigaction sa;
    sa.sa_handler = signals_function;
    sigdelset(&mask, SIGINT);
    sa.sa_mask = mask; // Esta es la máscara que se pone el proceso mientras se ejecuta el sa_handler, estará bloqueando SIGALRM
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    alarm(5);

    // MODIFICACIÓN TEMPORAL DE LA MÁSCARA DE SIGNALS BLOQUEADOS DEL PROCESO MIENTRAS ESPERA A QUE LLEGUE UN SIGNAL
    sigdelset(&mask, SIGALRM);
    sigaddset(&mask, SIGINT);
    sigsuspend(&mask); // Mientras está en sigsuspend, SIGINT no hará que el proceso se desbloquee
    // Después del sigsuspend, el proceso recupera la máscara que tenía antes de la llamada a sigsuspend
    if (execlp("./sigint", "./sigint", (char *)NULL) < 0) {
        perror("Error execlp\n");
        exit(1);
    }
}