#include <pthread.h>
#include <stdlib.h>

void BusquedaExponencial(int *A, int x, int inicio, int final, int * encontrado);
void BusquedaBinaria(int *A, int x, int inf, int sup, int *encontrado);
void BusquedaExponencialHilos(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado);
