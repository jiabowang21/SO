//Includes necesarios
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

//String a numero
niterations = atoi (argv[1]);

//Malloc amb free
char *p;
p = malloc (REGION_SIZE);
sprintf (buff, "\t Malloc fet p: %p, region %d: %p\n", &p, i, p);  //p direcció del heap.   %p pointer
write(1,buff,strlen(buff));
free(p);

//Error MALLOC
if (p == NULL) {
	sprintf(buff, "ERROR en el malloc\n");
	write(2,buff,strlen(buff));
}

//Error SBRK 
if (sbrk(REGION_SIZE) == (void *) -1) {
	sprintf(buff, "ERROR en el sbrk\n");
	write(2,buff,strlen(buff));
}


//Read bucle (fins CTRL d) 
ret=read(0,&read_buffer,sizeof(read_buffer));
// Cuando el read devuelve 0 significa que se ha acabado la
// entrada de datos --> acabamos el bucle de lectura
while(ret>0){
	// Escribimos en el canal 1 (salida std) 1 byte
	write(1,&read_buffer,sizeof(read_buffer));
	ret=read(0,&read_buffer,sizeof(read_buffer));
}


//Read Write Errors
if (ret >= 0) {
	sprintf(buf, "read o write correcto\n");
	write(1,buf,strlen(buf));
} else { //-1
	if (errno == EINTR) {
		sprintf(buf, "read o write interrumpido por signal\n");
		write(1,buf,strlen(buf));
	} else {
		sprintf(buf, "read o write con error\n");
		write(1,buf,strlen(buf));
	}
}


//PIPE AMB NOM
char buff[80];
int fd = open("./pipe",O_RDWR|O_NONBLOCK);
if ((fd < 0) && (errno == ENXIO)) perror("Esperando lector");
fd = open("./pipe",O_RDWR);
int ret = numero; 
while((ret = read(fd,buff,ret)) > 0){
	write(fd,buff,ret);
}

//PIPE SENSE NOM 
int fd[2]; 
int a = pipe(fd); 
if (a < 0) perror("error al crear pipe"); 
else {

}


//dup, dup2
int fd = dup(numero); 
if (fd < 0) {
	perror("Error al crear canal")
	return -1; 
}
else {

}

dup2(pd[1], 1); close(pd[0]); close(pd[1]);


//lseek
int a; 
if ((a = lseek(fd, 0, SEEK_END)) < 0) perror("Error en lseek")  //final de fd
if ((a = lseek(fd, 0, SEEK_SET)) < 0) perror("Error en lseek")  //principi de fd
if ((a = lseek(fd, 0, SEEK_CUR)) < 0) perror("Error en lseek")  //actual de fd


//append lseek
char c;
lseek(fd, ini, SEEK_SET);
while ((read(fd, &c, sizeof(char) > 0)
	&& ini < fi)) {
	lseek(fd, 0, SEEK_END);
	write(fd, &c, sizeof(char));
	++ini;
	lseek(fd, ini, SEEK_SET);
}


//crear fitxer i assignar-lo a canal
if ((fd2 = creat("out", 0600)) < 0) halt("creat");

if ((mknod("MIPIPE", S_IFIFO|0644, 0) < 0)&&(errno != EEXIST)){ //0644
	perror("Error en mknod");
	return -1;
}



//invertir fitxer lseek
char c;
lseek(fd1, -1, SEEK_END);
ini = -2;
while (read(fd1, &c, sizeof(char) > 0)) {
	write(fd2, &c, sizeof(char));
	if (lseek(fd1, ini, SEEK_END) < 0) return;
	--ini;
}



//Escriure a pipe sense nom
dup2(pd[1], 1); close(pd[0]); close(pd[1]);
execlp("cat", "cat", argv[i], NULL);




rwx oct    meaning
--- ---    -------
001 01   = execute
010 02   = write
011 03   = write & execute
100 04   = read
101 05   = read & execute
110 06   = read & write
111 07   = read & write & execute



%d //numero
%s //string de caracters
%p //pointer

pids[i-1] = fork();