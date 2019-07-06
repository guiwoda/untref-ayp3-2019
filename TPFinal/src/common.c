#include "common.h"

int last_insert_rowid() {
    const char *last_id_query = "SELECT last_insert_rowid();";
    const size_t last_id_query_length = strlen(last_id_query) + 1;

    static sqlite3_stmt *last_id_stmt = NULL;
    if (last_id_stmt == NULL) {
        sqlite3_prepare_v2(db(), last_id_query, last_id_query_length, &last_id_stmt, NULL);
    } else {
        sqlite3_reset(last_id_stmt);
    }
    sqlite3_step(last_id_stmt);
    return sqlite3_column_int(last_id_stmt, 0);
}

void ejecutarEnDbOFallar(sqlite3 *database, char *sql) {
    char *error = NULL;
    int res = sqlite3_exec(database, sql, 0, 0, &error);

    if (res != SQLITE_OK) {
        printf("Error en [%s]: %s\n", sql, error);
        salir();
    }
}

sqlite3 *db() {
    static sqlite3 *database;

    static int db_init = 0;
    if (db_init == 0) {
        int status = sqlite3_open("./sqlite.db", &database);
        if (status != SQLITE_OK) {
            printf("Error [%d] abriendo archivo de base de datos. \n", status);
            salir();
        }

//        ejecutarEnDbOFallar(database, "PRAGMA foreign_keys ON;");
        ejecutarEnDbOFallar(database,
                "CREATE TABLE IF NOT EXISTS clientes("
                "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                "nombre CHARACTER VARYING NOT NULL, "
                "nacimiento INTEGER NOT NULL,"
                "referente_id INTEGER);");
//                "-- FOREIGN KEY(referente_id) REFERENCES clientes(id));");

        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS clientes_nombre ON clientes(nombre);");
        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS clientes_nacimiento ON clientes(nacimiento);");
        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS clientes_referente ON clientes(referente_id);");

        ejecutarEnDbOFallar(database, "CREATE TABLE IF NOT EXISTS creditos("
                            "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                            "cliente_id INTEGER NOT NULL, "
                            "monto INTEGER NOT NULL, "
                            "pedido INTEGER NOT NULL);");
//                            "FOREIGN KEY(cliente_id) REFERENCES clientes(id))");

        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS creditos_cliente_id ON creditos(cliente_id);");

        ejecutarEnDbOFallar(database, "CREATE TABLE IF NOT EXISTS pagos("
                            "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                            "credito_id INTEGER NOT NULL,"
                            "monto INTEGER NOT NULL,"
                            "pago INTEGER NOT NULL);");
//                            "FOREIGN KEY(credito_id) REFERENCES creditos(id));");

        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS pagos_credito_id ON pagos(credito_id);");
        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS pagos_pago ON pagos(pago);");

        db_init = 1;
    }

    return database;
}

void salir() {
    printf("Cerrando...\n");
    system("exit");
}
