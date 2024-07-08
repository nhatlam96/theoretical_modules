/*Nhat-Lam Luong; inf3381*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t processid;
	if ((processid = fork()) < 0){
		perror("Fork hat nicht stattgefunden.\n");
		return EXIT_FAILURE;
	}
	else if(processid == 0){
        sleep(5);
        printf("\t[PID: %i, PPID: %i] Child.\n", getpid(), getppid());		
	}
	else
	{
        sleep(10);
		printf("\t[PID: %i, PPID: %i] Father.\n", getpid(), getppid());
	}
	sleep(2);
	return EXIT_SUCCESS;
}
