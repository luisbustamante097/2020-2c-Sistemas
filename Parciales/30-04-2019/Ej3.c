#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
/*
Se tiene un grafo conexo y no dirigido de 10 vertices, es decir, cada par de vertices esta conectado por al menos
un camino. Se desea crear la funcion: void pintar(int *colores) que crea un thread por cada uno de los 10 vertices
y toma como parametro una lista de colores para asignar a cada vertices segun su numero.

El thread numero 0 sera el encargado de pasar la lista de colores a los demas threads para que cada uno pueda
llamar a la funcion void pintame(int color). La comunicacion entre dos threads se realizara mediante pipes y
solo se podra realizar si son vecinos, es decir si existe un eje entre ese par de vertices/threads
(bool son_vecinos(int numeroThreadA, int numeroThreadB)).
Escribir el codigo de la funcion pintar que garantice que todos los threads reciban su color y pueda pintarse

SUGERENCIA. Cada vertices/thread puede tener muchos vecinos, no es necesario que solo uno de ellos le comuniquen
su color. Aunque seguramente le alcance con enterarse por 1era vez de la lista para comunicarsela a sus propios vecinos.
*/

#define N 3
int pipes[N][2];
bool vecinos[N][N] = {{0,1,1},{1,0,0},{1,0,0}};

void pintame(int color){
    printf("Tengo el color %d!\n",color);
}

bool son_vecinos(int numeroThreadA, int numeroThreadB){
    return vecinos[numeroThreadA][numeroThreadB];
}

void close_pipes (){
    for (int i = 0; i < N-1; i++){
        if (close(pipes[i][0])==-1){
            perror("close_pipe0");
            exit(EXIT_FAILURE);
        }
        if (close(pipes[i][1])==-1){
            perror("close_pipe1");
            exit(EXIT_FAILURE);
        }
    }
    
}

void pintar(int *colores){
    
    //Creo N-1 pipes, uno para cada nodo excpeto el 0
    for (int i = 0; i < N-1; i++){
        if (pipe(pipes[i]) < 0) {
            perror("pipes");
            exit(EXIT_FAILURE);
        }
    }
    
    int buffer[N]; // Para guardar los colores
    
    // El padre crea N hijos que conocen todos los pipes
	int indice_hijo = 0;
    int pid = 0;
	for (int i = 0; i < N; i++){
		pid = fork();
		if (pid==0) {
			indice_hijo = i;
			break;
		}
	}
    
    if (pid == 0) {
        //SOY UNO DE LOS HIJOS
        if (indice_hijo==0){
            // SOY EL PRIMER HIJO
            
            //Envio el mensaje a mis vecinos
            for (int i = 0; i < N; i++){
                if (son_vecinos(indice_hijo,i)){
                    //Escribo el mensaje a los demas vecinos
                    write(pipes[i][STDOUT_FILENO],colores,N);
                }
            }
            // Me pinto
            //printf("Soy el hijo: %d\n",indice_hijo);
            pintame(colores[indice_hijo]);
            
        }else{
            //Leo UN SOLO mensaje de mis vecinos
            //printf(" Hijo Nro: %d\n",indice_hijo);
            read(pipes[indice_hijo][STDIN_FILENO], buffer, N);
                        
            //Envio el mensaje a mis vecinos
            for (int i = 0; i < N; i++){
                if (indice_hijo != i && son_vecinos(indice_hijo,i)){
                    //Escribo el mensaje a los demas vecinos
                    //printf("Hijo Nro: %d",indice_hijo);
                    write(pipes[i][STDOUT_FILENO],buffer,N);
                }
            }
            // Me pinto
            //printf("Soy el hijo: %d\n",indice_hijo);
            pintame(colores[indice_hijo]);
        }
        //Siendo hijos, cierro todos los pipes
        close_pipes();
        exit(0);
	}
    //Siendo padre cierro todos los pipes
    wait(NULL);
    close_pipes();
    exit(0);
}



int main(int argc, char const *argv[]){
    int colores[N]={11,22,33};
    pintar(colores);
    return 0;
}
