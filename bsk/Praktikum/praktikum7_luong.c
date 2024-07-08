/* Nhat-Lam Luong inf3381; 11-11-2020 */
/* Danke an Nikolay Kalamski inf2874 fuer die Partner-Arbeit */
/* Danke an Andrej Alpatov inf3407 fuer die Partner-Arbeit */

/* Ein Deadlock kann entstehen, wenn beide gleichzeitig auf die Pipe zugreifen. */
/* Mit close(fd[x]) und wait(pid) kann man diesen Deadlock umgehen.*/

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define uWARTESEKUNDE 1000000

int main(){

    srand(time(NULL));
	time_t currentTime;
	time(&currentTime);
	
	int fd[2];
	if(pipe(fd) == -1){
		perror("\tpipe() failed.\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();

	if (pid == -1){	
		perror("\tfork() failed.\n");
		exit(EXIT_FAILURE);
	}

	else if (pid == 0){
		printf("[PID: %i, PPID: %i]\tKindprozess START.\n\n",getpid(), getppid());
		close(fd[0]);

		printf("[PID: %i, PPID: %i]\tDas ZahlenArray_child aufgelistet:\n",getpid(), getppid());
        int zahlenArray_child[10];		
        for(int counter = 0; counter < 10; counter++){
            printf("[PID: %i, PPID: %i]\tZahlenArray[%i]: %i\n", getpid(), getppid(), counter, zahlenArray_child[counter] = rand() % 100);
			usleep(uWARTESEKUNDE/2);		
		}
		printf("\n");

		write(fd[1], zahlenArray_child, sizeof(zahlenArray_child)); 
		close(fd[1]);

		printf("[PID: %i, PPID: %i]\tKindprozess ENDE.\n\n",getpid(), getppid());
		int byteSize = sizeof(zahlenArray_child);
		exit(byteSize);	
	}

	else {
		printf("[PID: %i, PPID: %i]\tElternprocess START: Kindprozess ID: [[%i]] Time: %s",getpid(), getppid(), pid, ctime(&currentTime));


		int wstatus;
        waitpid(pid, &wstatus, 0);
		int byteSize_child = WEXITSTATUS(wstatus);

		close(fd[1]);
		int zahlenArray_parent[10];
		int byteSize_pipe = read(fd[0], zahlenArray_parent, sizeof(zahlenArray_parent));

		printf("[PID: %i, PPID: %i]\tChild: %i bytes. Parent: %i bytes.\n",getpid(), getppid(), byteSize_child, byteSize_pipe);

        if(byteSize_child==byteSize_pipe){ printf("[PID: %i, PPID: %i]\tPipe_transfer erfolgreich: child_bytes: %i,\tpipe_bytes: %i\n\n",getpid(), getppid(), byteSize_child, byteSize_pipe); }
		else{ printf("[PID: %i, PPID: %i]\tPipe_transfer fehlgeschlagen: child_bytes: %i,\tpipe_bytes: %i\n\n",getpid(), getppid(), byteSize_child, byteSize_pipe); }

		printf("[PID: %i, PPID: %i]\tDas ZahlenArray_parent aufgelistet:\n", getpid(), getppid());
		for (int counter = 0; counter < 10; counter++){
			printf("[PID: %i, PPID: %i]\tZahlenArray[%i]: %i\n", getpid(), getppid(), counter, zahlenArray_parent[counter]);
			usleep(uWARTESEKUNDE/2);
		}
		printf("\n");

		close(fd[0]);
		printf("[PID: %i, PPID: %i]\tElternprocess ENDE: Kindprozess ID: [[%i]] Time: %s",getpid(), getppid(), pid, ctime(&currentTime));
	}

	return 0;
}