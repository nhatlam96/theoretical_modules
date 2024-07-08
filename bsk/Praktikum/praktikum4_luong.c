/*Nhat-Lam Luong; inf3381; 18-10-2020*/
/*Danke an Andrej Alpatov inf3407 fuer die Erklaerungen!!!*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <stdbool.h>





int main()
{

    srand(time(NULL));
    time_t currentTime;
    useconds_t WARTESEKUNDE = 1000000;

    pid_t pid2, pid3, pid4;


    if ((pid2=fork()) == 0) /*PID2-Anfang*/
    {
		printf("\t[PID: %i, PPID: %i] P2.\n", getpid(), getppid());
        
        printf("10 Zufahlszahlen:\t");
        for(int i = 0; i < 10; i++)
        {
            printf("%i\t", rand());
        }
        
        printf("Ende von P2.\n");    
	} /*PID2-Ende*/
    else if ((pid3=fork()) == 0){
        printf("Ich bin P3\n");
    }


	else /*PID1-Anfang*/
    {
		printf("\t[PID: %i, PPID: %i] P1.\n", getpid(), getppid());
        printf("\tHallo Bro\t\n");

        
        if((pid3=fork())==0) /*PID3-Anfang*/
        {
            printf("\t[PID: %i, PPID: %i] P3.\n", getpid(), getppid());


            if((pid4=fork())==0) /*PID4-Anfang*/
            {
                printf("\t[PID: %i, PPID: %i] P4.\n", getpid(), getppid());
                
                while(true)
                {
                    time(&currentTime);
                    printf("Current time: %s", ctime(&currentTime));
                    usleep(WARTESEKUNDE);
                }

                /*printf("P4 schliesst hier?\n"); P4 schliesst sich vor P3, somit muss P1 als letztes schliessen.*/

            } /*PID4-Ende*/

            else /*P3 Commands-Anfang*//*PID4 Else-Anfang*/
            {

                printf("P3 wartet 5 sek\n");
                usleep(WARTESEKUNDE*5);

                printf("P4 angehaltet\n");
                kill(pid4, 19);

                printf("P3 wartet 3 sek\n");
                usleep(WARTESEKUNDE*3);

                printf("In 5 sekunden wird P4 terminiert\n");
                kill(pid4, 18);
                usleep(WARTESEKUNDE*5);

                printf("Ende von P4.\n");  
                kill(pid4, 9);

            } /*P3 Commands-Ende*//*PID4 Else-Ende*/

            printf("Ende von P3.\n");
            exit(1);

        } /*PID3-Ende*/

        wait( &pid3 );
        wait( &pid2 );
        printf("Ende von P1.\n");

	} /*PID1-Ende*/
	

	return 0;
}
