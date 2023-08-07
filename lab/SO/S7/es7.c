#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	char buff[64];
	int numero = 10562;
	close(0);
	open("entrada.txt", O_RDONLY);
	close(1);
	open("salida.txt", O_WRONLY|O_TRUNC);
	int num;
    read(0, &num, sizeof(int));
	write(1, &num, sizeof(int));
}
