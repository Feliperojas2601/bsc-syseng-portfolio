#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>
 
#define PORT 3535
#define BACKLOG 2

int main(int argc, char* argv[]){
 
    int serverfd, clientfd, r, opt = 1;
    struct sockaddr_in server, client;
    socklen_t tamano;
    int pruebas = 10; 
    int size = atoi(argv[1]); 
    double * trash;
    double promedio=0; 
    trash= (double *)malloc(size*sizeof(double));

    for(int j = 0; j<size; j++){
        trash[j]=0; 
    }

    if(size >= 1250000 ){
        pruebas = 1; 
    }
 
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(server.sin_zero, 8); 
    
    setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int));
 
    r = bind(serverfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    
    r = listen(serverfd, BACKLOG);
    
    clientfd = accept(serverfd, (struct sockaddr *)&client, &tamano);
   

    for(int i = 0; i<pruebas; i++){
        struct timeval begin, end;
        gettimeofday(&begin, 0);
        gettimeofday(&end, 0);

        int aux=0; 
        //r = send(clientfd, trash, sizeof(trash), 0);
        while(r = send(clientfd, trash, sizeof(trash), 0) >0){
            aux = aux+r; 
            if(aux >= size){
                break; 
            }
        }

        char *mensaje = (char*)malloc(16*sizeof(char)); 
        r=recv(clientfd,mensaje,sizeof(mensaje),0);
        free(mensaje);
        gettimeofday(&end, 0);
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds + microseconds*1e-6;
        promedio = promedio + elapsed;
        
    }
    
    close(clientfd);   
    //close(serverfd);  
    switch(size*8){
        case 1000:
            if(promedio >0){
                printf("Para el tamaño 1KB\t\t Tiempo: %f s.\n", promedio/pruebas); 
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
                printf("Para el tamaño 1MB\t\t Tiempo: %f s.\n", (promedio/pruebas)); 
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
}