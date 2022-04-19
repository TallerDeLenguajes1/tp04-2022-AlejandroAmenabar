#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} tarea;

void cargarTareas (tarea **Tareas, int cantTareas);
void mostrarTareas (tarea **Tareas,tarea **TareasRealizadas, int cantTareas);
void mostrarTareasRealizadas (tarea **Tareas,tarea **TareasRealizadas, int cantTareas);

int main(){
    int cantTareas;
    tarea **Tareas;
    tarea **TareasRealizadas;


    printf("Ingrese la Cantidad de tareas a cargar\n");
    scanf("%d",&cantTareas);
    
    Tareas = (tarea **) malloc(sizeof(tarea*)*cantTareas);
    TareasRealizadas = (tarea **) malloc(sizeof(tarea*)*cantTareas);
    

    cargarTareas(Tareas,cantTareas);
    mostrarTareas(Tareas,TareasRealizadas,cantTareas);
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

void mostrarTareas (tarea **Tareas,tarea **TareasRealizadas, int cantTareas)
{    
    int realizado;
    for (int j=0; j<cantTareas; j++)
    {
        printf("-->Tarea %d \n",(*(Tareas+j))->TareaID);
        printf("%s\n",(*(Tareas+j))->Descripcion);
        printf("Duracion: %d\n\n",(*(Tareas+j))->Duracion);

        printf("\t¿Se realizo la Tarea?(1.Si  0.No)\n");
        scanf("%i",&realizado);
        if(realizado==1){

            (*(TareasRealizadas+j))->TareaID = (*(Tareas+j))->TareaID;
            strcpy((*(TareasRealizadas+j))->Descripcion , (*(Tareas+j))->Descripcion);
            (*(TareasRealizadas+j))->Duracion = (*(Tareas+j))->Duracion;

            (*(Tareas+j))=NULL;

        }else{
            (*(TareasRealizadas+j))=NULL;
        }   


    }
    
}