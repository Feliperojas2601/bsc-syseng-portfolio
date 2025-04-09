#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3535

int main(int argc, char* argv[])
{
    int clientfd, r;
    struct sockaddr_in client;
    struct hostent *he;
    int pruebas = 10; 
    int size = atoi(argv[1]); 
    double * buffer;
    buffer= (double *)malloc(size*sizeof(double));

    if(size >= 1250000 ){
        pruebas = 1; 
    }

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0)
    {
        perror("\n-->Error en socket():");
        exit(-1);
    }
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);

    inet_aton(argv[2], &client.sin_addr);

    r = connect(clientfd, (struct sockaddr *)&client, (socklen_t)sizeof(struct sockaddr));

    for(int i=0; i<pruebas; i++){
        int aux=0; 
        while(r = recv(clientfd, buffer, sizeof(buffer), 0) >0){
            aux = aux+r; 
            if(aux >= size){
                break; 
            }
        }

        r=send(clientfd, "Confirmacion", 16*sizeof(char), 0);

    }

    close(clientfd);
    free(buffer);
}