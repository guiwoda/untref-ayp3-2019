#ifndef TPFINAL_TESTS_H
#define TPFINAL_TESTS_H

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "clientes.h"

void test_cliente_nuevo(void **state);

const struct CMUnitTest clientes_tests[] = {
    cmocka_unit_test(test_cliente_nuevo),
};

#endif //TPFINAL_TESTS_H
