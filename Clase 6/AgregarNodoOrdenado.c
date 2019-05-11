#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct structNodo {

    int valor;

    struct structNodo *siguiente;
};

typedef struct structNodo Lista;

typedef struct structNodo Nodo;

void getLista (Lista *miLista)
{
    int i = 0;

    while(miLista != NULL)
    {
        printf("Elemento[%d]----> %d \n", i, miLista->valor);

        i++;

        miLista = miLista->siguiente;
    }
}


Lista * agregarNodo(Lista *miLista, Nodo *nodo)
{
    Lista *aux;
    aux = miLista;

    if(miLista == NULL)
    {
        return nodo;
    }
    else if (nodo->valor < aux->valor)
    {
        nodo->siguiente = aux;

        return nodo;
    }
    else
    {
        while(aux->siguiente != NULL && aux->siguiente->valor < nodo->valor)
        {
            aux = aux->siguiente;
        }
        nodo->siguiente = aux->siguiente;

        aux->siguiente = nodo;

        return aux;
    }
}
Lista* agregarAlFinal(Lista *miLista, Nodo *nodo) {
    if (miLista == NULL) {
        return nodo;
    }

    Lista *aux = miLista;
    while (aux->siguiente != NULL) {
        aux = aux->siguiente;
    }

    aux->siguiente = nodo;
    nodo->siguiente = NULL;

    return miLista;
}


int getLongitud(Lista *miLista) {
    int longitud = 0;

    while( miLista != NULL ) {
        longitud++;
        miLista = miLista->siguiente;
    }

    return longitud;
}

Lista* ordenar(Lista* miLista) {
    Lista* cursorX = miLista;

    while (cursorX != NULL) {
        int valorX = cursorX->valor;
        Lista* cursorY = cursorX->siguiente;

        while (cursorY != NULL) {
            int valorY = cursorY->valor;

            if (valorX > valorY) {
                cursorX->valor = valorY;
                cursorY->valor = valorX;
            }

            cursorY = cursorY->siguiente;
        }

        cursorX = cursorX->siguiente;
    }

    return miLista;
}

int main(){

    Lista miLista;
    Lista *lista = &miLista;
    lista->valor = 5;
    lista->siguiente = NULL;

    Nodo nodo;
    Nodo *nodo1 = &nodo;
    nodo1->valor = 9;
    nodo1->siguiente = NULL;
    lista = agregarAlFinal(lista, nodo1);


    Nodo nodoA;
    Nodo *nodo2 = &nodoA;
    nodo2->valor = 2;
    nodo2->siguiente = NULL;
    lista = agregarAlFinal(lista, nodo2);

    getLista(lista);
    lista = ordenar(lista);
    getLista(lista);

/*
   Nodo otroNodo2;
   Nodo *nodo3 = &otroNodo2;
   nodo3->valor = 4;
   nodo3->siguiente = NULL;

   agregarNodo(lista, nodo3);
*/
    getLista(lista);
}

