#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int fd = open("PIPE", O_RDONLY); // Esta llamada es bloqueante si no hay ningún otro proceso que esté escribiendo en "PIPE"
                                     // Para que se desbloquee, se debe abrir el ejecutable namedpipe
    char buff[256]; 
    while (read(fd, buff, sizeof(char)) > 0) {
        write(1, buff, sizeof(char));
    }

    exit(0);
}