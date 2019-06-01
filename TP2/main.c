#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

static void consultar(int *valor) {
    printf("Ingrese el valor...\n");
    scanf("%d", valor);
}

static void agregarElemento(Arbol *arbol) {
    int valor;
    consultar(&valor);
    insertar(arbol, valor);
    printf("Valor agregado.\n\n");
}

static void eliminarElemento(Arbol *arbol) {
    int valor;
    consultar(&valor);
    eliminar(arbol, valor);
    printf("Valor eliminado.\n\n");
}

void imprimirElemento(Nodo *nodo) {
    printf("(%d) ", nodo->valor);
}

void imprimirPreOrder(Arbol *arbol) {
    preOrder(arbol, &imprimirElemento);
}

void imprimirInOrder(Arbol *arbol) {
    inOrder(arbol, &imprimirElemento);
}

void imprimirPostOrder(Arbol *arbol) {
    postOrder(arbol, &imprimirElemento);
}

void imprimirContenido(Arbol *arbol) {
    int opcion;
    do {
        printf("Seleccione método:\n 1- pre-order\n 2- in-order\n 3- post-order\n 0- Volver");
        scanf("%d", &opcion);
    } while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 0);
    
    switch (opcion) {
        case 1:
            imprimirPreOrder(arbol);
            break;
        case 2:
            imprimirInOrder(arbol);
            break;
        case 3:
            imprimirPostOrder(arbol);
            break;
    }

    printf("\n\n");
}

void buscarElemento(Arbol *arbol) {
    int valor;
    consultar(&valor);
    Nodo *nodo = buscar(arbol, valor);

    if (nodo != NULL) {
        printf("Encontrado valor %d en nivel %d.\n\n", valor, nodo->nivel);
    } else {
        printf("Valor %d no encontrado.\n\n", valor);
    }
}

void salir() {
    printf("Cerrando...\n");
    system("exit");
}

static void menu(Arbol *arbol) {
    int opciones;

    do {
        printf("\nMENU"
               "\n1- Agregar elemento"
               "\n2- Eliminar elemento"
               "\n3- Imprimir contenido"
               "\n4- Buscar"
               "\n0- Salir"
               "\nIngrese una Opcion: ");

        scanf("%d", &opciones);

        switch(opciones) {
            case 1:
                agregarElemento(arbol);
                break;
            case 2:
                eliminarElemento(arbol);
                break;
            case 3:
                imprimirContenido(arbol);
                break;
            case 4:
                buscarElemento(arbol);
                break;
            case 0:
                salir();
                break;

            default:
                printf("Opcion Incorrecta.\n Por favor ingrese un numero del 1 al 4 o 0 para salir.\n");
        }

    } while (opciones != 0);
}

int main() {
    Arbol *arbol = crearArbol();

    menu(arbol);
}