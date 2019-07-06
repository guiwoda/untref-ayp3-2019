#ifndef TPFINAL_COMMON_H
#define TPFINAL_COMMON_H

#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

typedef struct tm Fecha;
sqlite3 *db();
void ejecutarEnDbOFallar(sqlite3 *database, char *sql);
void salir();

#endif //TPFINAL_COMMON_H
