#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int fork();                    //Crea un proceso exactamente igual al actual y devuelve el 
                               //nuevo processID en el proceso padre y 0 en el proceso hijo
void wait_for_child(pidchild); //Espera hasta que el child indicado finalice su ejecución
void exit(int exit_code);      //Indica al sistema operativo que el proceso actual ha finalizado su ejecución
// void printf(const char*str);   //Escribe un string en pantalla.


/** Abraham es padre de Homer
 * Homer es padre de Bart
 * Homer es padre de Lisa
 * Homer es padre de Maggie
 */

int main(int argc, char const *argv[]){
    pid_t pid = fork();
    if (pid != 0){
        printf("Soy Abraham\n");
        printf("%d\n",getpid());
        wait_for_child(pid);
    }else{        
        printf("Soy Homer\n");
        printf("%d\n",getpid());
        pid_t pid_child1 = fork();
        if (pid_child1 != 0){
            pid_t pid_child2 = fork();
            if (pid_child2 != 0){
                pid_t pid_child3 = fork();
                if (pid_child3 != 0){
                    wait_for_child(pid_child1);
                    wait_for_child(pid_child2);
                    wait_for_child(pid_child3);
                }else{
                    printf("Soy Maggie\n");
                    printf("%d\n",getpid());
                }
            }else{
                printf("Soy Lisa\n");
                printf("%d\n",getpid());
            }
        }else{
            printf("Soy Bart\n");
            printf("%d\n",getpid());
        }
    }
    exit(0);
}

// # Ejercicio 6

void exec(const char *arg); // Reemplaza el programa actual por el codigo localizado en el string

void system(const char *arg){
    int pid_child = fork();
    if (pid_child!=0){
        wait_for_child(pid_child);
    }else{
        exec(arg);
    }
    exit(0);
}