#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Se guarda el id de destino, la hora, y el tiempo, para cada línea
//El número de la línea indica el id de origen
const char* TRAVELDATA_FORMAT = " %d %d %f";

struct TravelData{
    int idOrigin;
    int idDest;
    int hour;
    float time;
};

struct Node{
    struct TravelData dest;
    struct Node *next;
};

struct HashTable{
    struct Node *table[1160];
};

int hash(int x);
void insertNode(struct Node** head, struct TravelData newData);
void printList(struct Node *node);
int writeHashTable(struct HashTable data);

int main()
{   
    //Se abre el archivo
    FILE *csv = fopen("datos_viajes.csv", "r");
    //Se revisa si hubo error
    if(csv == NULL){
        perror("Error al abrir el archivo");
        exit(1);
    }
    //Se crea un char[] en donde se guardará cada linea, y se lee la primera linea del csv
    char str[256];
    //Se lee la linea de nombres de columnas
    fgets(str, sizeof(str), csv);

    //Se crea la hash table
    struct HashTable hashTable;
    for(int i = 0; i<1160; i++){
        hashTable.table[i] = malloc(sizeof(struct Node*));
    }
    int count = 0; 
    while(fgets(str, sizeof(str), csv)!=NULL){
        //Se revisa si ya se llegó al final del archivo
        
        //Se separa la linea por comas
        char *token = strtok(str, ",");

        //Se leen los datos y se crea un struct para guardarlo en la lista enlazada correspondeinte
        int idOriginT = atoi(token);
        token = strtok(NULL, ",");
        int idDestT = atoi(token);
        token = strtok(NULL, ",");
        int hourT = atoi(token);
        token = strtok(NULL, ",");
        float timeT = atof(token);

        struct TravelData newData = {
            .idOrigin = idOriginT,
            .idDest = idDestT,
            .hour = hourT,
            .time = timeT
        };

        //Se calcula la posición de la lista enlazada en donde se agregará el nuevo nodo
        int pos = hash(idOriginT-1);
        //Se imprime la linea leída, para saber el progreso de la ejecución
        insertNode(&hashTable.table[pos], newData);
        printf("line: %d \n", count++);
    }

    fclose(csv);

    writeHashTable(hashTable);

    return 0;
}

//Funcion hash
int hash(int x){
    return ((15*x + 6) % 1163) % 1160;
}

void insertNode(struct Node** head, struct TravelData newData){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    
    struct Node *last = *head;

    //Se agrega el destino al nuevo nodo, y como será el último, el siguiente nodo es nulo
    newNode->dest = newData;
    newNode->next = NULL;

    //Se revisa si la lista está vacia
    if((*head)->dest.idOrigin == 0){
        *head = newNode;
        return;
    }

    //Se llega al final de la lista
    while(last->next != NULL) last = last->next;

    //Se agrega el nuevo nodo
    last->next = newNode;
    return;
}

//Esta función se usó en la etapa de pruebas
void printList(struct Node *node){
    while (node != NULL){
        printf("origin: %d\ndest: %d\nhour: %d\ntime: %f\n\n", node->dest.idOrigin, node->dest.idDest, node->dest.hour, node->dest.time);
        node = node->next;
    } 
}

int writeHashTable(struct HashTable data){
    FILE* file;
    file = fopen("hashTable.dat", "w");
    if(file == NULL){
        return 1;
    }
    //Se recorre la hashTable
    for(int i = 0; i < 1160; i++){
        //Se obtiene la cabeza de la lista
        struct Node* node = data.table[i];
        //Se imprime el id de origen
        fprintf(file, "%d", node->dest.idOrigin);
        while(node != NULL){
            //Por cada elemento de la lista enlazada se imprime todo menos el id de origen
            fprintf(file, TRAVELDATA_FORMAT, node->dest.idDest, node->dest.hour, node->dest.time);
            node = node->next;
        }

        fprintf(file,"\n");
    }
    
    fclose(file);
    return 0;

}