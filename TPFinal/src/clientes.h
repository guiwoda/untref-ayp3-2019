#ifndef TPFINAL_CLIENTES_H
#define TPFINAL_CLIENTES_H

#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct {
    unsigned int id;
    char *nombre;
    time_t nacimiento;
    unsigned int referente_id;
} Cliente;

typedef struct {
    Cliente *prev;
    Cliente *current;
    Cliente *next;
} Clientes;

/**
 * @return el próximo ID a usar para un cliente.
 */
unsigned int cliente_proximo_id();

/**
 * Agrega un cliente con referido.
 *
 * @param nombre
 * @param nacimiento
 * @param referente_id
 *
 * @return el cliente agregado.
 */
Cliente* cliente_nuevo_con_referido(char *nombre, time_t nacimiento, int referente_id);

/**
 * Agrega un cliente.
 *
 * @param nombre
 * @param nacimiento
 *
 * @return el cliente agregado.
 */
Cliente* cliente_nuevo(char *nombre, time_t nacimiento);

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

#endif //TPFINAL_CLIENTES_H
