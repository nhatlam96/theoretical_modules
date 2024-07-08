/* Nhat-Lam Luong inf3381; 31-10-2020 */

/* Bitte folgende Befehle ins Terminal eintippen: */
/* 1. kill -SIGUSR1 ProcessID */
/* 2. kill -SIGHUP ProcessID */
/* 3. nochmal kill -SIGHUP ProcessID */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define uWARTESEKUNDE 1000000

void sighup_handler(){
    static int aufrufZaehler = 1;
    
    if(aufrufZaehler >= 2){
        printf("\n[PID: %i, PPID: %i]\tSIGHUP Handler: %i. Aufruf.\n\n",getpid(), getppid(), aufrufZaehler);
        
        int fork_return = fork();
        if(fork_return == -1){
            perror("Error: fork() failed.\n");
            exit(EXIT_FAILURE);
        }
        else if (fork_return == 0){
            printf("[PID: %i, PPID: %i]\tHallo ich bin ein Kindprozess.\n",getpid(), getppid());
            int argc = 7;
            char *arg = "xeyes";
            char *argv[argc];
            argv[argc-argc] = "xeyes";
            argv[1] = "+shape";
            argv[2] = "-fg";
            argv[3] = "blue";
            argv[4] = "-bg";
            argv[5] = "green";
            argv[argc-1] = NULL;
            printf("[PID: %i, PPID: %i]",getpid(), getppid());
            for(argc = 0; argv[argc] != NULL;){
                printf(" %s", argv[argc++]);
            }
            printf("\n");
            execvp(arg, argv);
        }
        else{
            printf("[PID: %i, PPID: %i]\tElternprocess wird beendet.\n",getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
    }
    else if(aufrufZaehler == 1){
        printf("\n[PID: %i, PPID: %i]\tSIGHUP Handler: %i. Aufruf.\n\n",getpid(), getppid(), aufrufZaehler);
        aufrufZaehler++;
    }
}

void sigusr1_handler(){
	printf("\n[PID: %i, PPID: %i]\tSIGUSR1 Handler wurde aufgerufen.\n",getpid(), getppid());

    printf("[PID: %i, PPID: %i]\tWeitere kill -SIGUSR1 werden ignoriert.\n",getpid(), getppid());
    signal(SIGUSR1, SIG_IGN);
    
    printf("[PID: %i, PPID: %i]\tHandler fuer SIGHUP wurde eingerichtet.\n\n",getpid(), getppid());
    signal(SIGHUP, &sighup_handler);
}

int main(){
    printf("\n[PID: %i, PPID: %i]\tNhat-Lam Luong, inf3381 = BSK Praktikum 6.\n\n",getpid(), getppid());

	printf("\n[PID: %i, PPID: %i]\tWarte auf kill -SIGUSR1 %i\n\n",getpid(), getppid(), getpid());
    signal(SIGUSR1, &sigusr1_handler);

    time_t currentTime;
    while(true)
    {
        time(&currentTime);
        printf("[PID: %i, PPID: %i]\tCurrent time: %s", getpid(), getppid(), ctime(&currentTime));
        usleep(uWARTESEKUNDE);
    }

	return 0;
}
