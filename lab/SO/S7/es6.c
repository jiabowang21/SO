#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

void func(int s) {
	char buff[128] = "recibido\n";
	write(1, &buff, strlen(buff));
}

int main(){
	struct sigaction sa;

	sa.sa_handler = &func;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);


	char buf[256];
	char c;

	int ret = read(0, &c, sizeof(char));


	if (ret >= 0) {
		sprintf(buf, "read correcto\n");
		write(1,buf,strlen(buf));
	} 
	else {
		if (errno == EINTR) {
			sprintf(buf, "read interrumpido por signal\n");
			write(1,buf,strlen(buf));
		} else {
			sprintf(buf, "read con error\n");
			write(1,buf,strlen(buf));
		}
	}
}
