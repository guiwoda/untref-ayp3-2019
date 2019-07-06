#include "common.h"

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
                "nacimiento TIMESTAMP WITHOUT TIME ZONE,"
                "referente_id INTEGER);");
//                "-- FOREIGN KEY(referente_id) REFERENCES clientes(id));");

        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS clientes_nombre ON clientes(nombre);");
        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS clientes_nacimiento ON clientes(nacimiento);");
        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS clientes_referente ON clientes(referente_id);");

        ejecutarEnDbOFallar(database, "CREATE TABLE IF NOT EXISTS creditos("
                            "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                            "cliente_id INTEGER NOT NULL, "
                            "monto INTEGER NOT NULL, "
                            "fecha_pedido TIMESTAMP WITHOUT TIME ZONE);");
//                            "FOREIGN KEY(cliente_id) REFERENCES clientes(id))");

        ejecutarEnDbOFallar(database, "CREATE TABLE IF NOT EXISTS pagos("
                            "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                            "credito_id INTEGER NOT NULL,"
                            "pago INTEGER,"
                            "fecha TIMESTAMP WITHOUT TIME ZONE);");
//                            "FOREIGN KEY(credito_id) REFERENCES creditos(id));");
        ejecutarEnDbOFallar(database, "CREATE INDEX IF NOT EXISTS pagos_pago ON pagos(pago);");

        db_init = 1;
    }

    return database;
}

void salir() {
    printf("Cerrando...\n");
    system("exit");
}
