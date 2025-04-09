#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/time.h>

// Declaration of thread condition variable
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

char* trash;
int readyToWrite = 0;

void * handleFile(void* arg){
    int size = *(int*)arg;

    pthread_mutex_lock(&lock);

    //productor
    if(readyToWrite == 1){
        key_t key = ftok("shmfile",65);
        int shmid = shmget(key,size,0666|IPC_CREAT);

        char *memBlock = (char*) shmat(shmid,(void*)0,0);
        //Se escribe en el bloque de memoria
        strncpy(memBlock,trash,size);
        
        shmdt(memBlock);

        pthread_cond_signal(&cond);
    }else{//Consumidor
        readyToWrite = 1;
        //Se espera hasta que el productor acabe
        pthread_cond_wait(&cond, &lock);
        key_t key = ftok("shmfile",65);

        int shmid = shmget(key,size,0666|IPC_CREAT);

        char *memBlock = (char*) shmat(shmid,(void*)0,0);

        strncpy(trash,memBlock,size);

        shmdt(memBlock);
        
        shmctl(shmid,IPC_RMID,NULL);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main( int argc, char *argv[]){
    char *s;

    pthread_t t1, t2;
    long seconds, microseconds;
    double elapsed = 0.0;
 
    int size = atoi(argv[1]);
    trash = (char *) malloc(size);

    switch(size){
        case 1000:
            s = "1KB";
            break;
        case 10000:
            s = "10KB";
            break;
        case 100000:
            s = "100KB";
            break;
        case 1000000:
            s = "1MB";
            break;
        case 10000000:
            s = "10MB";
            break;
        case 100000000:
            s = "100MB";
            break;
        default:
            s = "XXX";
            break;
    }

    for(int i=0; i<size; i++){
        trash[i] = 'a';
    }

    for(int i=0; i<10; i++){
        //Se comienza a medir el tiempo
        struct timeval begin, end;
        gettimeofday(&begin, 0);

        //Consumidor
        pthread_create(&t1, NULL, handleFile, &size);
        //Productor
        pthread_create(&t2, NULL, handleFile, &size);

        pthread_join(t2, NULL);
        pthread_join(t1, NULL);

        //Se termina de medir el tiempo
        gettimeofday(&end, 0);
        seconds = end.tv_sec - begin.tv_sec;
        microseconds = end.tv_usec - begin.tv_usec;
        elapsed += seconds + microseconds*1e-6;

        //Se reinician las variables de los mutex
        pthread_mutex_destroy(&lock);
        pthread_mutex_init(&lock, NULL);
        pthread_cond_destroy(&cond);
        pthread_cond_init(&cond, NULL);
        readyToWrite = 0;
    }

    printf("Para el tamaño %s\t\t Tiempo: %f s.\n", s, elapsed/10.0);
    free(trash);

    return 0;
}