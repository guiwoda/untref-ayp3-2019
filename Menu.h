#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

    char nombre[100];

    char apellido[100];

    int edad;

    int legajo;

    unsigned int dni;

}Empleado;

void inicializarVector(Empleado vector[], int longitud){

   for(int i = 0; i<longitud; i++)
   {
      vector[i].edad = 0;

      vector[i].dni = 0;
   }
}

void agregarEmpleado(Empleado vector[]){

   Empleado empleado;

   char nombreAux[100];

   char apellidoAux[100];

   printf("Ingresar Apellido:\n");
   scanf("%s", apellidoAux);
   printf("Ingresar Nombre:\n");
   scanf("%s", nombreAux);
   printf("Ingresar edad:\n");
   scanf("%d", &empleado.edad);
   printf("Ingresar dni:\n");
   scanf("%d", &empleado.dni);
   printf("Ingresar Legajo:\n");
   scanf("%d", &empleado.legajo);
   strcpy(empleado.apellido, apellidoAux);
   strcpy(empleado.nombre, nombreAux);

   vector[empleado.legajo] = empleado;

   printf("El Empleado fue ingresado correctamente\n");
}

void imprimirEmpleado(Empleado aImprimir){

         printf("-Legajo = %d \n", aImprimir.legajo);
         printf("-Apellido = %s \n", aImprimir.apellido);
         printf("-Nombre = %s \n", aImprimir.nombre);
         printf("-Edad = %d \n", aImprimir.edad);
         printf("-DNI = %d \n", aImprimir.dni);
         printf("\n");

}
void listarEmpleados(Empleado vector[], int longitud) {

   printf("\nLISTA DE EMPLEADOS:\n\n");

   int cantidadDeEmpleados = 0;

   for(int i = 0; i<longitud; i++)
   {
      if(vector[i].dni != 0 )
      {
         imprimirEmpleado(vector[i]);

         cantidadDeEmpleados++;
      }
   }

    printf("Cantidad de empleados: %d \n", cantidadDeEmpleados);
}

void buscarEmpleadoPorNombre(Empleado vector[], int longitud){

   char nombre[100];

   printf("Ingresar Nombre: \n");

   int encontro = 0;

   scanf("%s", nombre);

   for(int i = 0; i<longitud; i++)
   {

      if(strcmp(vector[i].nombre, nombre) == 0)
      {
         encontro = 1;

         imprimirEmpleado(vector[i]);
      }
   }
   if(encontro == 0)
   {
      printf("No se encontraron resultados. \n");
   }
}

void getEmpleado(Empleado vector[]){

   int legajo;

   printf("Ingresar Legajo: \n");

   scanf("%d", &legajo);

   imprimirEmpleado(vector[legajo]);
}

void reemplazarEmpleado(Empleado vector[]){

   Empleado empleado;

   printf("Ingresar Legajo del empleado a reemplazar: \n");

   scanf("%d", &empleado.legajo);

   printf("El empleado a reemplazar es: \n");

   imprimirEmpleado(vector[empleado.legajo]);

   char nombreAux[100];

   char apellidoAux[100];

   printf("Ingresar Apellido del nuevo empleado:\n");
   scanf("%s", apellidoAux);
   printf("Ingresar Nombre del nuevo empleado:\n");
   scanf("%s", nombreAux);
   printf("Ingresar edad del nuevo empleado:\n");
   scanf("%d", &empleado.edad);
   printf("Ingresar dni del nuevo empleado:\n");
   scanf("%d", &empleado.dni);
   strcpy(empleado.apellido, apellidoAux);
   strcpy(empleado.nombre, nombreAux);

   vector[empleado.legajo] = empleado;

   printf("El Empleado fue ingresado correctamente\n");
}

void Salir()
{
    printf("Programa Finalizado. \n");
    system("pause");

}

void menu(Empleado vector[], int longitud) {

   int opciones;

   do{
      printf("\nMENU"
              "\n1- Crear Empleado"
              "\n2- Listar todos los Empleados "
              "\n3- Buscar empleado por legajo"
              "\n4- Remplazar Empleado "
              "\n5- Buscar Empleado por su Nombre "
              "\n6- Salir \n "
              "\nIngrese una Opcion:");

      scanf("%d", &opciones);

      switch(opciones) {

         case 1:
            agregarEmpleado(vector);
         break;

         case 2:
            listarEmpleados(vector, longitud);
         break;

         case 3:
            getEmpleado(vector);
         break;

         case 4:
            reemplazarEmpleado(vector);
         break;

         case 5:
            buscarEmpleadoPorNombre(vector, longitud);
         break;

         case 6:
             Salir();
         break;

         default:
            printf("Opcion Incorrecta. \n por favor ingrese un numero del 1 al 6 \n");
      }

   }while(opciones !=6);
}


