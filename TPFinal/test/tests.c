#include "tests.h"

void test_cliente_nuevo(void **state) {
    (void) state;

    struct tm nacimiento;
    nacimiento.tm_year = 1986 - 1900;
    nacimiento.tm_mon = 7 - 1;
    nacimiento.tm_mday = 7;
    nacimiento.tm_hour = nacimiento.tm_min = nacimiento.tm_sec = 0;

    char *nombre = "Guido Contreras Woda";
    Cliente *guido = cliente_nuevo(nombre, mktime(&nacimiento));

    assert_int_equal(1, guido->id);
    assert_string_equal(nombre, guido->nombre);
    assert_int_equal(1986 - 1900, gmtime(&guido->nacimiento)->tm_year);
    assert_int_equal(7 - 1, gmtime(&guido->nacimiento)->tm_mon);
    assert_int_equal(7, gmtime(&guido->nacimiento)->tm_mday);
}

int main(void) {
    return cmocka_run_group_tests(clientes_tests, NULL, NULL);
}
