#ifndef TPFINAL_COMMON_H
#define TPFINAL_COMMON_H

#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

typedef struct tm Fecha;
sqlite3 *db();
void ejecutarEnDbOFallar(sqlite3 *database, char *sql);
void salir();
int last_insert_rowid();

#endif //TPFINAL_COMMON_H
