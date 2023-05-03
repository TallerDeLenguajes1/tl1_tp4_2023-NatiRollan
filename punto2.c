#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} typedef Tarea;

void inicializarArreglo (Tarea **arreglo, int cantidad);
void cargarTareas (Tarea **arreglo, int cantidad, char *buff);
void mostrarTarea (Tarea *arreglo);  //muestra una tarea
Tarea* buscarTareaPorID(Tarea **arreglo, int cantidad, int comparar); 
Tarea* buscarTareaPorPalabra(Tarea **arreglo, int cantidad, char *palabraClave);

int main ()
{
    //----1
    int ctdadTareas;
    printf("Ingrese la cantidad de tareas que quiere cargar: ");
    scanf("%d", &ctdadTareas);

    //----2
    //creo un arreglo de punteros dobles dinamicamente
    Tarea **tareasPendientes;
    tareasPendientes = (Tarea **) malloc(ctdadTareas*sizeof(Tarea *));
    inicializarArreglo(tareasPendientes, ctdadTareas);

    //----3
    char *buff = (char *) malloc(200*sizeof(char));
    cargarTareas(tareasPendientes, ctdadTareas, buff);

    //----4
    int respuesta, j=0;
    Tarea **tareasRealizadas = (Tarea **) malloc(ctdadTareas*sizeof(Tarea *));
    inicializarArreglo(tareasRealizadas, ctdadTareas);
    for (int i = 0; i < ctdadTareas; i++)
    {
        puts("\n------ Tarea ----------");
        mostrarTarea(tareasPendientes[i]);  //en la posición i tengo un puntero simple.
        printf("\nRealizo la tarea? 1(si)-0(no): ");
        scanf("%d", &respuesta);
        if (respuesta == 1)
        {
            tareasRealizadas[j] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
            j++;
        }
    }

    //----5
    puts("-------- Tareas Realizadas ----------");
    for (int i = 0; i < ctdadTareas; i++)
    {
        if (tareasRealizadas[i] != NULL)
        {
            mostrarTarea(tareasRealizadas[i]);
        }
    }

    puts("-------- Tareas Pendientes ----------");
    for (int i = 0; i < ctdadTareas; i++)
    {
        if (tareasPendientes[i] != NULL)
        {
            mostrarTarea(tareasPendientes[i]);
        }
    }

    //----6
    Tarea *tareaBuscadaP, *tareaBuscadaR;
    int id;
    printf("\nIngrese id de la tarea que busca: ");
    scanf("%d", &id);
    tareaBuscadaP = buscarTareaPorID(tareasPendientes, ctdadTareas, id);
    tareaBuscadaR = buscarTareaPorID(tareasRealizadas, ctdadTareas, id);
    if (tareaBuscadaP == NULL && tareaBuscadaR == NULL)
    {
        puts("No se encontro la tarea");
    } else
    {
        puts("Si se encontro la tarea");
        puts("\n------ Tarea ----------");
        if (tareaBuscadaP == NULL)
        {
            mostrarTarea(tareaBuscadaR);
        } else
        {
            mostrarTarea(tareaBuscadaP);
        }
    }

    //----7
    fflush(stdin);
    char palabraClave[50];
    printf("\nIngrese la palabra clave a buscar: ");
    gets(palabraClave);
    Tarea *tareaBuscadaPorPalabraP = buscarTareaPorPalabra(tareasPendientes, ctdadTareas, palabraClave);
    Tarea *tareaBuscadaPorPalabraR = buscarTareaPorPalabra(tareasRealizadas, ctdadTareas, palabraClave);
    if (tareaBuscadaPorPalabraP == NULL && tareaBuscadaPorPalabraR == NULL)
    {
        puts("No se encontro la tarea");
    } else
    {
        puts("Si se encontro la tarea");
        puts("\n------ Tarea ----------");
        if (tareaBuscadaPorPalabraP == NULL)
        {
            mostrarTarea(tareaBuscadaPorPalabraR);
        } else
        {
            mostrarTarea(tareaBuscadaPorPalabraP);
        }
    }

    //libero memorias dinamicas
    // Liberar memoria de las estructuras Tarea y las cadenas de descripción
    for (int i = 0; i < ctdadTareas; i++)
    {
        if (tareasPendientes[i] != NULL)
        {
            free(tareasPendientes[i]->Descripcion);
            free(tareasPendientes[i]);
        }
    }

    // Liberar memoria del arreglo tareasPendientes
    free(tareasPendientes);

    // Liberar memoria de las estructuras Tarea y las cadenas de descripción
    for (int i = 0; i < ctdadTareas; i++)
    {
        if (tareasRealizadas[i] != NULL) //*
        {
            free(tareasRealizadas[i]->Descripcion);
            free(tareasRealizadas[i]);
        }
    }

    // Liberar memoria del arreglo tareasRealizadas
    free(tareasRealizadas);
    free(buff);
    
    return 0;
}

void inicializarArreglo (Tarea **arreglo, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        arreglo[i] = NULL;
    }
}

void cargarTareas (Tarea **arreglo, int cantidad, char *buff)
{
    for (int i = 0; i < cantidad; i++)
    {
        arreglo[i] = (Tarea *) malloc(sizeof(Tarea));
        printf("\n----------- TAREA -----------\n");
        arreglo[i]->TareaID = i+1;
        fflush(stdin);
        printf("Ingrese una descripcion: ");
        gets(buff);
        arreglo[i]->Descripcion = (char *) malloc((strlen(buff)+1) * sizeof(char));
        strcpy(arreglo[i]->Descripcion, buff);
        printf("\nIngrese duracion entre 10 y 100: ");
        scanf("%d", &arreglo[i]->Duracion);
    }
}

void mostrarTarea (Tarea *arreglo)
{
    printf("\nTarea ID: %d", arreglo->TareaID);
    printf("\nDescripcion: %s", arreglo->Descripcion);
    printf("\nDuracion: %d\n", arreglo->Duracion);
}

Tarea* buscarTareaPorID(Tarea **arreglo, int cantidad, int comparar)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (arreglo[i] != NULL && arreglo[i]->TareaID == comparar)
        {
            return arreglo[i];
        }
    }
    
    return NULL;
}

Tarea* buscarTareaPorPalabra(Tarea **arreglo, int cantidad, char *palabraClave)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (arreglo[i] != NULL && strstr(arreglo[i]->Descripcion, palabraClave) != NULL)
        {
            return arreglo[i];
        }
    }
    
    return NULL;
}

//* garantiza que solo se intente liberar la memoria si el puntero tareasRealizadas[i] apunta 
//a una tarea que existe. Si el puntero es NULL, significa que no hay ninguna tarea asignada en esa posición
// y no es necesario liberar la memoria.