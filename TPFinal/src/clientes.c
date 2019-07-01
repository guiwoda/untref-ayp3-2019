#include "clientes.h"

static unsigned int CLIENTES_LAST_ID = 0;
unsigned int cliente_proximo_id() {
    return ++CLIENTES_LAST_ID;
}

Cliente* cliente_nuevo_con_referido(char *nombre, time_t nacimiento, int referente_id) {
    Cliente *cliente = (Cliente*) malloc(sizeof(Cliente));
    cliente->id = cliente_proximo_id();
    cliente->nombre = nombre;
    cliente->nacimiento = nacimiento;
    cliente->referente_id = referente_id;

    return cliente;
}

Cliente* cliente_nuevo(char *nombre, time_t nacimiento) {
    return cliente_nuevo_con_referido(nombre, nacimiento, 0);
}

Cliente* cliente_indice(int id) {
    return NULL;
}

Clientes* cliente_buscar_nombre(char *busqueda) {
    return NULL;
}

Clientes* cliente_buscar_edad_rango(int min, int max) {
    return NULL;
}
