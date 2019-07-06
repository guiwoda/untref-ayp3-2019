#ifndef TPFINAL_CREDITOS_H
#define TPFINAL_CREDITOS_H

#include "common.h"
#include "clientes.h"

typedef struct {
    unsigned int id;
    unsigned int cliente_id;
    unsigned int monto;
    Fecha *pedido;
} Credito;

typedef struct _creditos Creditos;

struct _creditos {
    Creditos *prev;
    Credito *credito;
    Creditos *next;
};

typedef struct {
    unsigned int id;
    unsigned int credito_id;
    unsigned int monto;
    Fecha *pago;
} Pago;

typedef struct _pagos Pagos;

struct _pagos {
    Pagos *prev;
    Pago *pago;
    Pagos *next;
};


Credito *credito_nuevo(Cliente *cliente, int monto, Fecha *pedido);
Pago *pago_nuevo(Credito *credito, int monto, Fecha *pago);
Creditos *credito_por_cliente(Cliente *cliente);

#endif //TPFINAL_CREDITOS_H
