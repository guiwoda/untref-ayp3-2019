#ifndef TPFINAL_MAIN_H
#define TPFINAL_MAIN_H

#include "main.h"
#include "creditos.h"
#include "clientes.h"
#include "common.h"

void menu_agregar_referido(Cliente *referente);

void menu_agregar_cliente();

void menu_buscar_cliente();

void menu_buscar_clientes();

void menu_buscar_cliente_edad();

void menu_buscar_cliente_nombre();

void menu_buscar_cliente_id();

void menu();

void pedir_datos_cliente(const unsigned char *nombre, Fecha *nacimiento);

void mostrar_cliente(Cliente *cliente);

void mostrar_creditos(Creditos *creditos);

void menu_agregar_credito(Cliente *cliente);

void fecha_a_texto(Fecha *fecha, char *res);

void mostrar_cliente_tabla(Cliente *cliente);

#endif //TPFINAL_MAIN_H
