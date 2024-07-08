/* Nhat-Lam Luong inf3381; 11-11-2020 */
/* Danke an Andrej Alpatov inf3407 fuer die Partner-Arbeit */

#include <stdio.h>		//stderr
#include <stdlib.h> 	//EXIT_FAILURE
#include <unistd.h> 	//STDIN_FILENO
#include <sys/wait.h> 	//waitpid

int main(){

	int fd[2];
	if(pipe(fd) == -1){
		printf("[PID: %i, PPID: %i]\tPipe failed.\n", getpid(), getppid());
		return EXIT_FAILURE;
	}

	pid_t pid = fork();
	if(pid == -1){
		printf("[PID: %i, PPID: %i]\tFork failed.\n", getpid(), getppid());
		return EXIT_FAILURE;
	}

	if(pid == 0){
		printf("[PID: %i, PPID: %i]\tKindprozess: START.\n", getpid(), getppid());

		close(fd[1]);	/* Lesedeskriptor nutzen. */
		dup2(fd[0], STDIN_FILENO); /* Lesedeskriptor nach STDIN leiten. */
		close(fd[0]);	/* Lesedeskriptor schliessen, weil es schon dupliziert wurde. */
		
        char *argv[] = {"zenity", "--text-info", NULL};
        printf("[PID: %i, PPID: %i]\tKindprozess: execvp()", getpid(), getppid());
        for(int i = 0; argv[i] != NULL; i++){
			printf(" %s", argv[i]);
        }
        printf("\n");
        int execvp_return = execvp(argv[0], argv);
		if(execvp_return == -1){
			printf("[PID: %i, PPID: %i]\tKindprozess: Fehler beim execvp.\n", getpid(), getppid());
			return EXIT_FAILURE;
		}
	}

	else{
		printf("[PID: %i, PPID: %i]\tVaterprozess: START.\n", getpid(), getppid());

		close(fd[0]);	/* Schreibedeskriptor nutzen. */
		dup2(fd[1], STDERR_FILENO);	/* Schreibedeskriptor nach STDERR leiten. */
		close(fd[1]);	/* Schreibedeskriptor schliessen, weil es schon dupliziert wurde. */

		fprintf(stderr, "1.Vaterprozess_Schreibedeskriptor geht nach STDERR.\n");
		fprintf(stderr, "2.Kindprozess_Lesedeskriptor nimmt von Pipe auf und leitet nach STDIN.\n");
		fprintf(stderr, "3.Neuer Prozess von execvp() benutzt STDIN als Eingabe.\n");
		fprintf(stderr, "4.Deswegen erscheint dieser Text hier.\n");

		int if_exited;
		waitpid(pid, &if_exited, 0 );
		if(WIFEXITED(if_exited)){
			int exit_status_child = WEXITSTATUS(if_exited);
			printf("[PID: %i, PPID: %i]\tVaterprozess: Kindprozess ENDE: exit(%i)\n", getpid(), getppid(), exit_status_child);
		}
		printf("[PID: %i, PPID: %i]\tVaterprozess: ENDE.\n", getpid(), getppid());
	}	
	
	return 0;
}

/* FileDescriptor: 0 = STDIN || 1 = STDOUT || 2 = STDERR */