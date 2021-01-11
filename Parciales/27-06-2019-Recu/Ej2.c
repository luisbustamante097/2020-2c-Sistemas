#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
Se desea implementar una funcion telefonoDescompuesto que toma dos parametros: una cadena de texto indicando el
nombre de un programa p y un entero n (mayor a 1) indicando la cantidad de procesos que deben generar un anillo.

La funcion debe ejecutar el programa p (sin utilizar la funcion system()) y redirigir su salida s al proceso 0 del
anillo. El proceso numero 0 debe agregarle un caracter al azar a la cadena s 
(utilizar la función char letraAlAzar()) y envia ese nuevo texto al proceso numero 1, el cual realizara el mismo
procedimiento y lo enviara al proceso 2. Una vez que la cadena llegue al proceso n-1 este tambien agregara su caracter
y se lo pasara al proceso 0 que debera imprimir por pantalla la cadena inicial s y la cadena resultante de la vuelta s'.
*/

char* letraAlAzar(){
    char* res = "a";
    return res;
}

void telefonoDescompuesto(char* nombre_programa, unsigned int cant_procs){
    int pipe_exec[2];
    char buffer[4096];
    if (pipe(pipe_exec)==-1){
        perror("pipe_exec");
        exit(EXIT_FAILURE);
    }   
    pid_t pid_exec = fork();
    if (pid_exec == 0){
        // SOY EL HIJO
        
        if (dup2(pipe_exec[1],STDOUT_FILENO)==-1){ // stdout ---> PIPE OUT
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipe_exec[0]);
        execlp(nombre_programa," ",NULL);
        // Al final de la ejecucion se cierra el pipe out
        
    }
    // SOY EL PADRE TODAVIA
    int status=0;
    waitpid(pid_exec,&status,0);
    
    // El padre crea n pipes
	int pipes[cant_procs][2];
	for (int i = 0; i < cant_procs; i++){
		if (pipe(pipes[i]) < 0) {
			perror("pipes");
			exit(EXIT_FAILURE);
		}
	}
	
 	/* El padre crea n hijos que conocen todos los pipes */
	int indice_hijo = 0;
    int pid = 0;
	for (int i = 0; i < cant_procs; i++){
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
            read(pipe_exec[0],buffer,sizeof(buffer));
            //Cierro el pipe del exec
            close(pipe_exec[0]);
            close(pipe_exec[1]);
            //printf("%s", buffer);
            //Guardo el buffer original
            char buffer_original[4096];
            strcpy(buffer_original, buffer);
            
            strcat(buffer,letraAlAzar());
            
            //Escribo en el pipe del siguiente
            write(pipes[indice_hijo+1][STDOUT_FILENO],buffer,sizeof(buffer));
            
            char buffer_last[4096];
            // Espero a que alguien escriba en mi pipe
            read(pipes[0][STDIN_FILENO], buffer_last,sizeof(buffer_last));
            
            //Escribo las salidas pedidas
            printf("Salida original:\n%s \nSalida actual:\n%s\n",buffer_original, buffer_last);
            
            //Cierro mi pipe
            close(pipes[indice_hijo][STDIN_FILENO]);
            close(pipes[indice_hijo][STDOUT_FILENO]);
            exit(0);
            
        }else{
            // SOY alguno de los otros hijos
            
            //Leo mi pipe
            read(pipes[indice_hijo][STDIN_FILENO],buffer,sizeof(buffer));
            
            //Cierro mi pipe
            close(pipes[indice_hijo][STDIN_FILENO]);
            close(pipes[indice_hijo][STDOUT_FILENO]);
            
            strcat(buffer,letraAlAzar());
            
            //Escribo en la entrada del siguiente
            write(pipes[(indice_hijo+1)%cant_procs][STDOUT_FILENO],buffer,sizeof(buffer));
            
            exit(0);
        }
        
	}
    
    // SOY el padre de vuelta
    close(pipe_exec[0]);
    close(pipe_exec[1]);
    
    return;    
}




int main(int argc, char const *argv[]){
    telefonoDescompuesto("/bin/ls",4);
    return 0;
}
