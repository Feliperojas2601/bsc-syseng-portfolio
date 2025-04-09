/** 
 * @file server.c 
 * @version 1.0
 * @date 31/05/21
 * @author jrojasce-mbolanoss
 * @title P2-Server 
 * @brief Programa referente al servidor encargado de procesar hasta 32 peticiones simultaneas 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "structsandfunctions.h"
#include <signal.h>
#define PORT 3535
#define BACKLOG 32
#define MAXCLIENTS 32

//Formato de escritura del log
const char *LOG_FORMAT = "[Fecha %d%02d%02dT%d%d%d] Cliente [%s] [%f - %d - %d]\n";

//Variables para sockets
int serverfd, clientfd, r, opt = 1;
struct sockaddr_in server, client;
socklen_t tamano = sizeof(struct sockaddr_in);

//Mutex, variable condicional para gestionar los hilos y arreglo de hilos
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t threads[MAXCLIENTS];
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

int main()
{
    // Configuracion de CTRL+C 
    struct sigaction sa; 
    sa.sa_handler = &handleExit; 
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT,&sa,NULL);

    //Creamos los hilos
    for (int j = 0; j < MAXCLIENTS; j++)
    {
        pthread_create(&threads[j], NULL, thread_function, NULL);
    }

    //Configuracion del socket
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0)
    {
        perror("\n-->Error en socket():");
        exit(-1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(server.sin_zero, 8);
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(int));
    r = bind(serverfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if (r < 0)
    {
        perror("\n-->Error en bind(): ");
        exit(-1);
    }
    r = listen(serverfd, BACKLOG);
    if (r < 0)
    {
        perror("\n-->Error en Listen(): ");
        exit(-1);
    }

    //Ciclo infinito para aceptar y encolar peticiones
    while (true)
    {
        printf("Conectando ...\n");
        clientfd = accept(serverfd, (struct sockaddr *)&client, &tamano);
        if (clientfd < 0)
        {
            perror("\n-->Error en accept: ");
            exit(-1);
        }
        char *dirIp = inet_ntoa(client.sin_addr);
        printf("Conexion desde: %s\n", dirIp);
        fflush(stdout);
        pthread_mutex_lock(&lock);
        insertar(clientfd);
        pthread_cond_signal(&condition_var);
        pthread_mutex_unlock(&lock);
    }
    return 0;
}

void *thread_function(void *arg)
{
    //Ciclo infinito que busca en la cola un cliente en espera y le asigna un hilo
    while (true)
    {
        int clientfd;
        pthread_mutex_lock(&lock);
        if ((clientfd = extraer()) == -1){
            pthread_cond_wait(&condition_var,&lock);
            clientfd = extraer();
        }
        pthread_mutex_unlock(&lock);
        if (clientfd != -1){
            printf("Entrando a handle con: %d \n", clientfd);
            handleConnection(clientfd);
        }else{
            sleep(1);
        }
    }
}

void *handleConnection(int clientfd)
{
    //Variables para la busqueda
    int newClient = clientfd;
    int r;
    int option = 0;
    int dest = 0;
    int origin = 0;
    int hour = 0;
    float result = 0.0;

    while(true){
        //Se reciben los datos del cliente
        r = recv(newClient, &option, sizeof(option), 0);
        if(r == -1) perror("\n-->Error en recv OPTION: ");

        if(option == 5){
            break;
        }
        r = recv(newClient, &origin, sizeof(origin), 0);
        if(r == -1) perror("\n-->Error en recv ORIGIN: ");
        r = recv(newClient, &dest, sizeof(dest), 0);
        if(r == -1) perror("\n-->Error en recv DEST: ");
        r = recv(newClient, &hour, sizeof(hour), 0);
        if(r == -1) perror("\n-->Error en recv HOUR: ");
        
        //Se hace la busqueda y se envía el resultado y el tiempo al cliente
        clock_t start, end;
        start = clock();
        result = searchTime(hash(origin-1), dest, hour);
        end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;   
        
        r = send(newClient, &result, sizeof(result), 0);
        if(r < 0) perror("\n-->Error en send(): ");  

        r = send(newClient, &seconds, sizeof(seconds), 0);
        if(r < 0) perror("\n-->Error en send(): ");  

        //Se registra la operación en el log
        pthread_mutex_lock(&lock);
        writeLog(dest, origin, result, client);     
        pthread_mutex_unlock(&lock); 
    }
    close(newClient);
}

//Funcion hash
int hash(int x)
{
    return ((15 * x + 6) % 1163) % 1160;
}

int writeLog(int dest, int origin, float result, struct sockaddr_in client)
{
    FILE *file = fopen("log.dat", "a");
    if (file == NULL)
    {
        perror("Error al abrir archivo log\n");
        return 1;
    }

    //Esto se usa para obtener los datos de la fecha y hora
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //Se obtiene la ip privada del cliente
    struct in_addr ipAddr = client.sin_addr;
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ipAddr, clientIP, INET_ADDRSTRLEN);

    //Se escribe el registro al final del archivo
    fseek(file, 0, SEEK_END);
    fprintf(file, LOG_FORMAT, tm.tm_year + 1900, tm.tm_mon, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec, clientIP, result, origin, dest);

    fclose(file);
}

float searchTime(int pos, int idDest, int hour)
{
    //Se abre el archivo
    FILE *csv = fopen("hashTable.dat", "r");

    //Se revisa si hubo error
    if (csv == NULL)
    {
        perror("Error al abrir el archivo");
        exit(1);
    }

    //Se llega hasta la linea indicada
    char c = EOF;
    short linecount = 1;
    while ((c = fgetc(csv)) != EOF)
    {
        if (c == '\n')
        {
            if (linecount++ == pos)
            {
                break;
            }
        }
    }
    int idDestTable = -1;
    int hourTable = -1;
    char lineJump = -1;
    float timeTable = -1;

    //Se lee el id de origen
    fscanf(csv, "%d", &idDestTable);
    while (1)
    {
        //Se lee el id destino, la hora y el tiempo
        fscanf(csv, "%d", &idDestTable);
        fscanf(csv, "%d", &hourTable);
        fscanf(csv, "%f", &timeTable);

        //Se revisa si se encontró una coincidencia
        if (idDestTable == idDest && hour == hourTable)
        {
            return timeTable;
        }

        //Se revisa si se llegó al final de la línea
        lineJump = fgetc(csv);
        if (lineJump == 10)
        {
            break;
        }
    }
    fclose(csv);
    return -1.0;
}
void handleExit(int sig){
    close(serverfd); 
    for (int j = 0; j < MAXCLIENTS; j++)
    {
        pthread_cancel(threads[j]);
    }
    exit(0);
}