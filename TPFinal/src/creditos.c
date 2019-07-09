#include "creditos.h"

static void stmt_a_credito(Credito *credito, sqlite3_stmt *stmt) {
    credito->id = sqlite3_column_int(stmt, 0);
    credito->cliente_id = sqlite3_column_int(stmt, 1);
    credito->monto = sqlite3_column_int(stmt, 2);
    time_t fecha = (time_t) sqlite3_column_int(stmt, 3);
    credito->pedido = gmtime(&fecha);
}

static void stmt_a_creditos(Creditos **creditos, Creditos *prev, sqlite3_stmt *stmt) {
    *creditos = (Creditos*) malloc(sizeof(Creditos));
    (*creditos)->prev = prev;
    (*creditos)->credito = (Credito*) malloc(sizeof(Credito));
    (*creditos)->next = NULL;
    stmt_a_credito((*creditos)->credito, stmt);

    int next = sqlite3_step(stmt);
    if (next == SQLITE_ROW) {
        stmt_a_creditos(&(*creditos)->next, *creditos, stmt);
    }
}

void stmt_a_pago(Pago *pago, sqlite3_stmt *stmt) {
    pago->id = sqlite3_column_int(stmt, 0);
    pago->credito_id = sqlite3_column_int(stmt, 1);
    pago->monto = sqlite3_column_int(stmt, 2);
    time_t fecha = (time_t) sqlite3_column_int(stmt, 3);
    pago->fecha_pago = gmtime(&fecha);
}

void stmt_a_pagos(Pagos **pagos, Pagos *prev, sqlite3_stmt *stmt) {
    *pagos = (Pagos*) malloc(sizeof(Pagos));
    (*pagos)->prev = prev;
    (*pagos)->pago = (Pago*) malloc(sizeof(Pago));
    (*pagos)->next = NULL;
    stmt_a_pago((*pagos)->pago, stmt);

    int next = sqlite3_step(stmt);
    if (next == SQLITE_ROW) {
        stmt_a_pagos(&(*pagos)->next, *pagos, stmt);
    }
}

static void select_creditos_by_cliente(Cliente *cliente, Creditos **creditos) {
    const char *select_all_query = "SELECT id, cliente_id, monto, pedido FROM creditos WHERE cliente_id = ?;";
    const size_t select_all_query_length = strlen(select_all_query) + 1;

    sqlite3_stmt *select_all_stmt = NULL;
    sqlite3_prepare_v2(db(), select_all_query, select_all_query_length, &select_all_stmt, NULL);

    sqlite3_bind_int(select_all_stmt, 1, cliente->id);

    int row = sqlite3_step(select_all_stmt);
    if (row == SQLITE_ROW) {
        stmt_a_creditos(creditos, NULL, select_all_stmt);
    }
}

void select_pagos_by_credito(Credito *credito, Pagos **pagos) {
    const char *select_all_query = "SELECT id, credito_id, monto, fecha_pago FROM pagos WHERE credito_id = ?;";
    const size_t select_all_query_length = strlen(select_all_query) + 1;

    sqlite3_stmt *select_all_stmt = NULL;
    sqlite3_prepare_v2(db(), select_all_query, select_all_query_length, &select_all_stmt, NULL);

    sqlite3_bind_int(select_all_stmt, 1, credito->id);

    int row = sqlite3_step(select_all_stmt);
    if (row == SQLITE_ROW) {
        stmt_a_pagos(pagos, NULL, select_all_stmt);
    }
}

static void insert_credito(Credito *credito) {
    const char *insert_query = "INSERT INTO creditos(cliente_id, monto, pedido) VALUES(?, ?, ?);";
    const size_t insert_query_length = strlen(insert_query) + 1;

    sqlite3_stmt *insert_stmt = NULL;
    sqlite3_prepare_v2(db(), insert_query, insert_query_length, &insert_stmt, NULL);

    sqlite3_bind_int(insert_stmt, 1, credito->cliente_id);
    sqlite3_bind_int(insert_stmt, 2, credito->monto);
    sqlite3_bind_int64(insert_stmt, 3, timegm(credito->pedido));

    sqlite3_step(insert_stmt);
    credito->id = last_insert_rowid();
}

void insert_pago(Pago *pago) {
    const char *insert_query = "INSERT INTO pagos(credito_id, monto, fecha_pago) VALUES(?, ?, ?);";
    const size_t insert_query_length = strlen(insert_query) + 1;

    sqlite3_stmt *insert_stmt = NULL;
    sqlite3_prepare_v2(db(), insert_query, insert_query_length, &insert_stmt, NULL);

    sqlite3_bind_int(insert_stmt, 1, pago->credito_id);
    sqlite3_bind_int(insert_stmt, 2, pago->monto);
    sqlite3_bind_int64(insert_stmt, 3, timegm(pago->fecha_pago));

    sqlite3_step(insert_stmt);
    pago->id = last_insert_rowid();
}

Credito *credito_nuevo(Cliente *cliente, int monto, Fecha *pedido) {
    Credito *credito = (Credito *) malloc(sizeof(Credito));

    credito->cliente_id = cliente->id;
    credito->monto = monto;
    credito->pedido = pedido;

    insert_credito(credito);

    return credito;
}

Pago *pago_nuevo(Credito *credito, int monto, Fecha *fecha_pago) {
    Pago *pago = (Pago *) malloc(sizeof(Pago));

    pago->credito_id = credito->id;
    pago->monto = monto;
    pago->fecha_pago = fecha_pago;

    insert_pago(pago);

    return pago;
}

Creditos *credito_por_cliente(Cliente *cliente) {
    Creditos *creditos = NULL;
    select_creditos_by_cliente(cliente, &creditos);

    return creditos;
}

Pagos *pago_por_credito(Credito *credito) {
    Pagos *pagos = NULL;

    select_pagos_by_credito(credito, &pagos);

    return pagos;
}
