#include "hilo.h"

typedef struct auxiliarExponencial{
	int *arreglo;
	int valorABuscar;
	int *encontrado;
	int inicio;
	int final;
}AuxiliarExponencial;

void * procesarBusquedaExponencial(void* busqueda);

void BusquedaExponencial(int *A, int x, int inicio, int final, int * encontrado){
	int anterior = inicio, actual = inicio + 1;

	if(A[inicio] == x)
		*encontrado = 1;
	
	while((actual < final) && (A[actual] < x)){
		anterior = actual;
		actual *= 2;
	}
	
	if(*encontrado == -1)
		*encontrado = 0;
		
	if(*encontrado == 0)
		BusquedaBinaria(A, x, anterior, actual, encontrado);
}

void BusquedaBinaria(int *A, int x, int inf, int sup, int *encontrado){
	int limInf = inf;
	int limSup = sup;
	int centro = (limSup+limInf)/2;
	
	while((limInf <= limSup) && (*encontrado == 0)){
		if(A[centro] == x)
			*encontrado = 1;
				
		
		else if(A[centro] < x)
			limInf = centro+1;
			
		else
			limSup = centro-1;	
			
		centro = (limSup+limInf)/2; 
	}
	
	if(*encontrado != 1)
		*encontrado = 0; 
}

void BusquedaExponencialHilos(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado)
{
	int puntoMedio = (final - inicio) / 2;
	if(puntoMedio > 0)
	{
		// Comenzamos la
		// repartición de los subarreglos
		pthread_t *thread;
		thread = malloc(2*sizeof(pthread_t));
		// Creamos los auxiliares 
		AuxiliarExponencial * izq = (AuxiliarExponencial *)malloc(sizeof(AuxiliarExponencial));
		(*izq).arreglo = arreglo;
		(*izq).valorABuscar = valorABuscar;
		(*izq).encontrado = encontrado;
		(*izq).inicio = inicio;
		(*izq).final = puntoMedio;


		AuxiliarExponencial * der = (AuxiliarExponencial *)malloc(sizeof(AuxiliarExponencial));
		(*der).arreglo = arreglo;
		(*der).valorABuscar = valorABuscar;
		(*der).encontrado = encontrado;
		(*der).inicio = puntoMedio + 1;
		(*der).final = final;

		// Creamos los hilos
		if(pthread_create(&thread[0], NULL, procesarBusquedaExponencial, (void *)izq) != 0)
		{
			perror("El thread no  pudo crearse \n");
			exit(-1);
		}
		if(pthread_create(&thread[1], NULL, procesarBusquedaExponencial, (void *)der) != 0)
		{
			perror("El thread no  pudo crearse \n");
			exit(-1);
		}
		// Esperamos a los hilos
		int i;
		for (i=0; i<2; i++) pthread_join (thread[i], NULL);
		free(thread);
	}	
}

// Nos ayudará a lanzar la búsqueda exponencial por cada hilo
void * procesarBusquedaExponencial(void* busqueda)
{
	AuxiliarExponencial * b = (AuxiliarExponencial *)busqueda;
	BusquedaExponencial((*b).arreglo, (*b).valorABuscar,(*b).inicio, (*b).final, (*b).encontrado);
}


