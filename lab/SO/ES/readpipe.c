#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char buff[256];
    while (read(30, buff, sizeof(char)) > 0) {
        write(1, buff, sizeof(char));
    }
    exit(0);
}