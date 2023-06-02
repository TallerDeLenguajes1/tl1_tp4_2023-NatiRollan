#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} typedef Tarea;

struct Nodo {
    Tarea T;
    struct Nodo *Siguiente; //puntero llamado enlace
};
typedef struct Nodo* Lista;

//Declaro funciones y procedimientos
Lista crearListaVacia();
Lista crearNodo(Lista cabecera, Tarea x); 
Tarea crearTarea(int id);
void cargarTareas(Lista *cabecera);
void mostrarTarea(Tarea T);
void liberarNodo(Lista nodo);
Lista quitarNodo(Lista *cabecera, Tarea id);
Lista insertarNodo(Lista cabecera, Lista nodo);  //inserta tarea al inicio de la lista
void moverTarea(Lista *pendiente, Lista *realizadas);
Lista buscaTareaPorId(Lista cabecera, int idBuscado);
Lista buscaTareaPorPalabra(Lista cabecera, char *palabraBuscada);
Lista consultarTareas(Lista H, Lista P);
Lista borrar(Lista cabecera);

int main ()
{
    //Creo mis listas vacias.
    Lista TareasPendientes, TareasRealizadas; //punteros que apuntan a una estructura nodo (cabecera)
    TareasPendientes = crearListaVacia(); //puntero que a punta a NULL
    TareasRealizadas = crearListaVacia();

    //Cargo tareas
    cargarTareas(&TareasPendientes);

    //Muevo tareas
    moverTarea(&TareasPendientes, &TareasRealizadas);

    //Muestro tareas
    Lista auxP = TareasPendientes, auxR = TareasRealizadas;
    puts("----Tareas Pendientes----");
    while (auxP != NULL)
    {
        mostrarTarea(auxP->T);
        auxP = auxP->Siguiente;
    }
    puts("----Tareas Realizadas----");
    while (auxR != NULL)
    {
        mostrarTarea(auxR->T);
        auxR = auxR->Siguiente;
    }

    //Busco tarea
    Lista ayuda;
    ayuda = consultarTareas(TareasPendientes, TareasRealizadas);
    if (ayuda)
    {
        puts("----Tarea Buscada----");
        mostrarTarea(ayuda->T);
    }

    //Libero memoria dinamica
    while (TareasPendientes != NULL)
    {
        TareasPendientes = borrar(TareasPendientes);
    }
    while (TareasRealizadas != NULL)
    {
        TareasRealizadas = borrar(TareasRealizadas);
    }

    return 0;
}

//Desarrollo funciones y procedimientos
Lista crearListaVacia(){
    return NULL;
}

Lista crearNodo(Lista cabecera, Tarea x){
    Lista nuevoNodo;
    nuevoNodo = (Lista) malloc(sizeof(struct Nodo));
    nuevoNodo->Siguiente = cabecera;
    nuevoNodo->T = x;
    cabecera = nuevoNodo;
    return cabecera;
}

Tarea crearTarea(int id){
    Tarea nueva;
    char *buff=(char *) malloc(sizeof(char) * 500);
    nueva.TareaID = id;
    fflush(stdin);
    printf("Ingrese descripcion: ");
    gets(buff);
    nueva.Descripcion = (char *) malloc(sizeof(char) * (strlen(buff)+1));
    strcpy(nueva.Descripcion, buff);
    free(buff);
    printf("Ingrese la duracion (10-100): ");
    scanf("%d", &nueva.Duracion);
    return nueva;
}

void cargarTareas(Lista *cabecera){
    int respuesta=1;

    for (int i = 1; respuesta; i++)
    {
        *cabecera = crearNodo(*cabecera, crearTarea(i));
        printf("Desea ingresar otra tarea? (0=no, 1=si) \n");
        scanf("%d", &respuesta);
    }
}

void mostrarTarea(Tarea T){
    printf("TareaID: %d\n", T.TareaID);
    printf("Descripcion: %s\n", T.Descripcion);
    printf("Duracion: %d\n", T.Duracion); 
}

