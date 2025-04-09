/*  Sistemas Operativos 2021-1 
    Practica 1
    Programa #1 : Interfaz de Usuario 
    Desarrollado por: 
    Miguel Bolaños 
    Felipe Rojas
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main (){

    // Inicialización de Variables utilizadas.
    int sourceid=0; 
    int dstid=0; 
    int hod=24; 
    int option; 
    float buffer; 
    double time;
    int fd;

    //Se crea el FIFO
    if( mkfifo("./FIFO",0666) == -1 ){
        printf("Error creando FIFO \n");
        return 1;
    }
    
    //Ejecutamos la interfaz hasta la opcion 5.
    while (option != 5){
        //Opciones del Programa.
        printf("\n Bienvenido \n\n");
        printf("1. Ingresar Origen \n");
        printf("2. Ingresar Destino \n");
        printf("3. Ingresar Hora \n");
        printf("4. Buscar tiempo de viaje medio \n");
        printf("5. Salir \n");
        scanf("%d",&option);

        //Distintas rutinas por opción.
        switch (option){
            case 1: scanf("%d", &sourceid);
                    break; 
            case 2: scanf("%d", &dstid);
                    break; 
            case 3: scanf("%d",&hod);
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
                                // Se abre el FIFO para escritura
                                fd = open("./FIFO",O_WRONLY);
                                if(fd < 0){
                                    printf("Error abriendo FIFO. \n");
                                }

                                //Se escriben los datos ingresados en el FIFO
                                if(write(fd,&option, sizeof(option))==-1){
                                    printf("Error escribiendo option \n");
                                }
                                if(write(fd,&sourceid, sizeof(sourceid))==-1){
                                    printf("Error escribiendo sourceID \n");
                                }
                                if(write(fd,&dstid,sizeof(dstid))==-1){
                                    printf("Error escribiendo destID \n");
                                }
                                if(write(fd,&hod,sizeof(hod))==-1){
                                    printf("Error escribiendo Hora \n");
                                }

                                close(fd);

                                //Se abre el fifo en modo lectura
                                fd = open("./FIFO",O_RDONLY);
                                if(fd < 0){
                                    printf("Error abriendo FIFO. \n");
                                }

                                //Se leen los datos que escribió el proceso de búsqueda
                                if(read(fd,&buffer,sizeof(buffer))==-1){
                                    printf("Error leyendo tiempo promedio");
                                }
                                if(buffer < 0){
                                    printf("Tiempo promedio de viaje: NA\n");
                                }else{
                                    printf("Tiempo promedio de viaje: %f \n",buffer);
                                }
                                if(read(fd,&time,sizeof(time))==-1){
                                    printf("Error leyendo tiempo promedio");
                                }else{
                                    printf("Tiempo de busqueda: %f segundos\n", time);
                                }
                                close(fd);
                            }
                        }
                    }
                    break;

            case 5: 
                    //Se abre el FIFO para escritura
                    fd = open("./FIFO",O_WRONLY);
                    if(fd < 0){
                        printf("Error abriendo FIFO. \n");
                    }

                    //Se escribe la opción ingresada
                    if(write(fd,&option, sizeof(option))==-1){
                        printf("Error escribiendo option \n");
                    }
                    close(fd);

                    //Se elimina el FIFO
                    if(remove("./FIFO")!=0){
                        printf("Error eliminando FIFO");
                    }

                    break; 

            default://Manejo de error opción no válida. 
                    printf("Error. Opción no válida \n");  
        }
    }
    return 0;
}