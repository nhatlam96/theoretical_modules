/*
 *  Beispielprogramm fuer pipes und fork. WiSe 2020
 *  Autor: A. Brunner und D. Bub
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>     /* used for waitpid() */
#include <sys/wait.h>      /* used for waitpid() */
#include <string.h>
#include <limits.h>        /* Defines PIPE_BUF */
#include <signal.h>
#include <time.h>

#define BUFF_COUNT 10

void sig_fkt(int);

int main(int argc, char *argv[])
{
	 int err, pd[2], status, child_exit_status;
	 pid_t pid;

	 signal(SIGPIPE, sig_fkt);

	 err = pipe(pd);
	 if (err == -1) {
		  int err = errno;
		  error(err, err, "exiting pipe()-Function on error %i", err);
	 }

	 pid = fork();
	 if (pid == -1) {
		  int err = errno;
		  error(err, err, "exiting fork()-Function on error %i", err);
	 }
	 if (pid > 0) {				  // Father
		  int byte_count=0, i;
		  int buff[BUFF_COUNT];
      time_t currentime;
      
      close(pd[1]);
		  //close(pd[0]); // wenn die Pipe zu früh geschlossen wird, erhalten wir SIGPIPE!
      
      time(&currentime);
		  printf("\n[PID: %i, PPID: %d] Father has started. Child-PID: %i. Current time: %s\n", getpid(), getppid(), pid, ctime(&currentime));
		   
		  sleep(1);
      
		  for(i=0;i<BUFF_COUNT;i++){
        byte_count += read(pd[0], &buff[i], sizeof(buff)/BUFF_COUNT);
		    printf("[PID: %i, PPID: %d] Father. i: %d rnd: %d\n", getpid(), getppid(), i, buff[i]);
		  }
		  close(pd[0]);
		  //printf("[PID: %i, PPID: %d] Father. byte_count: %d\n", getpid(), getppid(), byte_count);

      // wait for child to finish 
      waitpid(pid, &status, 0);  
      child_exit_status = WEXITSTATUS(status);
      if (child_exit_status == byte_count) {
        printf("\n[PID: %i, PPID: %d] Father. byte_count of father (%i) equals byte_count of child (%i)\n", getpid(), getppid(), byte_count, child_exit_status);
      } else {
        printf("\n[PID: %i, PPID: %d] Father. byte_count of father (%i) is not equal to byte_count of child (%i)\n", getpid(), getppid(), byte_count, child_exit_status);
      }

      time(&currentime);
		  printf("\n[PID: %i, PPID: %d] Father has finised. Child-PID: %i. Current time: %s\n", getpid(), getppid(), pid, ctime(&currentime));
      
		  exit(0);
	 } else {						  // Child
		  printf("\n[PID: %i, PPID: %d] Child.\n", getpid(), getppid());
      close(pd[0]);
      int byte_count_child=0, rnd;

		  srand(time(NULL));

		  int i;
		  for(i=0;i<BUFF_COUNT;i++){
		    rnd = (int) rand()%100 + 1;
		    byte_count_child += write(pd[1],&rnd, sizeof(int));
        printf("\n[PID: %i, PPID: %d] Child. i: %d: rnd: %d\n", getpid(), getppid(), i, rnd);
			  usleep(500000);    // sleep 500ms
		  }
		  close(pd[1]);
		  exit(byte_count_child);
	 }

	 return 0;
}


void sig_fkt(int sig)
{
	 printf("\n[PID: %i, PPID: %d] catching sig: %d\n",
			  getpid(), getppid(), sig);
}