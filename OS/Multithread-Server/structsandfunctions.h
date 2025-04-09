/** 
 * @file structsandfunctions.h 
 * @version 1.0
 * @date 31/05/21
 * @author jrojasce-mbolanoss
 * @title Estructuras de Datos y Funciones utilizadas
 * @code
int main(){
    //Variables para sockets
    int serverfd, clientfd, r, opt = 1;
    struct sockaddr_in server, client;
    socklen_t tamano = sizeof(struct sockaddr_in);

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
void *thread_function(void *arg){
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
void *handleConnection(int clientfd){
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

 * @endcode
 * @brief Estructuras de datos para representar una cola y funciones utilizadas en la configuración del servidor
*/
#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/**
 * @brief Estructura para almacenar un dato entero y fabricar implicitamente una cola
 */
struct nodo {
    int info;
    struct nodo *sig;
};

/** 
 * @brief Inicializacion  de nodo raiz para la cola
 */
struct nodo *raiz=NULL;
/** 
 * @brief Inicializacion  de nodo fondo para la cola
 */
struct nodo *fondo=NULL;

/**
 * @brief insertar Inserta un nuevo dato en la cola
 * @param x Dato entero a insertar
 * @return No retorna ningun valor
 */
void insertar(int x)
{
    struct nodo *nuevo;
    nuevo=malloc(sizeof(struct nodo));
    nuevo->info=x;
    nuevo->sig=NULL;
    if (raiz == NULL)
    {
        raiz = nuevo;
        fondo = nuevo;
    }
    else
    {
        fondo->sig = nuevo;
        fondo = nuevo;
    }
}

/** 
 * @brief extraer Extrae el dato en la cabeza de la cola
 * @return Retorna un entero en la cabeza de la cola
 */
int extraer()
{
    if (raiz != NULL)
    {
        int informacion = raiz->info;
        struct nodo *bor = raiz;
        if (raiz == fondo)
        {
            raiz = NULL;
            fondo = NULL;
        }
        else
        {
            raiz = raiz->sig;
        }
        free(bor);
        return informacion;
    }
    else{
        return -1;
    }
}

/**
 * @brief writeLog Escribe en archivo .log un formato con información acerca de la fecha, IP del cliente, valores ingresados, entre otros
 * @param dest Dato entero referente al ID de destino ingresado por el cliente
 * @param origin Dato entero referente al ID de origen ingresado por el cliente
 * @param result Dato real referente al resultado de la busqueda con los datos ingresados
 * @param client Estructura de datos con la dirección IP del cliente
 * @return Retorna 1 en caso de error al abrir el archivo
 */
int writeLog(int dest, int origin, float result, struct sockaddr_in client);

/**
 * @brief searchTime Busca en un archivo de datos el tiempo promedio de viaje
 * @param pos Dato entero referente al ID de origen ingresado por el cliente que simboliza la posicion de linea de la informacion
 * @param idDest Dato entero referente al ID de destino ingresado por el cliente
 * @param hout Dato entero referente a la hora ingresada por el cliente
 * @return Retorna un valor real de tiempo promedio de viaje
 */
float searchTime(int pos, int idDest, int hour);

/**
 * @brief hash Calcula un valor de la tabla de datos utilizando una funcion Hash
 * @param x Dato entero a calcular
 * @return Retorna un valor entero referente a una posicion de la tabla de datos
 */
int hash(int x);

/**
 * @brief handleConnection Funcion que dada la conexion a un cliente se encarga de recibir datos y cerrar la conexion 
 * @param clientfd Dato entero a insertar
 * @return No retorna ningun valor
 */
void *handleConnection(int clientfd);

/**
 * @brief thread_function Funcion lanzada en la creación de los hilos encargada de comprobar posibles conexiones de clientes en espera 
 * @return No retorna ningun valor
 */
void *thread_function(void *arg);

/**
 * @brief handleExit Funcion encargada de cancelar los hilos y cerrar el server luego fe una señal
 * @param sig Señal (CTRL+C)
 * @return No retorna ningun valor
 */
void handleExit(int sig);
#endif