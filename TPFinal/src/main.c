#include "common.h"
#include "clientes.h"

static void menu();
static void pedirDatosCliente(char *nombre, Fecha *nacimiento);
static void mostrarCliente(Cliente *cliente);

static void buscarClientePorIdMenu();

static void buscarClientePorNombreMenu();

static void buscarClientePorEdadMenu();

static void buscarClientesMenu();

void fecha_a_texto(Fecha *fecha, char *res);

static void agregarReferidoMenu(Cliente *referente) {
    char *nombre = (char*) malloc(sizeof(char));
    Fecha *nacimiento = (Fecha*) malloc(sizeof(Fecha));

    pedirDatosCliente(nombre, nacimiento);
    
    Cliente *cliente = cliente_nuevo_con_referido(nombre, nacimiento, referente->id);
    
    mostrarCliente(cliente);
}

static void agregarClienteMenu() {
    char *nombre = (char*) malloc(sizeof(char));
    Fecha *nacimiento = (Fecha*) malloc(sizeof(Fecha));

    pedirDatosCliente(nombre, nacimiento);

    Cliente *cliente = cliente_nuevo(nombre, nacimiento);

    mostrarCliente(cliente);
}

static void buscarClienteMenu() {
    char opcion;

    do {
        printf("\nMENU"
               "\n1- Buscar por ID"
               "\n2- Buscar por nombre"
               "\n3- Buscar por edad"
               "\n4- Mostrar todos"
               "\n0- Volver"
               "\nIngrese una Opcion: ");

        while ((opcion = getchar()) != '\n' && opcion != EOF) {}

        switch(opcion) {
            case '1':
                buscarClientePorIdMenu();
                break;
            case '2':
                buscarClientePorNombreMenu();
                break;
            case '3':
                buscarClientePorEdadMenu();
                break;
            case '4':
                buscarClientesMenu();
                break;

            case '0':
            default:
                break;
        }

    } while (opcion != '0');
}

static void mostrarClienteTabla(Cliente *cliente) {
    char fecha[11];
    fecha_a_texto(cliente->nacimiento, fecha);
    printf("| %d | %s | %s |\n", cliente->id, cliente->nombre, fecha);
}

static void buscarClientesMenu() {
    Clientes *todos = clientes();

    if (todos != NULL) {
        printf("| ID | Nombre | Fecha de nacimiento |\n");
    }

    while (todos != NULL) {
        mostrarClienteTabla(todos->cliente);
        todos = todos->next;
    }
}

static void buscarClientePorEdadMenu() {

}

static void buscarClientePorNombreMenu() {

}

static void buscarClientePorIdMenu() {
    char *intmax = NULL;
    sprintf(intmax, "%d", INT_MAX);
    const size_t max_int_length = strlen(intmax);

    char *id = NULL;
    printf("Ingrese el ID...\n");
    fgets(id, max_int_length, stdin);

    Cliente *cliente = cliente_indice(atoi(id));

    if (cliente != NULL) {
        mostrarCliente(cliente);
    } else {
        printf("Cliente con ID [%s] no encontrado.", id);
    }
}

void menu() {
    char opcion;

    do {
        printf("\nMENU"
               "\n1- Agregar cliente"
               "\n2- Buscar clientes"
               "\n0- Salir"
               "\nIngrese una Opcion: ");

        while ((opcion = getchar()) != '\n' && opcion != EOF) {}

        switch(opcion) {
            case '1':
                agregarClienteMenu();
                break;
            case '2':
                buscarClienteMenu();
                break;
            case '0':
                salir();
                break;

            default:
                printf("Opcion Incorrecta.\n Por favor ingrese un numero del menu.\n");
        }

    } while (opcion != '0');
}

void pedirDatosCliente(char *nombre, Fecha *nacimiento) {
    printf("Ingrese el nombre...\n");
    fgets(nombre, 255, stdin);

    char *nacimientoUnparsed = (char *) malloc(sizeof(char));
    printf("Ingrese la fecha de nacimiento...\n");
    fgets(nacimientoUnparsed, 11, stdin);

    strptime(nacimientoUnparsed, "%d/%m/%Y", nacimiento);
}

void mostrarCliente(Cliente *cliente) {
    printf("Nombre: %s\n", cliente->nombre);

    char fecha[11];
    fecha_a_texto(cliente->nacimiento, fecha);

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

    Cliente *referente = NULL;
    if (cliente->referente_id != 0) {
        referente = cliente_indice(cliente->referente_id);
        printf("Referido por: %s\n", referente->nombre);
    }

    char opcion;
    do {
        const char *menuSinReferido = "\n1- Agregar referido\n0- Volver";

        const char *menuConReferido = "\n1- Agregar referido"
                                "\n2- Ir al referido"
                                "\n0- Volver";

        printf("%s", cliente->referente_id ? menuConReferido : menuSinReferido);

        while ((opcion = getchar()) != '\n' && opcion != EOF) {}

        switch(opcion) {
            case '1':
                agregarReferidoMenu(cliente);
                break;
            case '2':
                if (referente != NULL) {
                    mostrarCliente(referente);
                }
            case '0':
            default:
                break;
        }

    } while (opcion != '0');
}

void fecha_a_texto(Fecha *fecha, char *res) {
    strftime(res, 11, "%d/%m/%Y", fecha);
}

int main() {
    sqlite3 *database = db();
    menu();

    sqlite3_close(database);
    return 0;
}
