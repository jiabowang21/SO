#include <unistd.h>

int main(int argc, char **argv){
	char c;

	while(read(20, &c, sizeof(char))>0)
		write(30, &c, sizeof(char));

	return 0;
}
