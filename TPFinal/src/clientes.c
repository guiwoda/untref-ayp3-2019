#include "clientes.h"

void stmt_a_cliente(Cliente *cliente, sqlite3_stmt *stmt) {
    cliente->id = sqlite3_column_int(stmt, 0);
    cliente->nombre = (unsigned char*) sqlite3_column_text(stmt, 1);
    time_t nac = (time_t) sqlite3_column_int(stmt, 2);
    cliente->nacimiento = (Fecha *) gmtime(&nac);
    cliente->referente_id = sqlite3_column_int(stmt, 3);
}

static void insert_into_clientes(Cliente *cliente) {
    const char *insert_query = "INSERT INTO clientes(nombre, nacimiento, referente_id) VALUES(?, ?, ?);";
    const size_t insert_query_length = strlen(insert_query) + 1;

    sqlite3_stmt *insert_stmt = NULL;
    sqlite3_prepare_v2(db(), insert_query, insert_query_length, &insert_stmt, NULL);

    sqlite3_bind_text(insert_stmt, 1, (char*) cliente->nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int64(insert_stmt, 2, timegm(cliente->nacimiento));
    sqlite3_bind_int(insert_stmt, 3, cliente->referente_id);

    sqlite3_step(insert_stmt);
    cliente->id = last_insert_rowid();
}

static void select_clientes(Cliente *cliente, void (*callback)(Cliente *)) {
    const char *select_all_query = "SELECT id, nombre, nacimiento, referente_id FROM clientes;";
    const size_t select_all_query_length = strlen(select_all_query) + 1;

    sqlite3_stmt *select_all_stmt = NULL;
    sqlite3_prepare_v2(db(), select_all_query, select_all_query_length, &select_all_stmt, NULL);

    int row = sqlite3_step(select_all_stmt);
    while (row == SQLITE_ROW) {
        stmt_a_cliente(cliente, select_all_stmt);
        callback(cliente);

        row = sqlite3_step(select_all_stmt);
    }
}

static void select_cliente_by_id(int id, Cliente **cliente) {
    const char *select_by_id_query = "SELECT id, nombre, nacimiento, referente_id FROM clientes WHERE id = ? LIMIT 1;";
    const size_t select_by_id_query_length = strlen(select_by_id_query) + 1;

    sqlite3_stmt * select_by_id_stmt = NULL;
    sqlite3_prepare_v2(db(), select_by_id_query, select_by_id_query_length, &select_by_id_stmt, NULL);

    sqlite3_bind_int(select_by_id_stmt, 1, id);
    int row = sqlite3_step(select_by_id_stmt);

    if (row == SQLITE_ROW) {
        *cliente = malloc(sizeof(Cliente));
        stmt_a_cliente(*cliente, select_by_id_stmt);
    }
}

void cliente_nuevo_con_referido(unsigned char *nombre, Fecha *nacimiento, int referente_id, void (*callback)(Cliente*)) {
    Cliente *cliente = malloc(sizeof(Cliente));
    cliente->nombre = nombre;
    cliente->nacimiento = nacimiento;
    cliente->referente_id = referente_id;

    insert_into_clientes(cliente);
    callback(cliente);

    free(cliente);
}

void cliente_nuevo(unsigned char *nombre, Fecha *nacimiento, void (*callback)(Cliente*)) {
    cliente_nuevo_con_referido(nombre, nacimiento, 0, callback);
}

void cliente_indice(int id, void (*callback)(Cliente*)) {
    Cliente *cliente = NULL;
    select_cliente_by_id(id, &cliente);
    callback(cliente);

    if (cliente != NULL) {
        free(cliente);
    }
}

void clientes(void (*callback)(Cliente*)) {
    Cliente *cliente = malloc(sizeof(Cliente));
    select_clientes(cliente, callback);
    free(cliente);
}

void cliente_buscar_nombre(char *busqueda, void (*callback)(Cliente*)) {
    return;
}

void cliente_buscar_edad_rango(int min, int max, void (*callback)(Cliente*)) {
    return;
}

void cliente_borrar_todo() {
}
