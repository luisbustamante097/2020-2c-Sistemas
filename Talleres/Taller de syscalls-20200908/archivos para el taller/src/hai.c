#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int i=0;

void aux (){
	i++;
	write(1,"ya va\n",6);
	return;
}

int main(int argc, char* argv[]) {
  	int pid_hijo = fork();
    if (pid_hijo==0){
        //HIJO
		signal(SIGURG,&aux);
		
		while (i<5){	
		}
		int pid_p = getppid();
		kill(pid_p, SIGINT);
		execvp(argv[1],argv+1);
		
        
    }else{
        //PADRE
		signal(SIGINT,&exit);
        while(1){
			sleep(1);
			write(1,"sup!\n",5);
			kill(pid_hijo,SIGURG);
		}
    }
    return 0;
}
