#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

void test_clientes_nuevo(void **state) {
    (void) state;
}

const struct CMUnitTest clientes_tests[] = {
        cmocka_unit_test(test_clientes_nuevo),
};

int main(void) {
    return cmocka_run_group_tests(clientes_tests, NULL, NULL);
}
