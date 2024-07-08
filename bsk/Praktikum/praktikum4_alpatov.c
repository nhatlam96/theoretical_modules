#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>	
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <stdbool.h>

#define WARTEZEIT 1000000

int main(){

	srand(time(NULL));
	
	//To display the curent time
	time_t act_time;
	struct tm *info;
	
	//Process IDs for pocesses from #1 till #4
	pid_t pid, pid_2, pid_3, pid_4;
	
	//Process #2 is created
	if((pid = fork()) == 0){
		printf("Process #2 [PID: %i, PPID: %i]\n\n", getpid(), getppid());
		pid_2 = getpid();
		
		//Output of 10 rundom numbers
		printf("Rundom numbers are:\n");
		for(int i = 0; i < 10; i++)
			printf("%i ", rand());
		
		printf("\n");
		printf("The end of the process #2\n");
		printf("\n");		
		
	} else {
		printf("Hallo, ich bin Prozess #1 [PID: %i, PPID: %i]\n\n", getpid(), getppid());
		
		//Process #3 is created
		if( (pid_3 = fork()) == 0 ){
			printf("Prozess #3 [PID: %i, PPID: %i]\n\n", getpid(), getppid());	
			
			//Process #4 is created
			if((pid_4 = fork()) == 0){
				printf("Process #4 [PID: %i, PPID: %i]\n", getpid(), getppid());
				
				//Endless loop displaying the curent time
				while(true){
					time( &act_time );
					info = localtime( &act_time );
					
					printf("Curent time: %s\n", asctime(info));				
					usleep(WARTEZEIT);
				}
				
			} else{
							
				printf("The process #3 sleeps 5 seconds\n\n");			
				usleep(WARTEZEIT*5);
				
				printf("The process #4 is suspended\n");					
				kill(pid_4, 19);
				
				printf("The process #3 sleeps 3 seconds\n");
				usleep(WARTEZEIT*3);
				
				printf("The process #4 continued\n");
				kill(pid_4, 18);
				
				//Process #4 have to be killed, because of endless cycle
				//Can also be terminated using the kill command in the console
				usleep(WARTEZEIT*5);
				kill(pid_4, 9);
				
				printf("The end of the process #4\n");
				printf("The end of the process #3\n");
				exit(1);
			}
		}
		
		//Process #1
		wait( &pid_2 );
		wait( &pid_3 );
		printf("The end of the process #1\n");
	}
	
	return 0;	
}