void liberarNodo(Lista nodo){
    free(nodo);
}

Lista quitarNodo(Lista *cabecera, Tarea id){
    Lista aux = *cabecera, anterior = *cabecera;
    while (aux != NULL && aux->T.TareaID != id.TareaID)
    {
        anterior = aux;
        aux = aux->Siguiente;
    }

    if (aux)  //si aux no es nulo
    {
        if (aux == *cabecera)  //verifico si es el primer nodo de la lista.
        {
            *cabecera = aux->Siguiente;
        } else
        {
            anterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL;  //el enlace del nodo aux apunta a NULL para que no esté vinculado a la lista
    }
    return aux;
}

Lista insertarNodo(Lista cabecera, Lista nodo)
{
    if (cabecera == NULL) {
        // Si la lista está vacía, el nuevo nodo se convierte en la cabeza de la lista
        cabecera = nodo;
    } else {
        // Si la lista no está vacía, el nuevo nodo se enlaza al inicio y se actualiza la cabeza de la lista
        nodo->Siguiente = cabecera;
        cabecera = nodo;
    }
    return cabecera;
}

void moverTarea(Lista *pendiente, Lista *realizada){
    int respuesta;
    Lista aux=*pendiente, nodo;
    while (aux != NULL)
    {
        mostrarTarea(aux->T);
        printf("Tarea Realizada? (0=no, 1=si): ");
        scanf("%d", &respuesta);
        if (respuesta)
        {
            nodo=aux;
            aux = aux->Siguiente;
            nodo = quitarNodo(pendiente, nodo->T);
            *realizada = insertarNodo(*realizada, nodo);
        } else
        {
            aux = aux->Siguiente;
            
        }
        
    }
    
}

Lista buscaTareaPorId(Lista cabecera, int idBuscado){
    Lista aux=NULL;
    while (cabecera != NULL)
    {
        if (cabecera->T.TareaID == idBuscado)
        {
            aux = cabecera;
        }
        cabecera = cabecera->Siguiente;
    }
    return aux;
}

Lista buscaTareaPorPalabra(Lista cabecera, char *palabraBuscada){
    Lista aux=NULL;
    while (cabecera != NULL)
    {
        if (strstr(cabecera->T.Descripcion, palabraBuscada) != NULL)
        {
            aux = cabecera;
        }
        cabecera = cabecera->Siguiente;
    }
    return aux;   
}

Lista consultarTareas(Lista H, Lista P){
    int respuesta, id;
    Lista aux=NULL;
    char *palabra=(char *) malloc(sizeof(char) * 100);

    printf("Buscar tarea en especifico? (0=no, 1=si)");
    scanf("%d", &respuesta);
    
    if (respuesta)
    {
        printf("En que lista quiere consultar? (0 = Lista Pendiente, 1 = Lista Realizada)");
        scanf("%d", &respuesta);
        if (respuesta)
        {
            printf("Consultar por id o palabra? (0=id, 1=palabra)");
            scanf("%d", &respuesta);
            if (respuesta)
            {
                fflush(stdin);
                printf("Ingrese la palabra: ");
                gets(palabra);
                aux = buscaTareaPorPalabra(P, palabra);
            } else
            {
                printf("Ingrese el ID de la tarea: ");
                scanf("%d", &id);
                aux = buscaTareaPorId(P, id);
            }
        } else
        {
            printf("Consultar por id o palabra? (0=id, 1=palabra)");
            scanf("%d", &respuesta);
            if (respuesta)
            {
                fflush(stdin);
                printf("Ingrese la palabra: ");
                gets(palabra);
                aux = buscaTareaPorPalabra(H, palabra);
            } else
            {
                printf("Ingrese el ID de la tarea: ");
                scanf("%d", &id);
                aux = buscaTareaPorId(H, id);
            }
        }
    }
    free(palabra);
    return aux;
}

Lista borrar(Lista cabecera){
    Lista primerNodo;
    primerNodo = cabecera;
    cabecera = cabecera->Siguiente;
    free(primerNodo);
    return cabecera;
}