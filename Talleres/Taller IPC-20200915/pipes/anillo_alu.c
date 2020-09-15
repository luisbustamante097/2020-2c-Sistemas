#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{	
	int status, pid;
	int buffer[1];

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
    /* Parsing de los argumentos */
  	int n, c, s;
		n = atoi(argv[1]);
		c = atoi(argv[2]);
		s = atoi(argv[3]);

    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, c, s);

	int pipe_padre[2];
	if (pipe(pipe_padre) < 0) {
			perror("pipes");
			exit(EXIT_FAILURE);
	}

   	/* El padre crea n pipes */
	int pipes[n][2];
	for (int i = 0; i < n; i++){
		if (pipe(pipes[i]) < 0) {
			perror("pipes");
			exit(EXIT_FAILURE);
		}
	}
	
 	/* El padre crea n hijos que conocen todos los pipes */
	//pid_t pids[n];
	int indice_hijo = 0;
	for (int i = 0; i < n; i++){
		//pids[i] = fork();
		pid = fork();
		if (pid==0) {
			indice_hijo = i;
			break;
		}
	}

	/* Si soy un hijo... */
  if (pid == 0) {
		//Leo del pipe actual
		printf("Hijo: %d, LEER \n", indice_hijo);
		if (read(pipes[indice_hijo][0], &c, sizeof(c)) != sizeof(c)) {
			perror("read_hijo");
			exit(EXIT_FAILURE);
		}
		close(pipes[indice_hijo][0]);
		c++;

		//Si soy el ultimo hijo del circuito
		int ult = (((s-1) % n + n) %n);
		if (indice_hijo == ult) {
			//Escribo en el pipe del padre
			printf("Hijo: %d, Escribe\n ", indice_hijo);
			if (write(pipe_padre[1], &c, sizeof(c)) != sizeof(c)) {
				perror("write_final");
				exit(EXIT_FAILURE);
			}
			close(pipe_padre[1]);
			
		}else{
			//Escribo en el pipe del hijo siguiente
			printf("Hijo: %d, ESCRIBIR \n", indice_hijo);
			if (write(pipes[(indice_hijo+1)%n][1], &c, sizeof(c)) != sizeof(c)) {
				perror("write_hijo");
				exit(EXIT_FAILURE);
			}
			close(pipes[(indice_hijo+1)%n][1]);
		}
		exit(0);
	}

	/* Si soy el padre...  */
	//
	int s_ini = ((s % n + n) %n);
	if (write(pipes[s_ini][1], &c, sizeof(c)) != sizeof(c)) {
		perror("write_comienzo");
		exit(EXIT_FAILURE);
	}
	close(pipes[s_ini][1]);

	if (read(pipe_padre[0], &c, sizeof(c)) != sizeof(c)) {
		perror("read_final");
		exit(EXIT_FAILURE);
	}
	
	close(pipe_padre[0]);
	close(pipe_padre[1]);

	printf("c=%d\n", c);
	return 0;
}
