#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "config.h"

int main(int argc, char **argv){
	char bufrecv[MSGLEN + 1], *bufsend, *p;
	struct sockaddr_in name;
	size_t bufsendsiz=0;
	ssize_t r, w;
	int s;
	bufsend = NULL;
	memset(&name, 0, sizeof(name));

	if (argc != 2) {
		fprintf(stderr, "uso: %s ip\n", argv[0]);
		exit(1);
	}

	//Creamos el socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	//Configuracion, no tocar
	if (!inet_aton(argv[1], &name.sin_addr)) {
		fprintf(stderr, "%s: ip desconocida\n", argv[1]);
		exit(1);
	}

	name.sin_family = AF_INET;
	name.sin_port = htons(PORT);

	//COMPLETAR: conectar el socket
	if (connect(s,(const struct sockaddr*) &name, sizeof(name)) < 0) {
		perror("connect");
		return 1;
	};

	//COMPLETAR: Recibir mensaje de bienvenida y ponerlo en bufrecv
	if(recv(s, bufrecv, sizeof(bufrecv), 0) > MSGLEN+1){
		perror("welcome_msg");
		return 1;
	} 

	printf("Bienvenida: %s\n",bufrecv);

	for (;;) {
		printf("[%s]> ", argv[1]);
		//Tomamos el input
		if ((w = getline(&bufsend, &bufsendsiz, stdin)) == -1) {
			if (!feof(stdin))
				perror("getline");

			printf("getline");
			break;
		}
		//Nos fijamos si era ENDMSG para cortar la ejecucion
		if (strncmp(bufsend, ENDMSG, w) == 0){
			printf("----Salimos por chau\n");
			break;
		}
		//COMPLETAR: Enviar el mensaje
		if (send(s, bufsend, bufsendsiz, 0) < 0) {
			perror("send");
			return 1;
		}
		
		while(1){
			//COMPLETAR: Recibir mensajes hasta que envie  CMDSE
			
			//LIMPIAMOS EL BUFFER
			for (int i = 0; i < MSGLEN; i++)
			{
				bufrecv[i]=0;
			}
			
			if(recv(s, bufrecv, MSGLEN, 0) < 0){
				perror("server_msg");
				return 1;
			}
			//IMPRIMIMOS el mensaje del servidor
			// write(1,bufrecv,sizeof(bufrecv));
			printf("%s\n",bufrecv);
			
			//SALIMOS si recibimos CMDSEP
			if (strncmp(bufrecv, CMDSEP, MSGLEN) == 0){
				printf("----Salimos por CMDSEP\n");
				break;
			}
		
		}
		
		//
	}

	free(bufsend);
	close(s);

	return 0;
}
