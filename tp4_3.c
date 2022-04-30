#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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
nodo* crearNodo(char *descripcion,int id,int duracion);
void insertarNodo(nodo **start,char *descripcion,int id,int duracion);
void mostrarTareas(nodo *start);
void moverTareas(nodo **Tareas, nodo **TareasRealizadas);
void eliminarNodo(nodo *nodo);
tarea buscarTareaId(nodo **Tareas,nodo **TareasRealizadas,int id);
void mostrarTarea(tarea T);
tarea buscarTareaPalabra(nodo **Tareas,nodo **TareasRealizadas,char* palabra);


int main(){
    srand(time(NULL));
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

        insertarNodo(&Tareas,descripcion,i+1,0);
        free(descripcion);//probar
    }
    printf("\n Las tareas ingresadas son: ");
    mostrarTareas(Tareas);


    moverTareas(&Tareas,&TareasRealizadas);

    printf("\t--TAREAS REALIZADAS--\n");
    mostrarTareas(TareasRealizadas);
    printf("\t--TAREAS PENDIENTES--\n");
    mostrarTareas(Tareas);

    //Busqueda por id
    tarea busqueda;
    int id;
    printf("\n\t--BUSQUEDA DE TAREAS POR ID--\n");
    printf("Ingrese el ID de la tarea que busca: \n");
    scanf("%i",&id);
    busqueda = buscarTareaId(&Tareas,&TareasRealizadas,id);
    printf("\nResultado: ");
    mostrarTarea(busqueda);

    //Busqueda por palabra
    char* clave;
    clave = (char*)malloc(sizeof(char)*10);
    printf("\n\t--BUSQUEDA DE TAREAS POR PALABRA--\n");
    printf("Ingrese la palabra clave de la tarea que busca: \n");
    fflush(stdin);
    gets(clave);
    busqueda = buscarTareaPalabra(&Tareas,&TareasRealizadas,clave);
    printf("\nResultado: ");
    if(busqueda.TareaID == 0){
		printf("\nNo se encontraron tareas con esa palabra clave");
	}else{
		mostrarTarea(busqueda);
	}

    free(Tareas);
    free(TareasRealizadas);


    return 0;
}

nodo* crearListaVacia()
{
    return NULL;
}

nodo* crearNodo(char *descripcion,int id,int duracion)
{
    nodo* Tarea = (nodo*)malloc(sizeof(nodo));


    Tarea->t.Descripcion = (char *) malloc(strlen(descripcion+1) * sizeof(char));
    strcpy(Tarea->t.Descripcion, descripcion);
    if(duracion==0){
        Tarea->t.Duracion = rand() % 99;
    }else{
        Tarea->t.Duracion = duracion;
    }
    Tarea->t.TareaID = id;
    
    Tarea->Siguiente=NULL;

    return Tarea;
}

void insertarNodo(nodo **start,char *descripcion,int id,int duracion)
{
    nodo *nuevoNodo = crearNodo(descripcion,id,duracion);
    nuevoNodo->Siguiente = *start;
    *start = nuevoNodo;
}

void mostrarTareas(nodo *start)
{
    nodo * aux=start;
    while (aux)
    {
        printf("\nTarea %i: ",aux->t.TareaID);
        printf("%s",aux->t.Descripcion);
        printf("\nDuracion: %i\n",aux->t.Duracion);
        aux = aux->Siguiente;
    }    
}
void eliminarNodo(nodo *nodo)
{
    if(!nodo) free(nodo);
}

void moverTareas(nodo **Tareas, nodo **TareasRealizadas)
{
    nodo * TareasPendientes = crearListaVacia();
    int realizado;

    printf("\nREVISION DE TAREAS");
    while ((*Tareas)!=NULL)
    {
        printf("\nTarea ID%i: ",(*Tareas)->t.TareaID);
        printf("%s",(*Tareas)->t.Descripcion);
        printf("\nDuracion: %i",(*Tareas)->t.Duracion);

        printf("\tSe realizo la Tarea?(1.Si  0.No)\n");
        scanf("%i",&realizado);

        if(realizado==1){
            //inserto el nodo en tareas realizadas
            insertarNodo(TareasRealizadas, (*Tareas)->t.Descripcion,(*Tareas)->t.TareaID,(*Tareas)->t.Duracion); //no me hace falta el & en realizadas porque ya lo envie asi a la funcion revisar
            //mejorar funcion insertar
        }else{
            insertarNodo(&TareasPendientes, (*Tareas)->t.Descripcion,(*Tareas)->t.TareaID,(*Tareas)->t.Duracion); //no me hace falta el & en realizadas porque ya lo envie asi a la funcion revisar   
        }
        *Tareas = (*Tareas)->Siguiente;
    }
    *Tareas = TareasPendientes;

}

tarea buscarTareaId(nodo **Tareas,nodo **TareasRealizadas,int id)
{
    tarea resultado;
    resultado.TareaID=0;

    while ((*Tareas)!= NULL)
    {
        if (id == (*Tareas)->t.TareaID)
        {
            return (*Tareas)->t;
        }
        *Tareas = (*Tareas)->Siguiente;
    }
    
    while ((*TareasRealizadas)!= NULL)
    {
        if (id == (*TareasRealizadas)->t.TareaID)
        {
            return (*TareasRealizadas)->t;
        }
        *TareasRealizadas = (*TareasRealizadas)->Siguiente;
    }
    return resultado;
}

void mostrarTarea(tarea T){
	printf("\nTarea %d: ", T.TareaID);
	printf("\nDescripcion: %s", T.Descripcion);
	printf("\nDuracion: %d dias", T.Duracion);
	printf("\n");
}

tarea buscarTareaPalabra(nodo **Tareas,nodo **TareasRealizadas,char* palabra)
{
    tarea resultado;

    while ((*Tareas)!= NULL)
    {
        while (*((*Tareas)->t.Descripcion) != '\0')
        {
            if(strstr((*Tareas)->t.Descripcion,palabra))
            {
                return (*Tareas)->t;
            }
            ((*Tareas)->t.Descripcion)++;
        }
        *Tareas = (*Tareas)->Siguiente;
        
    }
    
    while ((*TareasRealizadas)!= NULL)
    {
        while (*((*TareasRealizadas)->t.Descripcion) != '\0')
        {
            if(strstr((*TareasRealizadas)->t.Descripcion,palabra))
            {
                return (*TareasRealizadas)->t;
            }
            ((*TareasRealizadas)->t.Descripcion)++;
        }
        *TareasRealizadas = (*TareasRealizadas)->Siguiente;
    }
    resultado.TareaID = 0;
    return resultado;

}