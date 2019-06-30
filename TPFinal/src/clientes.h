#ifndef TPFINAL_CLIENTES_H
#define TPFINAL_CLIENTES_H

#include <time.h>
#include <limits.h>

typedef struct _cliente {
    unsigned int id;
    char *nombre;
    time_t nacimiento;
    unsigned int referente_id;
} Cliente;

void cliente_referido(char *nombre, time_t nacimiento, int referente_id);

void cliente_nuevo(char *nombre, time_t nacimiento) {
    cliente_referido(nombre, nacimiento, 0);
}

Cliente* cliente_indice(int id);
Cliente* cliente_buscar_nombre(char *busqueda);
Cliente* cliente_buscar_edad_rango(int min, int max);
Cliente* cliente_buscar_edad_mayor(int min) {
    return cliente_buscar_edad_rango(min, INT_MAX);
}
Cliente* cliente_buscar_edad_menor(int max) {
    return cliente_buscar_edad_rango(0, max);
}

#endif //TPFINAL_CLIENTES_H
