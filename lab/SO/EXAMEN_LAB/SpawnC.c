#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int N;
int* pids;

void usage() {
    char buff[256];
    sprintf(buff, "Usage: spawnA hijo_1 .. hijo_n\n");
    write(1, buff, strlen(buff));
    exit(1);
}

void error_y_exit (char *msg, int exit_status) {
	perror(msg);
	exit(exit_status);
}

void hijo (int j) {
	char buff[256];
	sprintf(buff, "pids de los hijos vivos\n");
	write(1, buff, strlen(buff));
	int pid;
	for (int i = 0; i < N; ++i) {
		pid = pids[i];
		sprintf(buff, "hijo %d con pid %d\n", i, pid);
		write(1, buff, strlen(buff));
	}
} 

void trat_muerte (int s) {
	char buff[256];
	sprintf(buff, "Ha muerto un hijo\n");
	write(1, buff, strlen(buff));
	int pid;
	char c[100];
	int i = 10;
	sprintf(c, "%d\n", i);
	//crea otro hijo
	pid = fork();
	//código hijo 
	if (pid == 0) {
		execlp("./hijo1", "hijo1", c, (char*)0);
		error_y_exit("execlp", 1); //error del execlp
	}
	//error del fork
	else if (pid < 0) {
		error_y_exit("fork", 1);
	}
} 

int main(int argc, char* argv[]) {
	N = argc;
	int pid;
	pids = malloc(N*sizeof(int));
	int i;
	char buff[256];
	//error, falta la N
	if (argc < 2) {
		usage();
	}
	char c[100];
	//creación de los N hijos
	for (i = 0; i < argc; ++i) {
		pid = fork();
		pids[i] = pid;
		//código hijo 
		if (pid == 0) {
			sprintf(c, "%d\n", i);
			execlp("./hijo1", "./hijo1", c, NULL);
			error_y_exit("execlp", 1); //error del execlp
		}
		//error del fork
		else if (pid < 0) {
			error_y_exit("fork", 1);
		}
	}
	struct sigaction trat;
	sigset_t mask;
	//reprogramar SIGCHLD
	trat.sa_handler = trat_muerte;
	trat.sa_flags = 0;
	sigemptyset(&trat.sa_mask);
	if (sigaction(SIGCHLD, &trat, NULL) < 0) {
		error_y_exit("sigaction", 1);
	}
	//reprogramar SIGUSR1
	trat.sa_handler = hijo;
	trat.sa_flags = 0;
	sigemptyset(&trat.sa_mask);
	if (sigaction(SIGUSR1, &trat, NULL) < 0) {
		error_y_exit("sigaction", 1);
	}
	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);
	sigaddset(&mask, SIGUSR1);
	if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
		error_y_exit("sigprocmask", 1);
	} 
	while (1) {
		sprintf(buff, "Controlando\n");
		write(1, buff, strlen(buff));
		sigfillset(&mask);
		sigdelset(&mask, SIGCHLD);
		sigdelset(&mask, SIGUSR1);
		sigsuspend(&mask);
	}	
	free(pids);
}