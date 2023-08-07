#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    mknod("PIPE", S_IFIFO | 0664, 0);
    int fd = open("PIPE", O_WRONLY); // Esta llamada es bloqueante si no hay ningún otro proceso que esté leyendo el pipe "PIPE"
                                     // Para que se desbloquee, se debe abrir el ejecutable readnamedpipe
    char buff[256];
    sprintf(buff, "Este mensaje ha sido enviado por el pipe con nombre PIPE\n");
    write(fd, buff, strlen(buff));
    sprintf(buff, "Mensaje enviado\n");
    write(1, buff, strlen(buff));
}