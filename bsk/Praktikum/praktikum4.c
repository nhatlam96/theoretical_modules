/*
 *  Beispielprogramm fuer fork-Baum. WiSe 2020 
 *  Autor: A. Brunner und D. Bub
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
       

int main(){
   int pid2,pid3,pid4;
   
   // P1
   
   // P1 vor dem fork()
   pid2=fork();
   if((pid2)>0){  // Vater Prozess P1
         
        
         
         pid3=fork();
         if((pid3)>0){  // Vater Prozess P1
             
         printf("[PID: %d, PPID: %d] P1 \n", getpid(), getppid());
           
         int status; 
         wait(&status); 
         wait(&status);
         }else{ // Kind P3
                 
            pid4=fork();
            if((pid4)>0){  // Kind Prozess P3
              printf("[PID: %d, PPID: %d] P3 \n", getpid(), getppid());
                
              int status; 
              wait(&status);
            }else{ // Kind P4
             printf("[PID: %d, PPID: %d] P4 \n", getpid(), getppid());
   
            } 
           
         }  
                     
   }else{ // Kind P2
          
           printf("[PID: %d, PPID: %d] P2\n", getpid(), getppid());
          
   }
         
   return EXIT_SUCCESS;
}