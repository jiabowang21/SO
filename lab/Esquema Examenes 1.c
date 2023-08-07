//Includes necesarios
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

//funcion que hace el signal
void funcion_alarma(int signal)
{
	char buff[256];
	segundos=segundos+10;
	sprintf(buff,"ALARMA pid=%d: %d segundos\n",getpid(),segundos);
	write(1, buff, strlen(buff) );
}

//funcion para cuando pasas los parametros mal o son insuficientes
void Usage() {
	char buff[128];
	sprintf(buff, "Usage: [escribir formato de entrada]\n");
	write(1, buff, strlen(buff));
	exit (1);
}

//funcion para mutar
void muta(char *username) {
	execlp("ps", "ps", "-u", username, (char*)NULL);
	error_y_exit("Ha fallado la mutación al ps", 1);
}

//Funcion de error
void error_y_exit(char *s, int error) {
	perror(s);
	exit(error);
}

//Muerte hijo WNOHANG
	sa.sa_handler = &trata_hijo;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);
	while (hijos > 0);

void trata_hijo(int s) {  //s es SIGCHLD
	int pid, exit_code;
	char buff[256];	
	while ((pid = waitpid(-1, &exit_code, WNOHANG)) > 0) {
		if (WIFEXITED(exit_code)) {
			int statcode = WEXITSTATUS(exit_code);
			sprintf(buff,"Termina el proceso %d com exit code %d\n",pid, statcode);
		}
		else {
			int signcode = WTERMSIG(exit_code);
			sprintf(buff,"Han matado al proceso %d antes de acabar alarm por el signal %d\n",pid, signcode);
		}
		write(1, buff, strlen(buff)); 
		hijos--;
		++contador;
	}
}

//Muerte hijo normal
while ((waitpid(-1, NULL, 0)) > 0);

//Error waitpid
if ((pid = waitpid(-1, NULL, 0)) < 0)
	perror("waitpid"); 
	return -1; 


//Exit o signal??
if (WIFEXITED(res)) {
		sprintf(buff,"Termina el proceso %d con exitcode %d\n",pid, WEXITSTATUS(res));
		write(1, buff, strlen(buff));
	}
	else {
		if (WTERMSIG(res) == SIGUSR1) {
			sprintf(buff,"Termina el proceso %d por el signal USR1\n",pid);
		}
		else {
			sprintf(buff,"Termina el proceso %d por el signal %d\n",pid, WTERMSIG(res));
		}
		write(1, buff, strlen(buff));
	}



int main(int argc, char *argv[]) {
	sigset_t mask;
	struct sigaction sa;
	char s[1024]; 


	// Block signals
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &mask, NULL);
	//O en modo funcion
	void configurar_esperar_alarma() {
	sigemptyset(&mask);
	sigaddset(&mask, SIGALRM);
	sigprocmask(SIG_BLOCK, &mask, NULL);
	}


	// Reprogramar signals
	sa.sa_handler = &ras;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);


	// Esperar a signals
	sigfillset(&mask);
	sigdelset(&mask, SIGUSR1);
	sigdelset(&mask, SIGINT);
	sigsuspend(&mask);
	//O en modo funcion
	void esperar_alarma() {
	sigfillset(&mask);
	sigdelset(&mask, SIGALRM);
	sigsuspend(&mask);
	}

	//Para que la reprogramación del signal funcione
	if (sigaction(SIGALRM, &sa, NULL) < 0) error_y_exit("sigaction", 1);
	
	//Switch para que el padre y el hijo hagan cosas distintas
	switch (fork()) {
			case 0:
				sprintf(s, "Soy el proceso HIJO: %d de %s\n", getpid(), argv[1]);
				write(1, s, strlen(s));
				while(1);
				break;
			case -1:
				sprintf(s,"Ha fallado el fork del proceso: %d\n", getpid());
				error_y_exit(s, 1);
				break;
			default:
				sprintf(s, "Soy el proceso PADRE: %d\n", getpid());
				write(1, s, strlen(s));
				while(1);
				break;
		}
		

