#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defino estructuras
struct Tarea{
    int TareaID; //Numerado en ciclo iterativo 
    char *Descripcion; 
    int Duracion; // entre 10 – 100
} typedef Tarea;
typedef Tarea item;
struct Nodo{
    item T;
    struct Nodo *Siguiente;
};
typedef struct Nodo* Lista;

//Defino funciones
Lista crearListaVacia();
Lista crearNodo(Lista H, item x);
Tarea crearTarea(int iter);
void cargarTareas(Lista *H);
void mostrarTarea(Tarea task);
void EliminarTarea(Lista nodo);
Lista quitarNodo(Lista *H, item id);
Lista insertarNodo(Lista H, Lista nodo);
void estatusTarea(Lista *H, Lista *L);
Lista buscaTareaPorId(Lista H, int idBuscado);
Lista buscaTareaPorPalabra(Lista H, char *palabraBuscada);
Lista consultarTareas(Lista H, Lista P);
Lista borrar(Lista H);

int main(){
    //Defino listas
    Lista TareasPendientes, TareasRealizadas, TareasEnProceso;

    //Creo listas vacias
    TareasPendientes = crearListaVacia();
    TareasRealizadas = crearListaVacia();
    TareasEnProceso = crearListaVacia();

    //Cargo tareas
    cargarTareas(&TareasPendientes);

    //Muevo tareas
    estatusTarea(&TareasPendientes, &TareasRealizadas);

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
    //Funciones buscar
    Lista ayuda;
    ayuda = consultarTareas(TareasPendientes, TareasRealizadas);
    if (ayuda)
    {
        puts("----Tarea Buscada----");
        mostrarTarea(ayuda->T);
    }
    //Libero memoria
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
//Desarrollo las funciones
Lista crearListaVacia(){
    return NULL;
}
Lista crearNodo(Lista H, item x){
    Lista nuevoNodo;
    nuevoNodo = (Lista) malloc(sizeof(struct Nodo));
    nuevoNodo->Siguiente = H;
    nuevoNodo->T = x;
    H = nuevoNodo;
    return H;
}
Tarea crearTarea(int iter){
    Tarea nueva;
    char *buff=(char *) malloc(sizeof(char) * 500);
    nueva.TareaID = iter;
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
void cargarTareas(Lista *H){
    int respuesta=1;

    for (int i = 1; respuesta; i++)
    {
        *H = crearNodo(*H, crearTarea(i));
        printf("Desea ingresar otra tarea? (0=no, 1=si) \n");
        scanf("%d", &respuesta);
    }
}
void mostrarTarea(Tarea task){
    printf("TareaID: %d\n", task.TareaID);
    printf("Descripcion: %s\n", task.Descripcion);
    printf("Duracion: %d\n", task.Duracion); 
}
void EliminarTarea(Lista nodo){
    free(nodo);
}

Lista quitarNodo(Lista *H, item id){
    Lista aux = *H, anterior = *H;
    while (aux != NULL && aux->T.TareaID != id.TareaID)
    {
        anterior = aux;
        aux = aux->Siguiente;
    }

    if (aux)
    {
        if (aux == *H)
        {
            *H = aux->Siguiente;
        } else
        {
            anterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL;
    }
    return aux;
}

Lista insertarNodo(Lista H, Lista nodo){
    nodo->Siguiente = H;
    H = nodo;
    return H;
}

void estatusTarea(Lista *H, Lista *L){
    int respuesta;
    Lista aux=*H, nodo;
    while (aux != NULL)
    {
        mostrarTarea(aux->T);
        printf("Tarea Realizada? (0=no, 1=si): ");
        scanf("%d", &respuesta);
        if (respuesta)
        {
            nodo=aux;
            aux = aux->Siguiente;
            nodo = quitarNodo(H, nodo->T);
            *L = insertarNodo(*L, nodo);
        } else
        {
            aux = aux->Siguiente;
            
        }
        
    }
    
}

Lista buscaTareaPorId(Lista H, int idBuscado){
    Lista aux=NULL;
    while (H != NULL)
    {
        if (H->T.TareaID == idBuscado)
        {
            aux = H;
        }
        H = H->Siguiente;
    }
    return aux;
}

Lista buscaTareaPorPalabra(Lista H, char *palabraBuscada){
    Lista aux=NULL;
    while (H != NULL)
    {
        if (strstr(H->T.Descripcion, palabraBuscada) != NULL)
        {
            aux = H;
        }
        H = H->Siguiente;
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

Lista borrar(Lista H){
    Lista primerNodo;
    primerNodo = H;
    H = H->Siguiente;
    free(primerNodo);
    return H;
}