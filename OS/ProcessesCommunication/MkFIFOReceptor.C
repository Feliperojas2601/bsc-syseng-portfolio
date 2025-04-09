#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    int fd, r, pruebas =10;
    int size = atoi(argv[1]); 
    double * buffer;
    buffer= (double *)malloc(size*sizeof(double)); 

    if(size >= 1250000 ){
        pruebas = 1; 
    }
    
    for(int i = 0; i<pruebas; i++){
        int aux = 0;
        fd = open("./FIFO",O_RDONLY);
        if(fd < 0){
            printf("Error abriendo FIFO. \n");
        }
        while(r = read(fd,buffer+aux, sizeof(buffer)-aux) >0){
            aux = aux+r; 
            if(aux >= size-1){
                break; 
            }
        }
        close(fd);

        fd = open("./FIFOAUX",O_WRONLY);
        if(fd < 0){
            printf("Error abriendo FIFO. \n");
        }
        r = write(fd,"Confirmacion", 16*sizeof(char));
        close(fd);
    }
    free(buffer);
}