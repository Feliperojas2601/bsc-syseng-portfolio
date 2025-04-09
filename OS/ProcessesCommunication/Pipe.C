#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char* argv[]){

    int size = atoi(argv[1]);
    int pipefd[2]; 
    int pipefdaux[2]; 
    int r,pruebas=10; 
    double promedio =0; 
    double * trash; 
    double * buffer;
    trash = (double *) malloc(size*sizeof(double)); 
    buffer= (double *)malloc(size*sizeof(double));

    if(size >= 1250000){
        pruebas = 1; 
    }
    
    for(int j = 0; j<size; j++){
        trash[j]=0; 
    }


    r= pipe(pipefd); 
    if (r<0){
        printf("Error pipe"); 
        exit(-1);
    }

    pid_t pid; 
    pid = fork(); 
    if(pid < 0){
        printf("Error Fork"); 
        exit(-1); 
    }

    if(pid == 0){
        for(int i = 0; i<pruebas; i++){
            struct timeval begin, end;
            gettimeofday(&begin, 0);
            gettimeofday(&end, 0);

            int aux = 0;
            close(pipefd[0]);  
            while(r = write(pipefd[1],trash+aux,sizeof(trash)-aux) >0){
                aux = aux+r; 
                if(aux >= size){
                    break; 
                }
            }
            close(pipefd[1]);

            char *mensaje = (char*)malloc(16*sizeof(char)); 
            close(pipefdaux[1]);
            r = read(pipefdaux[0],mensaje, sizeof(mensaje)); 
            close(pipefdaux[0]); 
            free(mensaje);

            gettimeofday(&end, 0);
            long seconds = end.tv_sec - begin.tv_sec;
            long microseconds = end.tv_usec - begin.tv_usec;
            double elapsed = seconds + microseconds*1e-6;
            promedio = promedio + elapsed; 
        }
    }else{
        for(int i = 0; i<pruebas; i++){
            int aux=0; 
            close(pipefd[1]);
            while(r = read(pipefd[0],buffer+aux,sizeof(buffer)-aux) >0){
                aux = aux+r; 
                if(aux >= size){
                    break; 
                }
            }
            close(pipefd[0]); 

            close(pipefdaux[0]); 
            r = write(pipefdaux[1], "Confirmacion", 16*sizeof(char)); 
            close(pipefdaux[1]); 
        }
    }

    switch(size*8){
        case 1000:
            if(promedio >0){
                printf("Para el tamaño 1KB\t\t Tiempo: %f s.\n",promedio/pruebas); 
            }   
            break;
        case 10000:
           if(promedio >0){
                printf("Para el tamaño 10KB\t\t Tiempo: %f s.\n",promedio/pruebas); 
            }   
            break;
        case 100000:
            if(promedio >0){
                printf("Para el tamaño 100KB\t\t Tiempo: %f s.\n", promedio/pruebas); 
            }   
            break;
        case 1000000:
            if(promedio >0){
                printf("Para el tamaño 1MB\t\t Tiempo: %f s.\n",promedio/pruebas); 
            }   
            break;
        case 10000000:
            if(promedio >0){
                printf("Para el tamaño 10MB\t\t Tiempo: %f s.\n",promedio/pruebas); 
            }          
            break;
        case 100000000:
            if(promedio >0){
                printf("Para el tamaño 100MB\t\t Tiempo: %f s.\n",promedio/pruebas); 
            }      
            break;
        default:
            break;
    }
    free(trash);
    free(buffer);
    return 0;

}