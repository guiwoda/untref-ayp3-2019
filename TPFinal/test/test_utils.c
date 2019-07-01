#include "test_utils.h"

Fecha* una_fecha(int year, int month, int day) {
    Fecha *nacimiento = (Fecha*) malloc(sizeof(Fecha));
    nacimiento->tm_year = year - 1900;
    nacimiento->tm_mon = month - 1;
    nacimiento->tm_mday = day;
    nacimiento->tm_hour = nacimiento->tm_min = nacimiento->tm_sec = 0;
    return nacimiento;
}

char* nombre_al_azar() {
    static char nombres[20][9] = {
            "Guido",
            "Esteban",
            "Gabriel",
            "Lucas",
            "Jose",
            "Martin",
            "Carlos",
            "Lucia",
            "Florencia",
            "Ana",
            "Maria",
            "Juana",
            "Romina",
            "Ramon",
            "Isidoro",
            "Leon",
            "Gustavo",
            "Alberto",
            "Miguel",
            "Nina"
    };

    static char apellidos[20][10] = {
            "Gomez",
            "Alvear",
            "Gutierrez",
            "Woda",
            "Benegas",
            "Souza",
            "Merlo",
            "Martinez",
            "Lopez",
            "Bullrich",
            "Smith",
            "Rincon",
            "Fernandez",
            "Russo",
            "Parker",
            "Simmons",
            "Justo",
            "Stark",
            "Lannister",
            "Bolson"
    };

    char *resultado = malloc(21 * sizeof(char));
    strcat(resultado, nombres[rand() % 20]);
    strcat(resultado, " ");
    strcat(resultado, apellidos[rand() % 20]);

    return resultado;
}

Fecha* fecha_al_azar() {
    return una_fecha(
            (rand() % 2000) + 1920,
            (rand() % 13) + 1,
            (rand() % 29) + 1);
}
