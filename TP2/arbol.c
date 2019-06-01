#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "arbol.h"

Nodo* crearNodo(int valor) {
    Nodo *nodo = (Nodo*) malloc(sizeof(Nodo));
    if (nodo == NULL) return NULL;
    nodo->valor = valor;
    nodo->nivel = 1;
    nodo->izq = nodo->der = NULL;
    return nodo;
}

Arbol* crearArbol() {
    Arbol *arbol = (Arbol*) malloc(sizeof(Arbol));
    if (arbol == NULL) return NULL;
    arbol->raiz = arbol->eliminado = NULL;

    return arbol;
}

void eliminarNodo(Nodo *nodo) {
    assert(nodo);
    if (nodo == NULL) return;
    if (nodo->izq != NULL) eliminarNodo(nodo->izq);
    if (nodo->der != NULL) eliminarNodo(nodo->der);
    free(nodo);
}

void eliminarArbol(Arbol *arbol) {
    assert(arbol && arbol->raiz);
    eliminarNodo(arbol->raiz);
    free(arbol);
}

/**
 * Rotación a la derecha para reemplazar un "link horizontal" a izquierda con un "link horizontal" a la derecha.
 * La torsión mantiene el nivel de los nodos.
 *
 * Ejemplo:
 *
 *       |          |
 *   A - B    ->    A - B
 *  /   / \        /   / \
 * 0   1   2      0   1   2
 * @param nodo
 * @return nodo
 */
Nodo* torsion(Nodo *nodo) {
    if (nodo == NULL || nodo->izq == NULL || nodo->nivel != nodo->izq->nivel) return nodo;
    Nodo *izq = nodo->izq;
    nodo->izq = izq->der;
    izq->der = nodo;
    return izq;
}


/**
 * Rotación a la izquierda y aumento de nivel para reemplazar un subárbol con dos o más "links horizontales" a
 * la derecha con otro de dos links menos.
 *
 * Ejemplo:
 *
 *   |                      |
 *   |                    - B -
 *   |                   /     \
 *   A - B - C    ->    A       C
 *  /   /   / \        / \     / \
 * 0   1   2   3      0   1   2   3
 *
 * @param nodo
 * @return nodo
 */
Nodo* division(Nodo *nodo) {
    if (nodo == NULL || nodo->der == NULL || nodo->der->der == NULL || nodo->der->der->nivel != nodo->nivel) return nodo;
    Nodo *der = nodo->der;
    nodo->der = der->izq;
    der->izq = nodo;
    der->nivel++;
    return der;
}

int min(int a, int b) {
    return a < b? a : b;
}

Nodo* buscarValor(Arbol *arbol, Nodo *nodo, int valor) {
    if (nodo == NULL) return NULL;
    else if (nodo->valor == valor) return nodo;
    else if (nodo->valor > valor) return buscarValor(arbol, nodo->izq, valor);
    else return buscarValor(arbol, nodo->der, valor);
}

Nodo* buscar(Arbol *arbol, int valor) {
    return buscarValor(arbol, arbol->raiz, valor);
}

Nodo* insertarBalanceado(Arbol *arbol, Nodo *nodo, int valor) {
    if (nodo == NULL) {
        return crearNodo(valor);
    }

    if (valor < nodo->valor) {
        nodo->izq = insertarBalanceado(arbol, nodo->izq, valor);
    } else if (valor > nodo->valor) {
        nodo->der = insertarBalanceado(arbol, nodo->der, valor);
    } else return nodo;

    nodo = torsion(nodo);
    nodo = division(nodo);
    return nodo;
}

void insertar(Arbol *arbol, int valor) {
    arbol->raiz = insertarBalanceado(arbol, arbol->raiz, valor);
}

int nivel(Nodo *nodo) {
    if (nodo == NULL) return 0;
    return nodo->nivel;
}

Nodo* eliminarBalanceado(Arbol *arbol, Nodo *nodo, int valor) {
    if (nodo == NULL) return nodo;

    if (valor < nodo->valor) {
        nodo->izq = eliminarBalanceado(arbol, nodo->izq, valor);
    } else if (valor > nodo->valor) {
        nodo->der = eliminarBalanceado(arbol, nodo->der, valor);
    } else {
        if (nodo->izq == NULL && nodo->der == NULL) {
            // Caso hoja.
            eliminarNodo(nodo);
            return NULL;
        }

        if (nodo->izq == NULL) {
            // Busco sucesor y lo roto con el actual.
            Nodo *temp = nodo->der;
            while (temp->izq != NULL) temp = temp->izq;
            nodo->der = eliminarBalanceado(arbol, nodo->der, temp->valor);
            nodo->valor = temp->valor;
        } else {
            // Busco predecesor y lo roto con el actual.
            Nodo *temp = nodo->izq;
            while (temp->der != NULL) temp = temp->der;
            nodo->izq = eliminarBalanceado(arbol, nodo->izq, temp->valor);
            nodo->valor = temp->valor;
        }
    }

    int nivelCandidato = min(nivel(nodo->izq), nivel(nodo->der)) + 1;

    if (nivelCandidato < nivel(nodo)) {
        nodo->nivel = nivelCandidato;
        if (nodo->der != NULL && nivelCandidato < nivel(nodo->der)) {
            nodo->der->nivel = nivelCandidato;
        }
    }

    return nodo;
}

void eliminar(Arbol *arbol, int valor) {
    arbol->raiz = eliminarBalanceado(arbol, arbol->raiz, valor);
}

void preOrderNodo(Nodo *nodo, void (*callback)(Nodo*)) {
    if (nodo == NULL) return;

    callback(nodo);
    preOrderNodo(nodo->izq, callback);
    preOrderNodo(nodo->der, callback);
}

void preOrder(Arbol *arbol, void (*callback)(Nodo*)) {
    preOrderNodo(arbol->raiz, callback);
}

void inOrderNodo(Nodo *nodo, void (*callback)(Nodo*)) {
    if (nodo == NULL) return;

    preOrderNodo(nodo->izq, callback);
    callback(nodo);
    preOrderNodo(nodo->der, callback);
}

void inOrder(Arbol *arbol, void (*callback)(Nodo*)) {
    inOrderNodo(arbol->raiz, callback);
}

void postOrderNodo(Nodo *nodo, void (*callback)(Nodo*)) {
    if (nodo == NULL) return;

    preOrderNodo(nodo->izq, callback);
    preOrderNodo(nodo->der, callback);
    callback(nodo);
}

void postOrder(Arbol *arbol, void (*callback)(Nodo*)) {
    postOrderNodo(arbol->raiz, callback);
}
