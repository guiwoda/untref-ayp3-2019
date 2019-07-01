#include "clientes.h"

static unsigned int CLIENTES_LAST_ID = 0;

/**
 * @return el próximo ID a usar para un cliente.
 */
static unsigned int cliente_proximo_id() {
    return ++CLIENTES_LAST_ID;
}

Cliente* cliente_nuevo_con_referido(char *nombre, Fecha *nacimiento, int referente_id) {
    Cliente *cliente = (Cliente*) malloc(sizeof(Cliente));
    cliente->id = cliente_proximo_id();
    cliente->nombre = nombre;
    cliente->nacimiento = nacimiento;
    cliente->referente_id = referente_id;

    return cliente;
}

Cliente* cliente_nuevo(char *nombre, Fecha *nacimiento) {
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

void cliente_borrar_todo() {
    // Borrar persistentes...

    CLIENTES_LAST_ID = 0;
}
