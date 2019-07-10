#ifndef TPFINAL_CLIENTES_H
#define TPFINAL_CLIENTES_H

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
 *
 * @return el cliente agregado.
 */
Cliente* cliente_nuevo_con_referido(unsigned char *nombre, Fecha *nacimiento, int referente_id);

/**
 * Agrega un cliente.
 *
 * @param nombre
 * @param nacimiento
 *
 * @return el cliente agregado.
 */
Cliente* cliente_nuevo(unsigned char *nombre, Fecha *nacimiento);

Clientes* clientes();

/**
 * Busca un cliente en el índice.
 * @param id
 * @return el cliente, si existe, o {@code NULL}.
 */
Cliente* cliente_indice(int id);

/**
 * Busca clientes por nombre.
 * @param busqueda
 * @return los clientes encontrados que concuerden con la búsqueda.
 */
Clientes* cliente_buscar_nombre(char *busqueda);

/**
 * Busca clientes en un rango de edad.
 *
 * @param min desde qué edad.
 * @param max hasta qué edad.
 * @return los clientes encontrados que concuerden con la búsqueda.
 */
Clientes* cliente_buscar_edad_rango(int min, int max);

/**
 * Limpia toda la base de datos de clientes.
 */
void cliente_borrar_todo();

#endif //TPFINAL_CLIENTES_H
