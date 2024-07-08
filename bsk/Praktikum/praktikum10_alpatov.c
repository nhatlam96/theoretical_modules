//Praktikum 10 system() Funktion 27.11.2020
//Andrej Alpatov

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

	int wahl, return_wert;
	
	printf("[PID: %i PPID: %i] Das Programm ist gestartet\n", getpid(), getppid());
	printf("Wenn sie wollen, dass das Program xeyes aufgerufen wird, geben Sie 1, 0 fuer quit\n");
	
	if (scanf("%i", &wahl) == EOF)
		error(errno, errno, "INPUT READING ERROR\n");
		
	if(!wahl){
		printf("[PID: %i PPID: %i] Das Programm ist beendet\n", getpid(), getppid());
		exit(0);	
		
	} else if(wahl == 1){
	
		return_wert = system("xeyes +shape -fg blue -bg green");
		
		if(return_wert == -1){
				error(errno, errno, "ERROR RUNNING SYSTEM() FUNCTION\n");
		}else{
			printf("SYSTEM RETURN WERT = %i\n", return_wert);
		}
	}else {	
		error(EINVAL, EINVAL, "Invalid input\n");
	}

		
	printf("[PID: %i PPID: %i] Das Programm xeyes ist beendet\n", getpid(), getppid());

	return 0;
}
