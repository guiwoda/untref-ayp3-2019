#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"

int main(){

   int longitud;

   printf("Ingrese la cantidad de empleados: \n");

   scanf("%d", &longitud);

   Empleado listaEmpleado[longitud];

   inicializarVector(listaEmpleado, longitud);

   menu(listaEmpleado, longitud);

   return 0;
}