#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

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

void trat_muerte (int s) {
	int pid;
	char c[100];
	int i = 10;
	sprintf(c, "%d\n", i);
	//crea otro hijo
	pid = fork();
	//código hijo 
	if (pid == 0) {
		execlp("./hijo2", "hijo2", c, (char*)0);
		error_y_exit("execlp", 1); //error del execlp
	}
	//error del fork
	else if (pid < 0) {
		error_y_exit("fork", 1);
	}
} 

int main(int argc, char* argv[]) {
	int pid;
	int i;
	char buff[256];
	//error, falta la N
	if (argc < 2) {
		usage();
	}
	char c[100];
	int npd;
	//creación de los N hijos
	for (i = 0; i < argc; ++i) {
		pid = fork();
		//código hijo 
		if (pid == 0) {
			if ((mknod("MIPIPE", S_IFIFO|0644, 0) < 0) && (errno != EEXIST)){
				error_y_exit("mknod", 1);
			}
			close(0);
			if ((npd = open("MIPIPE", O_WRONLY)) < 0){
				perror("Error en open MIPIPE");
				return -1;
			}
			dup2(0, npd); 
			close(0); close(1);
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
	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
		error_y_exit("sigprocmask", 1);
	} 
	while (1) {
		sprintf(buff, "Controlando\n");
		write(1, buff, strlen(buff));
		sigfillset(&mask);
		sigdelset(&mask, SIGCHLD);
		sigsuspend(&mask);
		sprintf(buff, "Ha muerto un hijo\n");
		write(1, buff, strlen(buff));
	}	
}