#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){
	mkfifo("pipetest", S_IWUSR |S_IRUSR |  /* El usuario puede leer */
                 S_IRGRP |  /* El grupo puede leer */
                     S_IROTH    /* Otros pueden leer */
         );
	/*char buff[80];
	int fd = open("pipe",O_WRONLY);
	int ret;
	while((ret = read(fd,buff,ret)) > 0){
		write(fd,buff,ret);
	}*/
}
