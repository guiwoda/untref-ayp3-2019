#include "tests.h"

void test_cliente_nuevo(void **state) {
    (void) state;

    char *nombre = "Guido Contreras Woda";
    Fecha *nacimiento = una_fecha(1986, 7, 7);
    Cliente *guido = cliente_nuevo((unsigned char*) nombre, nacimiento);

    assert_int_equal(1, guido->id);
    assert_string_equal(nombre, guido->nombre);
    assert_int_equal(1986 - 1900, guido->nacimiento->tm_year);
    assert_int_equal(7 - 1, guido->nacimiento->tm_mon);
    assert_int_equal(7, guido->nacimiento->tm_mday);
}

void test_clientes_nuevos(void **state) {
    (void) state;

    Clientes *clientes = malloc(sizeof(Clientes));

    int max = 50;
    for (int i = 0; i < max; i++) {
        clientes->cliente = cliente_nuevo((unsigned char*) nombre_al_azar(), fecha_al_azar());
        clientes->next = malloc(sizeof(Clientes));
        clientes->next->prev = clientes;

        printf("Cliente: Nombre [%s], ID [%d]\n", clientes->cliente->nombre, clientes->cliente->id);
        clientes = clientes->next;
    }

    assert_int_equal(50, clientes->prev->cliente->id);
}

int teardown(void **state) {
    cliente_borrar_todo();
    return 0;
}

int main(void) {
    return cmocka_run_group_tests(clientes_tests, NULL, NULL);
}
