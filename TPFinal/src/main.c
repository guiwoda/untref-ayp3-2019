#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "clientes.h"

static void menu();

void salir() {
    printf("Cerrando...\n");
    system("exit");
}

static void agregarReferidoMenu() {

}

static void mostrarCliente(Cliente *cliente) {
    printf("Nombre: %s\n", cliente->nombre);

    char fecha[10];
    strftime(fecha, 10, "%d/%m/%Y", cliente->nacimiento);

    time_t today = time(NULL);
    Fecha *todayTm = localtime(&today);
    int edad = todayTm->tm_year - cliente->nacimiento->tm_year;
    if (
            todayTm->tm_mon < cliente->nacimiento->tm_mon || (
                    todayTm->tm_mon == cliente->nacimiento->tm_mon &&
                    todayTm->tm_mday < cliente->nacimiento->tm_mday)) {
        edad--;
    }

    printf("Fecha de nacimiento: %s (edad: %d)\n", fecha, edad);

    int opciones;

    do {
        printf("\n1- Agregar referido"
               "\n0- Volver");

        scanf("%d", &opciones);

        switch(opciones) {
            case 1:
                agregarReferidoMenu();
                break;
            case 0:
            default:
                break;
        }

    } while (opciones != 0);
}

static void agregarClienteMenu() {
    char *nombre = (char*) malloc(sizeof(char));
    printf("Ingrese el nombre...\n");
    scanf("%s", nombre);

    char *nacimientoUnparsed = (char*) malloc(sizeof(char));
    printf("Ingrese la fecha de nacimiento...\n");
    scanf("%s", nacimientoUnparsed);

    Fecha *nacimiento = (Fecha*) malloc(sizeof(Fecha));
    strptime(nacimientoUnparsed, "%d/%m/%Y", nacimiento);

    Cliente *cliente = cliente_nuevo(nombre, nacimiento);

    mostrarCliente(cliente);
}

static void buscarClienteMenu() {

}

void menu() {
    int opciones;

    do {
        printf("\nMENU"
               "\n1- Agregar cliente"
               "\n2- Buscar clientes"
               "\n0- Salir"
               "\nIngrese una Opcion: ");

        scanf("%d", &opciones);

        switch(opciones) {
            case 1:
                agregarClienteMenu();
                break;
            case 2:
                buscarClienteMenu();
                break;
            case 0:
                salir();
                break;

            default:
                printf("Opcion Incorrecta.\n Por favor ingrese un numero del menu.\n");
        }

    } while (opciones != 0);
}

int main() {
    menu();

    return 0;
}
