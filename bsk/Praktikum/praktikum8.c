#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <limits.h>				  /* Defines PIPE_BUF */
#include <signal.h>

void sig_fkt(int);

int main(int argc, char *argv[])
{
	 int  pd[2];

	 pid_t pid;

	 signal(SIGPIPE, sig_fkt);

	 pipe(pd);
	 /* TODO: error handling */

	 pid = fork();
	 if (pid == -1) {
		  int err = errno;
		  error(err, err, "fork.c exiting fork()-Function on error %i", err);
	 }
	 if (pid > 0) {				  // Father
		  printf("[PID: %i, PPID: %d] Father. Closing read descr.\n",
					getpid(), getppid());


	
		  printf("[PID: %i, PPID: %d] Father. hit a key...\n", getpid(),
					getppid());
		  sleep(1);		  

		  dup2(pd[1], 2);	/* copy write descr. to stdout */
		  close(pd[0]);
		  close(pd[1]);
		  printf("Das ist ein Test...\n")	;	/* printf into pipe */	
		  fprintf(stderr, "Hallo Welt.\n")	;
		  sleep(3);	
		  fprintf(stderr, "Ab durch die Pipe...\n")	;
		  
		  exit(0);	
	 } else {						  // Child
		  printf
				("\n[PID: %i, PPID: %d] Child. Closing write descr.\n",
				 getpid(), getppid());
				 
		  dup2(pd[0], 0); // copy pd[read] to stdin		 
		  close(pd[0]);		 
		  close(pd[1]);
		  char *args[] = {"zenity", "--text-info", (char *) NULL};
		  execvp("zenity", args	);  /* word count reads from stdin */

		  exit(0);
	 }

	 return 0;
}


void sig_fkt(int sig)
{
	 printf("\n[PID: %i, PPID: %d] catching sig: %d\n",
			  getpid(), getppid(), sig);
}