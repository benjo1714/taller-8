#include "funciones.h"
#include <stdio.h>

int main()
{
    int max_time, max_resources;

    printf("Ingrese el tiempo maximo de produccion disponible en minutos: ");
    scanf("%d", &max_time);

    printf("Ingrese la cantidad maxima de recursos disponibles: ");
    scanf("%d", &max_resources);

    iniciarSistema(max_time, max_resources);

    return 0;
}