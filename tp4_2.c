#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} tarea;

void cargarTareas (tarea **Tareas, int cantTareas);
void mostrarTareas (tarea **Tareas, int cantTareas);
void revisarTareas (tarea** Tareas,tarea **, int cantTareas);
void mostrarTareasRealizadas (tarea **Tareas,tarea **TareasRealizadas, int cantTareas);
tarea *BuscarTarea (tarea **Tareas, tarea **TareasRealizadas, int cantTareas);


int main(){

    int cantTareas;
    tarea **Tareas;
    tarea **TareasRealizadas;
    tarea *tareaBuscada;
    tarea *tareaBuscada2;
    
    printf("Ingrese la Cantidad de tareas a cargar\n");
    scanf("%d",&cantTareas);
    
    Tareas = (tarea **) malloc(sizeof(tarea*)*cantTareas);
    TareasRealizadas = (tarea **) malloc(sizeof(tarea*)*cantTareas);
    

    cargarTareas(Tareas,cantTareas);
    mostrarTareas(Tareas,cantTareas);
    revisarTareas(Tareas,TareasRealizadas,cantTareas);
    mostrarTareasRealizadas(Tareas,TareasRealizadas,cantTareas);

    fflush(stdin);
    tareaBuscada2 = BuscarTarea(Tareas,TareasRealizadas, cantTareas);
    if(tareaBuscada2 != NULL){
        printf("\n------- TAREA ENCONTRADA por palabra-------\n");
        printf("Tarea ID: %d\n", tareaBuscada2->TareaID);
        printf("Descripcion: %s\n", tareaBuscada2->Descripcion);
        printf("Duracion: %d\n", tareaBuscada2->Duracion);
    }

    free(Tareas);
    free(TareasRealizadas);
    
    return 0;
}

void cargarTareas (tarea **Tareas, int cantTareas)
{    
    char *buff = (char *) malloc(100 * sizeof(char));
    
    for (int i=0; i < cantTareas; i++)
    {
        *(Tareas+i)=(tarea *)malloc(sizeof(tarea));
        (*(Tareas+i))->TareaID = i+1;

        printf("--> Ingrese la %d) tarea a realizar\n",i+1);
        fflush(stdin);
        gets(buff);
        (*(Tareas+i))->Descripcion = (char *) malloc(strlen(buff+1) * sizeof(char));
        strcpy((*(Tareas+i))->Descripcion,buff);

        printf("\t--> Cuanto dura la tarea?\n");
        scanf("%d",&(*(Tareas+i))->Duracion);
    }

    free(buff);
}

void mostrarTareas (tarea **Tareas, int cantTareas)
{    
    
    for (int j=0; j<cantTareas; j++)
    {
        printf("-->Tarea %d \n",(*(Tareas+j))->TareaID);
        printf("%s\n",(*(Tareas+j))->Descripcion);
        printf("Duracion: %d\n\n",(*(Tareas+j))->Duracion);
    }
    
}

void revisarTareas (tarea** Tareas, tarea ** TareasRealizadas, int cantTareas)
{
    int realizado;
    for (int j=0; j<cantTareas; j++)
    {
        printf("\t¿Se realizo la Tarea?(1.Si  0.No)\n");
        scanf("%i",&realizado);
        if(realizado==1){
            *(TareasRealizadas+j)=(tarea *)malloc(sizeof(tarea)); //me faltaba reservar el espacio de memoria de cada elemento tipo tarea del puntero doble tareasRealizadas
            
            (*(TareasRealizadas+j))->TareaID = (*(Tareas+j))->TareaID;

            (*(TareasRealizadas+j))->Descripcion = (char *) malloc(strlen((*(Tareas+j))->Descripcion) * sizeof(char));
            strcpy((*(TareasRealizadas+j))->Descripcion , (*(Tareas+j))->Descripcion);

            (*(TareasRealizadas+j))->Duracion = (*(Tareas+j))->Duracion;

            (*(Tareas+j))=NULL;

        }else{
            
            (*(TareasRealizadas+j))=NULL;
        }   
    }
    
}
void mostrarTareasRealizadas (tarea **Tareas,tarea **TareasRealizadas, int cantTareas)
{
    printf("\n---------- TAREAS REALIZADAS ----------\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (TareasRealizadas[i] != NULL)
        {
            printf("----------------------------------------\n");
            printf("Tarea ID: %d\n", TareasRealizadas[i]->TareaID);
            printf("Descripcion: %s\n", TareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\n", TareasRealizadas[i]->Duracion);
        }
    }

    printf("\n---------- TAREAS PENDIENTES ----------\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (Tareas[i] != NULL)
        {
            printf("----------------------------------------\n");
            printf("Tarea ID: %d\n", Tareas[i]->TareaID);
            printf("Descripcion: %s\n", Tareas[i]->Descripcion);
            printf("Duracion: %d\n", Tareas[i]->Duracion);
        }
    }
}

tarea *BuscarTarea (tarea **Tareas, tarea **TareasRealizadas, int cantTareas)
{
    char *buffer = (char *)malloc(15*sizeof(char));
    printf("\nIngrese la palabra para buscar la tarea:\n");
    gets(buffer);
    for (int i=0; i < cantTareas; i++)
    {
        if (Tareas[i]!=NULL && strstr(Tareas[i]->Descripcion, buffer))
        {
            return Tareas[i];
        }
        else if (TareasRealizadas[i]!=NULL && strstr(TareasRealizadas[i]->Descripcion, buffer))
        {
            return TareasRealizadas[i];
            free(buffer);//tal vez debe ir ahi en cada return?
        }
    }
    free(buffer); //¿lo esta eliminando o sale antes?
    return NULL;
    
}