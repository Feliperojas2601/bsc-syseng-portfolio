#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
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

    int fd,r, pruebas =10;
    int size = atoi(argv[1]); 
    double * trash; 
    double promedio = 0; 
    trash = (double *) malloc(size*sizeof(double)); 

    if(size >= 1250000 ){
        pruebas = 1; 
    }

    for(int j = 0; j<size; j++){
        trash[j]=0; 
    }

    /*if( mkfifo("./FIFO",0666) == -1 ){
        printf("Error creando FIFO \n");
        return 1;
    }*/
    /*if( mkfifo("./FIFOAUX",0666) == -1 ){
        printf("Error creando FIFO \n");
        return 1;
    }*/

    for(int i = 0; i<pruebas; i++){
        struct timeval begin, end;
        gettimeofday(&begin, 0);
        gettimeofday(&end, 0);

        int aux = 0; 
        fd = open("./FIFO",O_WRONLY);
        if(fd < 0){
            printf("Error abriendo FIFO. \n");
        }
        while(r = write(fd,trash+aux, sizeof(trash)-aux) >0){
            aux = aux+r; 
            if(aux >= size-1){
                break; 
            }
        }
        close(fd);

        fd = open("./FIFOAUX",O_RDONLY);
        if(fd < 0){
            printf("Error abriendo FIFO. \n");
        }
        char *mensaje = (char*)malloc(16*sizeof(char)); 
        r = read(fd,mensaje, sizeof(mensaje)); 
        free(mensaje);
        close(fd);

        gettimeofday(&end, 0);
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds + microseconds*1e-6;
        promedio = promedio + elapsed; 
    }

    free(trash);
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
                printf("Para el tamaño 100KB\t\t Tiempo: %f s.\n",promedio/pruebas); 
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
}