#ifndef TPFINAL_CLIENTES_H
#define TPFINAL_CLIENTES_H

#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct _cliente {
    unsigned int id;
    char *nombre;
    time_t nacimiento;
    unsigned int referente_id;
} Cliente;

unsigned int cliente_proximo_id();
Cliente* cliente_referido(char *nombre, time_t nacimiento, int referente_id);
Cliente* cliente_nuevo(char *nombre, time_t nacimiento);
Cliente* cliente_indice(int id);
Cliente* cliente_buscar_nombre(char *busqueda);
Cliente* cliente_buscar_edad_rango(int min, int max);
Cliente* cliente_buscar_edad_mayor(int min);
Cliente* cliente_buscar_edad_menor(int max);

#endif //TPFINAL_CLIENTES_H
