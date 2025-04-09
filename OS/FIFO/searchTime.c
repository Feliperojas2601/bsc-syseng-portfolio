#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int hash(int x);
float searchTime(int pos, int idDest, int hour);

int main(){

    int fd;

    while(1){
        //Se leen los datos enviados por el menú
        int idOrigin, idDest, hour, option;
        //Se abre el FIFO para lectura
        fd = open("./FIFO",O_RDONLY);
        if(fd < 0){
            printf("Error abriendo FIFO. \n");
        }

        if(read(fd, &option, sizeof(option)) == -1){
            printf("Error leyendo idOrigen\n");
        }
        //Esto es en caso de que el usuario termine la ejecución del menú
        if(option == 5){
            break;
        }

        if(read(fd, &idOrigin, sizeof(idOrigin)) == -1){
            printf("Error leyendo idOrigen\n");
        }
        if(read(fd, &idDest, sizeof(idDest)) == -1){
            printf("Error leyendo idDest\n");
        }
        if(read(fd, &hour, sizeof(hour)) == -1){
            printf("Error leyendo hora\n");
        }
        close(fd);

        //Se calcula el tiempo de ejecución de la búsqueda
        clock_t start, end;
        start = clock();
        float result = searchTime(hash(idOrigin-1), idDest, hour);
        end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC; 

        //Se abre el FIFO para escritura
        fd = open("./FIFO",O_WRONLY);
        if(fd < 0){
            printf("Error abriendo FIFO. \n");
        }

        //Se escribe el resultado en el FIFO
        if(write(fd, &result, sizeof(result)) == -1){
            printf("Error escribiendo resultado\n");
        }
        //Se escribe el tiempo de ejecución en el FIFO
        if(write(fd, &seconds, sizeof(seconds)) == -1){
            printf("Error escribiendo tiempo de ejecucion\n");
        }

        close(fd);
    }

    close(fd);



    return 0;
}

//Funcion hash
int hash(int x){
    return ((15*x + 6) % 1163) % 1160;
}

float searchTime(int pos, int idDest, int hour){
    //Se abre el archivo
    FILE *csv = fopen("hashTable.dat", "r");
    //Se revisa si hubo error
    if(csv == NULL){
        perror("Error al abrir el archivo");
        exit(1);
    }

    char line[3500000];

    //Se llega hasta la linea indicada
    int count = 0;
    while(count != pos){
        fgets(line, sizeof(line), csv);
        count++;
    }
    
    fgets(line, sizeof(line), csv);
    char *token = strtok(line, " ");
    //Se salta el primer token que corresponde al id de origen
    token = strtok(NULL, " ");
    //Este contador sirve para saber si está leyendo el idDest, la hora o el tiempo
    int item = 0;

    while( token != NULL ) {

        int idDestTable;
        int hourTable;
        float timeTable;

        //Cada if verifica que item se está leyendo
        if(item == 2){
            //Se lee el tiempo del viaje
            timeTable = atof(token);
            item = 0;
            if(idDestTable == idDest && hour == hourTable){
                return timeTable;
            }
        }else if (item == 0){
            //Se lee el id de del destino
            idDestTable = atoi(token);
            item++;
        }else if (item == 1){
            //Se lee la hora del viaje
            hourTable = atoi(token);
            item++;
        }

        //Se pasa al siguiente token
        token = strtok(NULL, " ");

    }
    

    fclose(csv);
    return -1.0;
}
