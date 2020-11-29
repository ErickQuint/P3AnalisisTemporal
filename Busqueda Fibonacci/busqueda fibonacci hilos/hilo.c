#include "hilo.h"

typedef struct auxiliarFibonacci{
	int *arreglo;
	int valorABuscar;
	int *encontrado;
	int final;
	int fibMMm1;
	int fibMMm2;
	int fibM;
}AuxiliarFibonacci;

void * procesarBusquedaFibonacci(void* busqueda);

int min(int x, int y){ 
	return (x<=y)? x : y; 
} 

void BusquedaFibonacci(int *A, int x, int n, int * encontrado, int fibMMm1, int fibMMm2, int fibM){
	int i;
	 
    int offset = -1; 

    while (fibM > 1 && (*encontrado == 0 || *encontrado == -1)){ 
        int i = min(offset+fibMMm2, n-1); 
  		
        if (A[i] < x){ 
            fibM  = fibMMm1; 
            fibMMm1 = fibMMm2; 
            fibMMm2 = fibM - fibMMm1; 
            offset = i; 
        } 
  
        else if (A[i] > x){ 
            fibM  = fibMMm2; 
            fibMMm1 = fibMMm1 - fibMMm2; 
            fibMMm2 = fibM - fibMMm1; 
        }
		
        else *encontrado = 1; 
    } 
  
    if(fibMMm1 && A[offset+1]==x) *encontrado = 1; 

    *encontrado = 0; 
}

void BusquedaFibonacciHilos(int * arreglo, int valorABuscar, int final, int * encontrado)
{
	int puntoMedio = final / 2;
	if(puntoMedio > 0)
	{
		int fibMMm2 = 0;   
    	int fibMMm1 = 1;    
    	int fibM = fibMMm2 + fibMMm1;
    	
		while (fibM < puntoMedio){ 
        	fibMMm2 = fibMMm1; 
        	fibMMm1 = fibM; 
        	fibM  = fibMMm2 + fibMMm1; 
    	}
		
		// Comenzamos la
		// repartición de los subarreglos
		pthread_t *thread;
		thread = malloc(2*sizeof(pthread_t));
		// Creamos los auxiliares 
		AuxiliarFibonacci * izq = (AuxiliarFibonacci *)malloc(sizeof(AuxiliarFibonacci));
		(*izq).arreglo = arreglo;
		(*izq).valorABuscar = valorABuscar;
		(*izq).encontrado = encontrado;
		(*izq).final = puntoMedio;
		(*izq).fibMMm1 = fibMMm1;
		(*izq).fibMMm2 = fibMMm2;
		(*izq).fibM = fibM;
		
		int fibMMm2_2 = fibMMm2;   
    	int fibMMm1_2 = fibMMm1;    
    	int fibM_2 = fibM; 
    	
    	while (fibM_2 < final){ 
        	fibMMm2_2 = fibMMm1_2; 
        	fibMMm1_2 = fibM_2; 
        	fibM_2  = fibMMm2_2 + fibMMm1_2; 
    	}

		AuxiliarFibonacci * der = (AuxiliarFibonacci *)malloc(sizeof(AuxiliarFibonacci));
		(*der).arreglo = arreglo;
		(*der).valorABuscar = valorABuscar;
		(*der).encontrado = encontrado;
		(*der).final = final;
		(*der).fibMMm1 = fibMMm1_2;
		(*der).fibMMm2 = fibMMm2_2;
		(*der).fibM = fibM_2;  

		// Creamos los hilos
		if(pthread_create(&thread[0], NULL, procesarBusquedaFibonacci, (void *)izq) != 0)
		{
			perror("El thread no  pudo crearse \n");
			exit(-1);
		}
		if(pthread_create(&thread[1], NULL, procesarBusquedaFibonacci, (void *)der) != 0)
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
void * procesarBusquedaFibonacci(void* busqueda)
{
	AuxiliarFibonacci * b = (AuxiliarFibonacci *)busqueda;
	BusquedaFibonacci((*b).arreglo, (*b).valorABuscar, (*b).final, (*b).encontrado, (*b).fibMMm1, (*b).fibMMm2, (*b).fibM);
}


