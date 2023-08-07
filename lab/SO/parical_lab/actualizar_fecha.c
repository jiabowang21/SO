#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void error_y_exit (char *msg, int exit_status) {
	perror(msg);
	exit(exit_status);
}

void usage() {
    char buff[256];
    sprintf(buff, "Usage: actualizar_fecha fichero_1 .. fichero_n\n");
    write(1, buff, strlen(buff));
    exit(1);
}

int main(int argc, char*argv[]) {
	if (argc < 2) {
		usage();
	}
	//int pids[5];
	int* pids;
	pids = malloc(5*sizeof(int));
	for (int i = 1; i < argc; ++i) {
		pids[i - 1] = fork();
		if (pids[i - 1] == 0) {
			execlp("touch", "touch", argv[i], (char*)0);
			error_y_exit("execlp", 1);
		}
		else if (pids[i - 1] < 0) {
			error_y_exit("fork", 1);
		}
	}
	int pid, j;
	char buff[256];
	for (int i = 1; i < argc; ++i) {
		if ((pid = waitpid(-1, NULL, 0)) < 0) {
			error_y_exit("waitpid", 1);
		}
		j = 0;
		while (pid != pids[j]) j++;
		sprintf(buff, "Fecha %s actualizada por %d\n", argv[j + 1], pid);
		write(1, buff, strlen(buff));
	}
	free(pids);
}