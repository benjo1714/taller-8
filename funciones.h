#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTS 100  // Número máximo de productos
#define NAME_LENGTH 50    // Longitud máxima del nombre

// Simulación de estructura con punteros
typedef struct
{
    char *name;              // Nombre del producto
    int *production_time;    // Tiempo de fabricación por unidad (en minutos)
    int *resources;          // Recursos necesarios por unidad
    int *demand;             // Cantidad demandada
} Product;

// Declaración de funciones
void liberarProducto(Product *producto);
void agregarProducto();
void editarProducto();
void eliminarProducto();
void calcularProduccion();
void iniciarSistema(int tiempo_max, int recursos_max);

#endif