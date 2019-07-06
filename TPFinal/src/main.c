#include "common.h"
#include "clientes.h"
#include "creditos.h"

static void menu();
static void pedirDatosCliente(char *nombre, Fecha *nacimiento);
static void mostrarCliente(Cliente *cliente);
static void buscarClientePorIdMenu();
static void buscarClientePorNombreMenu();
static void buscarClientePorEdadMenu();
static void buscarClientesMenu();
static void fecha_a_texto(Fecha *fecha, char *res);

void agregarCreditoMenu(Cliente *cliente);

Fecha *fecha_hoy();

void mostrarCreditos(Creditos *creditos);

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

        scanf("%s", &opcion);

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
    int id;
    printf("Ingrese el ID...\n");
    scanf("%d", &id);

    Cliente *cliente = cliente_indice(id);

    if (cliente != NULL) {
        mostrarCliente(cliente);
    } else {
        printf("Cliente con ID [%d] no encontrado.", id);
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

        scanf("%s", &opcion);

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
    scanf("%s", nombre);

    char *nacimientoUnparsed = (char *) malloc(sizeof(char));
    printf("Ingrese la fecha de nacimiento...\n");
    scanf("%s", nacimientoUnparsed);

    strptime(nacimientoUnparsed, "%d/%m/%Y", nacimiento);
}

void mostrarCliente(Cliente *cliente) {
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
    mostrarCreditos(creditos);

    char opcion;
    do {
        printf("\n1- Agregar referido");

        if (cliente->referente_id != 0) {
            printf("\n2- Ir al referido");
        }

        printf("\n0- Volver");

        scanf("%s", &opcion);

        switch(opcion) {
            case '1':
                agregarReferidoMenu(cliente);
                break;
            case '2':
                if (referente != NULL) {
                    mostrarCliente(referente);
                }
                break;
            case '3':
                agregarCreditoMenu(cliente);
                break;
            case '0':
            default:
                break;
        }

    } while (opcion != '0');
}

void mostrarCreditos(Creditos *creditos) {
    if (creditos == NULL) {
        return;
    }

    char fecha[11];
    fecha_a_texto(creditos->credito->pedido, fecha);

    printf("Credito por $%d tomado el dia %s\n", creditos->credito->monto, fecha);
    mostrarCreditos(creditos->next);
}

Fecha *fecha_hoy() {
    time_t today = time(NULL);
    Fecha *todayTm = localtime(&today);
    return todayTm;
}

void agregarCreditoMenu(Cliente *cliente) {
    int monto = 0;
    printf("Ingrese el monto...\n");
    scanf("%d", &monto);

    // TODO: Validar monto
    credito_nuevo(cliente, monto, fecha_hoy());

    mostrarCliente(cliente);
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
