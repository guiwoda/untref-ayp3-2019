#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <opencl-c.h>
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

void eliminarNodo(Arbol *arbol, Nodo *nodo) {
    assert(nodo);
    if (nodo == NULL) return;
    if (nodo->izq != NULL) eliminarNodo(arbol, nodo->izq);
    if (nodo->der != NULL) eliminarNodo(arbol, nodo->der);
    free(nodo);
}

void eliminarArbol(Arbol *arbol) {
    assert(arbol && arbol->raiz);
    eliminarNodo(arbol, arbol->raiz);
    free(arbol);
}

Nodo* torsion(Nodo *nodo) {
    if (nodo->izq == NULL || nodo->nivel != nodo->izq->nivel) return nodo;
    Nodo *izq = nodo->izq;
    nodo->izq = izq->der;
    izq->der = nodo;
    nodo = izq;
    return nodo;
}

Nodo* division(Nodo *nodo) {
    if (nodo->der == NULL || nodo->der->der == NULL || nodo->der->der->nivel != nodo->nivel) return nodo;
    Nodo *der = nodo->der;
    nodo->der = der->izq;
    der->izq = nodo;
    nodo = der;
    nodo->nivel++;
    return nodo;
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
        nodo = crearNodo(valor);
        return nodo;
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

Nodo* eliminarBalanceado(Arbol *arbol, Nodo *nodo, int valor) {
    if (nodo == NULL) return nodo;

    if (nodo->valor == valor) {
        if (nodo->izq != NULL) {
            // Busco predecesor y lo roto con el actual.
            Nodo *temp = nodo->izq;
            while (temp->der != NULL) temp = temp->der;
            nodo->valor = temp->valor;
            nodo->izq = eliminarBalanceado(arbol, nodo->izq, nodo->valor);
        } else if (nodo->der != NULL) {
            // Busco sucesor y lo roto con el actual.
            Nodo *temp = nodo->der;
            while (temp->izq != NULL) temp = temp->izq;
            nodo->valor = temp->valor;
            nodo->der = eliminarBalanceado(arbol, nodo->der, nodo->valor);
        } else {
            // No hay predecesor ni sucesor.
            return NULL;
        }
    } else if (valor < nodo->valor) {
        nodo->izq = eliminarBalanceado(arbol, nodo->izq, valor);
    } else if (valor > nodo->valor) {
        nodo->der = eliminarBalanceado(arbol, nodo->der, valor);
    }

    if (nodo->izq != NULL && nodo->der != NULL) {
        if (nodo->nivel == min(nodo->izq->nivel, nodo->der->nivel) + 1) {

        }

        if (nodo == arbol->ultimo && arbol->eliminado != NULL && valor == arbol->eliminado->valor) {
            arbol->eliminado->valor = nodo->valor;
            arbol->eliminado = NULL;
            nodo = nodo->der;
            free(arbol->ultimo);
        } else if (nodo->izq->nivel < nodo->nivel - 1 || nodo->der->nivel < nodo->nivel - 1) {
            nodo->nivel--;
            if (nodo->der->nivel > nodo->nivel) nodo->der->nivel = nodo->nivel;
            nodo = torsion(nodo);
            nodo->der = torsion(nodo->der);
            nodo->der->der = torsion(nodo->der->der);
            nodo = division(nodo);
            nodo->der = division(nodo->der);
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
