/** 
 * @file p2-client.c 
 * @version 1.0
 * @date 31/05/21
 * @author jrojasce-mbolanoss
 * @title P2-Client 
 * @brief Programa referente al cliente encargado de recibir datos desde una interfaz y enviar al servidor 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define PORT 3535

int main (int argc, char *argv[]){

    // Inicialización de Variables utilizadas.
    int sourceid=0; 
    int dstid=0; 
    int hod=24; 
    int option; 
    float buffer; 
    double time;

    //Se configura el cliente. IP utilizada: 127.0.0.1
    int clientfd, r;
    struct sockaddr_in client;
    struct hostent *he;
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd < 0){
        printf("Error en socket");
        exit(-1);
    }
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    inet_aton(argv[1], &client.sin_addr);
    r = connect(clientfd, (struct sockaddr *)&client, (socklen_t)sizeof(struct sockaddr));
    if(r < 0){
        printf("Error en connect \n");
        exit(-1);
    }
    
    //Ejecutamos la interfaz hasta la opcion 5.
    while (option != 5){
        //Opciones del Programa.
        printf("\n --Menú Cliente-- \n");
        printf("1. Ingresar Origen \n");
        printf("2. Ingresar Destino \n");
        printf("3. Ingresar Hora \n");
        printf("4. Buscar tiempo de viaje medio \n");
        printf("5. Salir \n");
        scanf("%d",&option);

        //Distintas rutinas por opción.
        switch (option){
            case 1: scanf("%d", &sourceid);
                    printf("EL valor ingresado es: %d. Pulse cualquier tecla para continuar.", sourceid);
                    getc(stdin);
                    break;

            case 2: scanf("%d", &dstid);
                    printf("EL valor ingresado es: %d. Pulse cualquier tecla para continuar.", dstid);
                    getc(stdin);
                    break; 

            case 3: scanf("%d",&hod);
                    printf("EL valor ingresado es: %d. Pulse cualquier tecla para continuar.", hod);
                    getc(stdin);
                    break;

            case 4: //Comprobamos posibles errores en los datos ingresados.
                    if(sourceid == 0 || dstid == 0 || hod ==  24){
                        printf("Error. Digite los campos 1,2 y3. \n");
                    }else{
                        if(1160 < sourceid || 0 > sourceid || 0 > dstid || 1160 < dstid){
                            printf("Error. El rango de los ID's debe ser entre 1 y 1160 \n");
                        }else{
                            if( 0>hod || hod > 24){
                                printf("Error. El rango de la hora debe ser entre 0 y 23 \n");
                            }else{

                                // Se envian al servidor los valores ingresados
                                r = send(clientfd, &option,sizeof(option), 0);
                                if(r < 0){
                                    printf("Error en send(option) \n");
                                    exit(-1);
                                }  

                                r = send(clientfd, &sourceid, sizeof(sourceid), 0);
                                if(r < 0){
                                    printf("Error en send(sourceid) \n");
                                    exit(-1);
                                }

                                r = send(clientfd,&dstid,sizeof(dstid), 0);
                                if(r < 0){
                                    printf("Error en send(dstid) \n");
                                    exit(-1);
                                }

                                r = send(clientfd,&hod,sizeof(hod), 0);
                                if(r < 0){
                                    perror("Error en send(hora) \n");
                                    exit(-1);
                                }       

                                //Se recibe los valores procesados por el servidor
                                r = recv(clientfd, &buffer, sizeof(buffer), 0);
                                if(buffer < 0){
                                    printf("Tiempo promedio de viaje: NA\n");
                                }else{
                                    printf("Tiempo promedio de viaje: %f \n",buffer);
                                }

                                r = recv(clientfd, &time, sizeof(time),0);
                                if(time < 0){
                                    printf("Error leyendo tiempo promedio");
                                }else{
                                    printf("Tiempo de busqueda: %f segundos\n", time);
                                }
                            }
                        }
                    }
                    break;

            case 5: 
                    //Se envia la opción ingresada y cerramos el servidor
                    r = send(clientfd,&option,sizeof(option), 0);
                    if(r < 0){
                        printf("Error en send(option 5)\n");
                        exit(-1);
                    }    

                    close(clientfd);
                    break; 

            default://Manejo de error opción no válida. 
                    printf("Error. Opción no válida \n");  
        }
    }
    return 0;
}