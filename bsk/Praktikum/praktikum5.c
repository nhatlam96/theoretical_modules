/*
 *  Beispielprogramm fuer threads. WiSe 2020 
 *  Autor: A. Brunner und D. Bub
 */
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


void* Thread2(void*x)
{
	int *i=(int*) x;
	while(*i<10){//5 odd numbers between 0 & 10
		if(*i%2==1){
		 	usleep(2000000); // 2s sleep
			printf("Thread2:Pong\n");
			(*i)++;
			
		}else{
			  usleep(100000); //100ms aktive wait
			  printf("Thread2: aktiv warten\n");
		}
	
	}
	pthread_exit(NULL);
	return NULL;
}

int main()
{
	pthread_t thandler2;//identifier of the thread

	int counter=0;//variable, shared by both threads

    // create thread 2
	if(pthread_create(&thandler2,NULL,Thread2,&counter)){
		perror("pthread_create");
		exit(1);
	}

    // thread 1 
	while(counter<19){//10 even numbers between 0 & 18
		if(counter%2==0){
		    usleep(1000000); // 1s sleep
			printf("Thread1:Ping\n");
			counter++;
		}else{
		  usleep(100000); //100ms aktive wait
		  printf("Thread1: aktiv warten\n");
		}
	}

	//wait for created thread to end
	pthread_join(thandler2,NULL);


	return 0;
}