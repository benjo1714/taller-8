#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales
Product *productos[MAX_PRODUCTS] = {NULL}; // Inicializar array a NULL
int count = 0;                             // Número de productos registrados
int max_time = 0, max_resources = 0;       // Restricciones de tiempo y recursos

// Función para inicializar un producto
Product *crearProducto()
{
    Product *producto = (Product *)malloc(sizeof(Product));
    producto->name = (char *)malloc(NAME_LENGTH * sizeof(char));
    producto->production_time = (int *)malloc(sizeof(int));
    producto->resources = (int *)malloc(sizeof(int));
    producto->demand = (int *)malloc(sizeof(int));
    return producto;
}

// Función para liberar un producto
void liberarProducto(Product *producto)
{
    if (producto)
    {
        free(producto->name);
        free(producto->production_time);
        free(producto->resources);
        free(producto->demand);
        free(producto);
    }
}

// Agregar un producto
void agregarProducto()
{
    if (count >= MAX_PRODUCTS)
    {
        printf("No se pueden agregar mas productos.\n");
        return;
    }
    productos[count] = crearProducto();
    printf("Ingrese el nombre del producto: ");
    scanf("%s", productos[count]->name);
    printf("Ingrese el tiempo de fabricacion (en minutos): ");
    scanf("%d", productos[count]->production_time);
    printf("Ingrese la cantidad de recursos necesarios: ");
    scanf("%d", productos[count]->resources);
    printf("Ingrese la cantidad demandada: ");
    scanf("%d", productos[count]->demand);
    count++;
    printf("Producto agregado correctamente.\n");
}

// Editar un producto
void editarProducto()
{
    char nombre[NAME_LENGTH];
    printf("Ingrese el nombre del producto a editar: ");
    scanf("%s", nombre);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(productos[i]->name, nombre) == 0)
        {
            printf("Producto encontrado. Ingrese nuevos valores:\n");
            printf("Nuevo tiempo de fabricacion: ");
            scanf("%d", productos[i]->production_time);
            printf("Nueva cantidad de recursos: ");
            scanf("%d", productos[i]->resources);
            printf("Nueva cantidad demandada: ");
            scanf("%d", productos[i]->demand);
            printf("Producto actualizado.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

// Eliminar un producto
void eliminarProducto()
{
    char nombre[NAME_LENGTH];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(productos[i]->name, nombre) == 0)
        {
            liberarProducto(productos[i]);
            for (int j = i; j < count - 1; j++)
            {
                productos[j] = productos[j + 1];
            }
            productos[count - 1] = NULL; // Evitar punteros colgantes
            count--;
            printf("Producto eliminado.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}
//calcular producto
void calcularProduccion()
{
    int total_time = 0;       // Variable para acumular el tiempo total requerido
    int total_resources = 0; // Variable para acumular los recursos totales necesarios

    // Iterar sobre cada producto registrado
    for (int i = 0; i < count; i++)
    {
        // Verificar que el producto y sus punteros no sean NULL y contengan valores válidos
        if (productos[i] != NULL && 
            productos[i]->production_time != NULL && 
            productos[i]->resources != NULL && 
            productos[i]->demand != NULL)
        {
            int tiempo = *(productos[i]->production_time);
            int recursos = *(productos[i]->resources);
            int demanda = *(productos[i]->demand);

            // Solo sumar si los valores son positivos
            if (tiempo > 0 && recursos > 0 && demanda > 0)
            {
                total_time += tiempo * demanda;
                total_resources += recursos * demanda;
            }
        }
    }

    // Imprimir los resultados
    printf("\nTiempo total de fabricacion requerido: %d minutos\n", total_time);
    printf("Cantidad total de recursos necesarios: %d\n", total_resources);

    // Verificar si se cumplen las limitaciones de tiempo y recursos
    if (total_time <= max_time && total_resources <= max_resources)
    {
        printf("La fabricacion puede cumplir con la demanda.\n");
    }
    else
    {
        printf("La fabricacion no puede cumplir con la demanda.\n");
    }
}
// Sistema principal
void iniciarSistema(int tiempo_max, int recursos_max)
{
    max_time = tiempo_max;
    max_resources = recursos_max;
    int choice;
    do
    {
        printf("\n--- Menu ---\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Calcular produccion\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            agregarProducto();
            break;
        case 2:
            editarProducto();
            break;
        case 3:
            eliminarProducto();
            break;
        case 4:
            calcularProduccion();
            break;
        case 5:
            printf("Saliendo del programa. Gracias por visitarnos.\n");
            break;
        default:
            printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (choice != 5);

    // Liberar memoria de todos los productos
    for (int i = 0; i < count; i++)
    {
        liberarProducto(productos[i]);
    }
}