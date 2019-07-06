#include "clientes.h"

void stmt_a_cliente(Cliente *cliente, sqlite3_stmt *stmt);
void stmt_a_clientes(Clientes **clientes, Clientes *prev, sqlite3_stmt *stmt);

static int last_insert_rowid() {
    const char *last_id_query = "SELECT last_insert_rowid();";
    const size_t last_id_query_length = strlen(last_id_query) + 1;

    static sqlite3_stmt *last_id_stmt = NULL;
    if (last_id_stmt == NULL) {
        sqlite3_prepare_v2(db(), last_id_query, last_id_query_length, &last_id_stmt, NULL);
    } else {
        sqlite3_reset(last_id_stmt);
    }
    int result = sqlite3_step(last_id_stmt);
    printf("\n -- SQLite debug: %s, Result: %d\n", last_id_query, result);

    return sqlite3_column_int(last_id_stmt, 0);
}

static void insert_into_clientes(Cliente *cliente) {
    const char *insert_query = "INSERT INTO clientes(nombre, nacimiento, referente_id) VALUES(?, ?, ?);";
    const size_t insert_query_length = strlen(insert_query) + 1;

    sqlite3_stmt *insert_stmt = NULL;
    sqlite3_prepare_v2(db(), insert_query, insert_query_length, &insert_stmt, NULL);

    sqlite3_bind_text(insert_stmt, 1, cliente->nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int64(insert_stmt, 2, timegm(cliente->nacimiento));
    sqlite3_bind_int(insert_stmt, 3, cliente->referente_id);

    int result = sqlite3_step(insert_stmt);
    printf("\n -- SQLite debug: %s, Result: %d\n", insert_query, result);

    cliente->id = last_insert_rowid();
}

static void select_clientes(Clientes **clientes) {
    const char *select_all_query = "SELECT id, nombre, nacimiento, referente_id FROM clientes;";
    const size_t select_all_query_length = strlen(select_all_query) + 1;

    sqlite3_stmt *select_all_stmt = NULL;
    sqlite3_prepare_v2(db(), select_all_query, select_all_query_length, &select_all_stmt, NULL);

    int row = sqlite3_step(select_all_stmt);
    printf("\n -- SQLite debug: %s, Result: %d\n", select_all_query, row);

    if (row == SQLITE_ROW) {
        stmt_a_clientes(clientes, NULL, select_all_stmt);
    }
}

static void select_cliente_by_id(int id, Cliente **cliente) {
    const char *select_by_id_query = "SELECT id, nombre, nacimiento, referente_id FROM clientes WHERE id = ? LIMIT 1;";
    const size_t select_by_id_query_length = strlen(select_by_id_query) + 1;

    sqlite3_stmt * select_by_id_stmt = NULL;
    sqlite3_prepare_v2(db(), select_by_id_query, select_by_id_query_length, &select_by_id_stmt, NULL);

    sqlite3_bind_int(select_by_id_stmt, 1, id);
    int row = sqlite3_step(select_by_id_stmt);

    printf("\n -- SQLite debug: %s, Result: %d\n", select_by_id_query, row);

    if (row == SQLITE_ROW) {
        *cliente = (Cliente *) malloc(sizeof(Cliente));
        stmt_a_cliente(*cliente, select_by_id_stmt);
    }
}

void stmt_a_cliente(Cliente *cliente, sqlite3_stmt *stmt) {
    cliente->id = sqlite3_column_int(stmt, 0);
    cliente->nombre = (char *) sqlite3_column_text(stmt, 1);
    time_t nac = (time_t) sqlite3_column_int64(stmt, 2);
    cliente->nacimiento = (Fecha *) gmtime(&nac);
    cliente->referente_id = sqlite3_column_int(stmt, 3);
}

void stmt_a_clientes(Clientes **clientes, Clientes *prev, sqlite3_stmt *stmt) {
    *clientes = (Clientes*) malloc(sizeof(Clientes));
    (*clientes)->prev = prev;
    (*clientes)->cliente = (Cliente*) malloc(sizeof(Cliente));
    stmt_a_cliente((*clientes)->cliente, stmt);

    int next = sqlite3_step(stmt);
    if (next == SQLITE_ROW) {
        stmt_a_clientes(&(*clientes)->next, *clientes, stmt);
    }
}

Cliente* cliente_nuevo_con_referido(char *nombre, Fecha *nacimiento, int referente_id) {
    Cliente *cliente = (Cliente*) malloc(sizeof(Cliente));
    cliente->nombre = nombre;
    cliente->nacimiento = nacimiento;
    cliente->referente_id = referente_id;

    insert_into_clientes(cliente);
    return cliente;
}

Cliente* cliente_nuevo(char *nombre, Fecha *nacimiento) {
    return cliente_nuevo_con_referido(nombre, nacimiento, 0);
}

Cliente* cliente_indice(int id) {
    Cliente *cliente = NULL;
    select_cliente_by_id(id, &cliente);

    return cliente;
}

Clientes* clientes() {
    Clientes *clientes = NULL;
    select_clientes(&clientes);

    return clientes;
}

Clientes* cliente_buscar_nombre(char *busqueda) {
    return NULL;
}

Clientes* cliente_buscar_edad_rango(int min, int max) {
    return NULL;
}

void cliente_borrar_todo() {
}
