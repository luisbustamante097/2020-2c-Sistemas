// Ejercicio 15 

// Escribir el código de un programa que se comporte de la misma manera que la ejecución del comando “ls -al | wc -l” en unashell. No está permitido utilizar la función “system”, y cada uno de los programas involucrados en la ejecución del comando deberá ejecutarse como un subproceso.

#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char const *argv[]){
    char buffer[4096];
    int link[2];
    
    if (pipe(link)==-1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }   
    pid_t pid_ls = fork();
    if (pid_ls == 0){
        // SOY EL HIJO LS
        
        if (dup2(link[1],STDOUT_FILENO)==-1){ // stdout ---> PIPE OUT
            perror("dup2 ls");
            exit(EXIT_FAILURE);
        }
        close(link[0]);
        //close(link[1]);
        execl("/bin/ls","ls","-al",NULL);
        // Al final se cierra el pipe
        
    }else{
        // SOY EL PADRE TODAVIA
        pid_t pid_wc = fork();
        if (pid_wc == 0){
            //SOY EL HIJO WC
            if (dup2(link[0],STDIN_FILENO)==-1){ // stdin ---> PIPE IN
                perror("dup2 wc");
                exit(EXIT_FAILURE);
            }
            //close(link[0]);
            close(link[1]);
            execl("/usr/bin/wc","wc","-l",NULL);
            // read(STDIN_FILENO,buffer,sizeof(buffer));
            // printf("%s",buffer);
            
        }else{
            // AUN SOY EL PADRE
            close(link[0]);
            close(link[1]);
            int status=0;
            waitpid(pid_wc,&status,0);
        }
    }
    return 0;
}
