#ifndef TPFINAL_TESTS_H
#define TPFINAL_TESTS_H

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdio.h>
#include "clientes.h"
#include "test_utils.h"

/**
 * Prueba que se puede agregar un nuevo cliente al sistema.
 */
void test_cliente_nuevo(void **state);

/**
 * Prueba que se puede agregar múltiples clientes al sistema.
 */
void test_clientes_nuevos(void **state);

int teardown(void **state);

const struct CMUnitTest clientes_tests[] = {
        cmocka_unit_test_teardown(test_cliente_nuevo, teardown),
        cmocka_unit_test(test_clientes_nuevos),
};

#endif //TPFINAL_TESTS_H
