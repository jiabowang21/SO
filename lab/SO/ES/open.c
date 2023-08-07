#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    int fd = open("./prueba.txt", O_RDWR | O_CREAT, 0644);
    
    char buff[256];
    sprintf(buff, "Holaaaa\n");
    write(fd, buff, strlen(buff));

    lseek(fd, 0, SEEK_SET);

    sprintf(buff, "%d\n", fd);
    write(1, buff, strlen(buff));

    char word[256];
    while (read(fd, word, sizeof(char)) > 0) {
        write(1, word, sizeof(char));
    }
}