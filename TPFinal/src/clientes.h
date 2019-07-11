#ifndef TPFINAL_CLIENTES_H
#define TPFINAL_CLIENTES_H

#define CLIENTES_COLUMNAS "nombre, nacimiento, referente_id"
#define CLIENTES_COLUMNAS_ID "id, " CLIENTES_COLUMNAS
#define INSERT_CLIENTES "INSERT INTO clientes(" CLIENTES_COLUMNAS ") VALUES(?, ?, ?);"
#define INSERT_CLIENTES_LENGTH strlen(INSERT_CLIENTES) + 1
#define SELECT_CLIENTES "SELECT " CLIENTES_COLUMNAS_ID " FROM clientes;"
#define SELECT_CLIENTES_LENGTH strlen(SELECT_CLIENTES) + 1
#define SELECT_CLIENTES_BUSQUEDA "SELECT " CLIENTES_COLUMNAS_ID " FROM clientes WHERE LOWER(nombre) LIKE '%' || ? || '%';"
#define SELECT_CLIENTES_BUSQUEDA_LENGTH strlen(SELECT_CLIENTES_BUSQUEDA) + 1
#define SELECT_CLIENTE_BY_ID "SELECT " CLIENTES_COLUMNAS_ID " FROM clientes WHERE id = ? LIMIT 1;"
#define SELECT_CLIENTE_BY_ID_LENGTH strlen(SELECT_CLIENTE_BY_ID) + 1

#include <stdlib.h>
#include <limits.h>
#include "common.h"
#include <string.h>

typedef struct {
    unsigned int id;
    unsigned char *nombre;
    Fecha *nacimiento;
    unsigned int referente_id;
} Cliente;

typedef struct _clientes Clientes;

struct _clientes {
    Clientes *prev;
    Cliente *cliente;
    Clientes *next;
};

/**
 * Agrega un cliente con referido.
 *
 * @param nombre
 * @param nacimiento
 * @param referente_id
 * @param callback
 */
void cliente_nuevo_con_referido(unsigned char *nombre, Fecha *nacimiento, int referente_id, void (*callback)(Cliente*));

/**
 * Agrega un cliente.
 *
 * @param nombre
 * @param nacimiento
 * @param callback
 */
void cliente_nuevo(unsigned char *nombre, Fecha *nacimiento, void (*callback)(Cliente*));

/**
 * Lista todos los clientes.
 *
 * @param callback
 */
void clientes(void (*callback)(Cliente*));

/**
 * Busca un cliente en el índice.
 * @param id
 * @param callback
 */
void cliente_indice(int id, void (*callback)(Cliente*));

/**
 * Busca clientes por nombre.
 * @param busqueda
 * @param callback
 */
void cliente_buscar_nombre(char *busqueda, void (*callback)(Cliente*));

/**
 * Busca clientes en un rango de edad.
 *
 * @param min desde qué edad.
 * @param max hasta qué edad.
 * @param callback
 */
void cliente_buscar_edad_rango(int min, int max, void (*callback)(Cliente*));

/**
 * Limpia toda la base de datos de clientes.
 */
void cliente_borrar_todo();

#endif //TPFINAL_CLIENTES_H
