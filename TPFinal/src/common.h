#ifndef TPFINAL_COMMON_H
#define TPFINAL_COMMON_H
#define SQLITE_DEFAULT_FOREIGN_KEYS = 1

#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

typedef struct tm Fecha;
sqlite3 *db();
void ejecutarEnDbOFallar(sqlite3 *database, char *sql);
int last_insert_rowid();
Fecha *fecha_hoy();

#endif //TPFINAL_COMMON_H
