#include "main.h"

void menu_agregar_referido(Cliente *referente) {
    unsigned char *nombre = malloc(sizeof(unsigned char));
    Fecha *nacimiento = malloc(sizeof(Fecha));

    pedir_datos_cliente(nombre, nacimiento);

    Cliente *cliente = cliente_nuevo_con_referido(nombre, nacimiento, referente->id);
    free(nombre);
    free(nacimiento);

    mostrar_cliente(cliente);

}

void menu_agregar_cliente() {
    unsigned char *nombre = malloc(sizeof(unsigned char));
    Fecha *nacimiento = malloc(sizeof(Fecha));

    pedir_datos_cliente(nombre, nacimiento);

    Cliente *cliente = cliente_nuevo(nombre, nacimiento);
    free(nombre);
    free(nacimiento);

    mostrar_cliente(cliente);
}

void menu_buscar_cliente() {
    char opcion;

    do {
        printf("\nMENU"
               "\n1- Buscar por ID"
               "\n2- Buscar por nombre"
               "\n3- Buscar por edad"
               "\n4- Mostrar todos"
               "\n0- Volver"
               "\nIngrese una Opcion: ");

        scanf("%s", &opcion);

        switch(opcion) {
            case '1':
                menu_buscar_cliente_id();
                break;
            case '2':
                menu_buscar_cliente_nombre();
                break;
            case '3':
                menu_buscar_cliente_edad();
                break;
            case '4':
                menu_buscar_clientes();
                break;

            case '0':
            default:
                break;
        }

    } while (opcion != '0');
}

void menu_buscar_clientes() {
    Clientes *todos = clientes();

    if (todos != NULL) {
        printf("| ID | Nombre | Fecha de nacimiento |\n");
    }

    mostrar_cliente_tabla(todos);
}

void menu_buscar_cliente_edad() {
    int min, max;

    printf("Edad minima...\n");
    scanf("%d", &min);

    printf("Edad maxima...\n");
    scanf("%d", &max);

    Clientes *todos = cliente_buscar_edad_rango(min, max);

    if (todos != NULL) {
        printf("| ID | Nombre | Fecha de nacimiento |\n");
    }

    mostrar_cliente_tabla(todos);
}

void menu_buscar_cliente_nombre() {
    char busqueda[255];
    printf("Ingresar busqueda...\n");
    scanf("%s", busqueda);

    Clientes *todos = cliente_buscar_nombre(busqueda);

    if (todos != NULL) {
        printf("| ID | Nombre | Fecha de nacimiento |\n");
    }

    mostrar_cliente_tabla(todos);
}

void menu_buscar_cliente_id() {
    int id;
    printf("Ingrese el ID...\n");
    scanf("%d", &id);

    Cliente *cliente = cliente_indice(id);

    if (cliente != NULL) {
        mostrar_cliente(cliente);
    } else {
        printf("Cliente con ID [%d] no encontrado.", id);
    }
}

void pedir_datos_cliente(const unsigned char *nombre, Fecha *nacimiento) {
    printf("Ingrese el nombre...\n");
    scanf("%s", (char*) nombre);

    char nacimientoUnparsed[11];
    printf("Ingrese la fecha de nacimiento...\n");
    scanf("%s", nacimientoUnparsed);

    strptime(nacimientoUnparsed, "%d/%m/%Y", nacimiento);
}

void mostrar_cliente(Cliente *cliente) {
    printf("Nombre: %s\n", cliente->nombre);

    char fecha[11];
    fecha_a_texto(cliente->nacimiento, fecha);

    Fecha *hoy = fecha_hoy();
    int edad = hoy->tm_year - cliente->nacimiento->tm_year;
    if (
            hoy->tm_mon < cliente->nacimiento->tm_mon || (
                    hoy->tm_mon == cliente->nacimiento->tm_mon &&
                    hoy->tm_mday < cliente->nacimiento->tm_mday)) {
        edad--;
    }

    printf("Fecha de nacimiento: %s (edad: %d)\n", fecha, edad);

    Cliente *referente = NULL;
    if (cliente->referente_id != 0) {
        referente = cliente_indice(cliente->referente_id);
        printf("Referido por: %s\n", referente->nombre);
    }

    Creditos *creditos = credito_por_cliente(cliente);
    mostrar_creditos(creditos);

    char opcion;
    do {
        printf("\n1- Agregar referido");

        if (cliente->referente_id != 0) {
            printf("\n2- Ir al referido");
        }

        printf("\n3- Agregar credito");
        printf("\n0- Volver");

        scanf("%s", &opcion);

        switch(opcion) {
            case '1':
                menu_agregar_referido(cliente);
                break;
            case '2':
                if (referente != NULL) {
                    mostrar_cliente(referente);
                }
                break;
            case '3':
                menu_agregar_credito(cliente);
                break;
            case '0':
            default:
                break;
        }

    } while (opcion != '0');
}

void mostrar_creditos(Creditos *creditos) {
    if (creditos == NULL) {
        return;
    }

    char fecha[11];
    fecha_a_texto(creditos->credito->pedido, fecha);

    printf("Credito por $%d tomado el dia %s\n", creditos->credito->monto, fecha);
    mostrar_creditos(creditos->next);
}

void menu_agregar_credito(Cliente *cliente) {
    int monto = 0;
    printf("Ingrese el monto...\n");
    scanf("%d", &monto);

    // TODO: Validar monto
    credito_nuevo(cliente, monto, fecha_hoy());

    mostrar_cliente(cliente);
}

void fecha_a_texto(Fecha *fecha, char *res) {
    strftime(res, 11, "%d/%m/%Y", fecha);
}

void mostrar_cliente_tabla(Clientes *clientes) {
    if (clientes == NULL) {
        return;
    }

    char fecha[11];
    fecha_a_texto(clientes->cliente->nacimiento, fecha);
    printf("| %d | %s | %s |\n", clientes->cliente->id, clientes->cliente->nombre, fecha);
    mostrar_cliente_tabla(clientes->next);
}

void menu() {
    char opcion;

    do {
        printf("\nMENU"
               "\n1- Agregar cliente"
               "\n2- Buscar clientes"
               "\n0- Salir"
               "\nIngrese una Opcion: ");

        scanf("%s", &opcion);

        switch(opcion) {
            case '1':
                menu_agregar_cliente();
                break;
            case '2':
                menu_buscar_cliente();
                break;
            case '0':
                printf("\nCerrando...\n\n");
                break;

            default:
                printf("\nOpcion Incorrecta.\n Por favor ingrese un numero del menu.\n");
        }

    } while (opcion != '0');
}

int main() {
    sqlite3 *database = db();
    menu();

    sqlite3_close(database);
    return 0;
}
