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

Se desea implementar la funcion traductor() que toma las primeras n lineas de texto de un archivo de entrada
y las copia traducidas en cualquier orden a otro archivo. La funcion traductor() toma 3 parametros:
* n: Cantidad de lineas a traducir
* infile: Nombre del archivo de entrada
* outfile: Nombre del archivo de salida

Cada linea sera traducida por un proceso distinto. Para traducir las lineas se debera contar con un proceso principal que
envie cada una de ellas a los otros n procesos. Cada uno de estos n procesos recibira una linea, la traducira mediante la
llamada a la funcion void traducir (char * linea, char *linea_traducida) y la enviara traducida al proceso principal
Solo el proceso principal sera el encargado de leer el archivo de entrada infile y escribir las lines traducidas en outfile.
Es fundamental que los procesos puedan traducir lineas en simultaneo dado que la funcion traducir es muy lenta.
* IMPORTANTE: Toda la comunicacion entre procesos debe hacerse mediante pipes.

*/
#define CHARS 10
char file[4096]={"01234567890987654321qwertyuioplkjhgfdsazxcvbnm,.-_01234567890987654321qwertyuioplkjhgfdsazxcvbnm,.-_"};

void traducir(char *linea, char *linea_traducida){
    //"Traducir"
    strcpy(linea_traducida,linea);
}

void traductor(int n, char* infile, char* outfile){
    int pipes[n][2];
    //Creo n pipes
    for (int i = 0; i < n; i++){
        if (pipe(pipes[i]) < 0) {
            perror("pipes");
            exit(EXIT_FAILURE);
        }
    }
    char buffer[CHARS];
    
    // El padre crea n hijos que conocen todos los pipes
	int indice_hijo = 0;
    int pid = 0;
	for (int i = 0; i < n; i++){
		pid = fork();
		if (pid==0) {
			indice_hijo = i;
			break;
		}
	}
    
    if (pid == 0) {
        //SOY UNO DE LOS HIJOS
        
        //Recibo el mensaje de padre
        read(pipes[indice_hijo][STDIN_FILENO],buffer,CHARS);
        
        //Lo traduzco
        char traducido[CHARS];
        traducir(buffer,traducido);
        //Lo devuelvo a padre
        write(pipes[indice_hijo][STDOUT_FILENO],traducido,CHARS);
        
        //Cierro los pipes de todos
        for (int i = 0; i < n; i++){
            if (close(pipes[i][0])==-1){
                perror("close_pipe0");
                exit(EXIT_FAILURE);
            }
            if (close(pipes[i][1])==-1){
                perror("close_pipe1");
                exit(EXIT_FAILURE);
            }
        }
        
        exit(0);
	}
    // SOY EL PADRE
    
    //Escribo la linea correspondiente a cada hijo
    for (int i = 0; i < n; i++){
        char buff_aux[CHARS];
        memcpy(buff_aux,&infile[i*CHARS],CHARS);
        write(pipes[i][STDOUT_FILENO],buff_aux,CHARS);
    }
    
    //Leo todas las lineas traducidas
    for (int i = 0; i < n; i++){
        read(pipes[i][STDIN_FILENO],buffer,CHARS);
        memcpy(&outfile[i*CHARS],buffer,CHARS);
        // printf("MI linea: %s\n",buffer);
    }
    printf("Archivo original:  %s\nArchivo traducido: %s\n",infile,outfile);
    
    
    //Espero a que terminen los hijos
    wait(NULL);
    //Cierro los pipes de todos
    for (int i = 0; i < n; i++){
        if (close(pipes[i][0])==-1){
            perror("close_pipe0");
            exit(EXIT_FAILURE);
        }
        if (close(pipes[i][1])==-1){
            perror("close_pipe1");
            exit(EXIT_FAILURE);
        }
    }
    exit(0);
}


int main(int argc, char const *argv[]){
    char out[4096];
    traductor(10,file,out);
    return 0;
}
