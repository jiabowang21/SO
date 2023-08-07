#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void error_y_exit(char* msg,int error_status) {
	perror(msg);
	exit(error_status);
}

int main(int argc, char **argv) {
	int fd, ret;
	char buff[128];
	if ((fd = open("salida.txt", O_RDWR)) < 0) error_y_exit("error al abrir el archivo",1);
	lseek(fd, -2, SEEK_END);
	ret = read(fd, buff, 2*sizeof(char));
	lseek(fd, -2, SEEK_END);
	write(fd, "X", sizeof(char));
	write(fd, buff, ret);
}
