#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Tarea{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} tarea;

typedef struct Nodo{
    tarea t;
    struct Nodo *Siguiente;
} nodo;

nodo* crearListaVacia();
nodo* crearNodo(char *descripcion,int id);
void insertarNodo(nodo **start,char *descripcion,int id);
void mostrarTareas(nodo *start);

int main(){
    nodo *Tareas=crearListaVacia();
    nodo *TareasRealizadas=crearListaVacia();
    int cantTareas;

    //cargar tareas
    printf("cuantas tareas desea ingresar? ");
    scanf("%i",&cantTareas);

    for (int i=0; i < cantTareas; i++)
    {
        char *descripcion = (char *) malloc(100 * sizeof(char));
        printf("--> Ingrese la %d) tarea a realizar\n",i+1);
        fflush(stdin);
        gets(descripcion);

        insertarNodo(&Tareas,descripcion,i+1);

    }
    
    mostrarTareas(Tareas);



    return 0;
}

nodo* crearListaVacia()
{
    return NULL;
}

nodo* crearNodo(char *descripcion,int id)
{
    nodo* Tarea = (nodo*)malloc(sizeof(nodo));


    Tarea->t.Descripcion = (char *) malloc(strlen(descripcion+1) * sizeof(char));
    strcpy(Tarea->t.Descripcion, descripcion);

    Tarea->t.Duracion = rand() % 99;
    Tarea->t.TareaID = id;
    
    Tarea->Siguiente=NULL;

    return Tarea;
}

void insertarNodo(nodo **start,char *descripcion,int id)
{
    nodo *nuevoNodo = crearNodo(descripcion,id);
    nuevoNodo->Siguiente = *start;
    *start = nuevoNodo;
}

void mostrarTareas(nodo *start)
{
    nodo * aux=start;
    while (aux->Siguiente)
    {
        printf("\nTarea %i: ",aux->t.TareaID);
        printf("%s",aux->t.Descripcion);
        printf("\nDuracion: %i",aux->t.Duracion);
        aux = aux->Siguiente;
    }
}