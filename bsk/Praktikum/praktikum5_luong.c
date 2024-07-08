/* Nhat-Lam Luong inf3381; 26-10-2020 */
/* Praktikum 5 Aufgabe 4 */
/* gcc -pthread -Wall -o executable code.c */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SEKUNDE 1


struct sharedContainer{
    int* sharedCounter;
    pthread_mutex_t sharedMutex;
};


void* thread2_method (void *init_sharedVariables){
    struct sharedContainer * sharedVariables = (struct sharedContainer *) init_sharedVariables;

    printf("Thread 2: Start of Method\n");
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&sharedVariables->sharedMutex);
        if((*sharedVariables->sharedCounter) % 2 == 1){
            (*sharedVariables->sharedCounter)++;
        }
        sleep(SEKUNDE*2);
        printf("Thread 2: Pong\n");
        pthread_mutex_unlock(&sharedVariables->sharedMutex);
    }

    printf("Thread 2: End of Method\n");
    return NULL;
}


int main(){
    /* pthread_t thread1 == bash is first thread */
    printf("Thread 1: Start of Process\n");

    /* struct class == share variables globally */
    struct sharedContainer sharedVariables;
    int mainCounter = 0;
    sharedVariables.sharedCounter = &mainCounter;

    /* synchronize the threads via locks */
    pthread_mutex_t mainMutex; pthread_mutex_init(&mainMutex, NULL);
    sharedVariables.sharedMutex = mainMutex;
    
    /* odds and pong */
    pthread_t thread2;
    if(!(pthread_create(&thread2, NULL, thread2_method, &sharedVariables))) 
    printf("Thread 2: Start of Process\n");
    else perror("Error on: pthread_create of thread2\n");

    /* even and ping */
    printf("Thread 1: Start of Method\n");
    for(int i = 0; i < 10; i++){
        pthread_mutex_lock(&mainMutex);
        if(mainCounter % 2 == 0){
            mainCounter++;
        }
        sleep(SEKUNDE*1);
        printf("Thread 1: Ping\n");
        pthread_mutex_unlock(&mainMutex);
    }
    printf("Thread 1: End of Method\n");

    /* tie loose ends */
    pthread_mutex_destroy(&mainMutex);
    if(!(pthread_join(thread2, NULL))) printf("Thread 2: End of Process\n");
    printf("Thread 1: End of Process\n");

	return EXIT_SUCCESS;
}

/* personal mental note: On success, pthread_create() returns 0; on error, it returns an error number, and the contents of *thread are undefined.*/
/* personal mental note: On success, pthread_join() returns 0; on error, it returns an error number.*/
