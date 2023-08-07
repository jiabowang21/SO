#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}

void usage() {
	char buff[256];
	sprintf(buff, "Usage: signals n\n");
	write(1, buff, strlen(buff));
	exit(1);
}

void trat_alarm(int s) {
}

void trat_usr1(int s) {
	int n;
	n = alarm(0);
	exit(n);
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		usage();
	}
	struct sigaction trat;
	sigset_t mask;
	//reprogramar SIGALRM
	trat.sa_handler = trat_alarm;
	trat.sa_flags = 0;
	sigemptyset(&trat.sa_mask);
	if (sigaction(SIGALRM, &trat, NULL) < 0) {
		error_y_exit("sigaction");
	}
	//reprogramar SIGUSR1
	trat.sa_handler = trat_usr1;
	if (sigaction(SIGUSR1, &trat, NULL) < 0) {
		error_y_exit("sigaction");
	}
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGALRM);
	if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
		error_y_exit("sigprocmask");
	}
	int n, i, status, wpid;
	n = atoi(argv[1]);
	int pids[10];
	char buff[256];
	for (i = 0; i < n; ++i) {
		pids[i] = fork();
		if (pids[i] == 0) {
			alarm(3);
			sigfillset(&mask);
			sigdelset(&mask, SIGUSR1);
			sigdelset(&mask, SIGALRM);
			sigsuspend(&mask);
			sprintf(buff, "%d: Timeout\n", getpid());
			write(1, buff, strlen(buff));
			exit(0);
		}
		else if (pids[i] < 0) {
			error_y_exit("fork");
		}
	}
	for (i = 0; i < n; i++) {
		if (pids[i]%2 == 0) {
			if (kill(pids[i], SIGUSR1) < 0) {
				error_y_exit("kill");
			}
		}
	}
	for (i = 0; i < n; i++) {
		if ((wpid = waitpid(-1, &status, 0)) < 0) {
			error_y_exit("waitpid");
		}
		if (WIFEXITED(status) && (wpid%2 == 0)) {
			sprintf(buff, "Hijo %d. Segundos restantes %d\n", wpid, WEXITSTATUS(status));
			write(1, buff, strlen(buff));
		}
	}
}
